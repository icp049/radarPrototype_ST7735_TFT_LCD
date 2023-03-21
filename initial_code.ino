#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>




const int TRIGGER_PIN = 6;
const int ECHO_PIN = 5;
const int NUM_READINGS = 5;
const int MAX_DISTANCE = 30; 
const int MIN_DISTANCE = 4; 
const int BUZZER = 3;
const int potPin = A0;  
int potVal; 
int pos = 0;    

Servo myservo; 
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display





void setup()
{
  myservo.attach(7); 
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop()
{
  float totalDistance = 0;

   for (int i = 0; i < NUM_READINGS; i++) {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
  
    float duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration / 58.2;
  
    Serial.print("Distance ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(distance);
    Serial.println(" cm");
  
    totalDistance += distance;
  }
  
  float averageDistance = totalDistance / NUM_READINGS;

  Serial.print("Average Distance: ");
  Serial.print(averageDistance);
  Serial.println(" cm");

   if (averageDistance > MAX_DISTANCE) {
   
    lcd.setCursor(0, 1);
    lcd.print("Out of range");
    lcd.setCursor(12, 1);
    lcd.print("             ");
    lcd.setCursor(0, 0);
    lcd.print("                  ");
    noTone(BUZZER);
    delay(100);
    
    
    
  } else if (averageDistance < MIN_DISTANCE) {
  
    lcd.setCursor(15, 0);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("IMPACT! IMPACT!"); 
    lcd.setCursor(0, 0);
    lcd.print("IMPACT! IMPACT!");
    tone(BUZZER,500);
    delay(100);
  
    
   
    
    
  } else {
    lcd.setCursor(0, 1);
    lcd.print(averageDistance, 2);
    lcd.print(" cm");
    lcd.setCursor(7, 1);
    lcd.print("            ");
    lcd.setCursor(0, 0);
    lcd.print("OBJECT DETECTED!");
    noTone(BUZZER);
    delay(100);
   
    
    
    
    
  }
  
  delay(200); // Delay for 500 milliseconds (0.5 seconds)

  potVal = analogRead(potPin); 
  

  
  if (potVal > 0) {
    
    int angle = map(potVal, 0, 1023, 0, 180); 
    myservo.write(angle);  
    delay(10);            
  }
  
  if(TRIGGER_PIN, HIGH){

      myservo.detach();
  
  }else {

    myservo.attach(7); 
    int angle = 90;
    
    for (pos = 90 - angle; pos <= 90 + angle; pos++)
    {
      myservo.write(pos);  
      delay(10);           
    }

    for (pos = 90 + angle; pos >= 90 - angle; pos--)
    {
      myservo.write(pos);  
      delay(10);          
    }
  }

}