#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Servo.h>

#define TFT_CS   10
#define TFT_RST  8
#define TFT_DC   9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Servo myservo;

void setup() {
  tft.initR();
  tft.fillScreen(ST7735_BLACK);
  myservo.attach(7);
  tft.setRotation(1);

  tft.drawCircle(80, 120, 30, ST7735_RED);
  tft.drawCircle(80, 120, 50, ST7735_RED);

  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.print("Servo position:");
  
}

void loop() {
 

  float prev_x, prev_y; // Add variables to store previous endpoint

  // Move servo from 0 to 180
  for(int pos = 0; pos <= 180; pos++) {
    tft.drawCircle(80, 120, 30, ST7735_RED);
    tft.drawCircle(80, 120, 50, ST7735_RED);
    myservo.write(pos);
    delay(5);

    float x = map(pos, 0, 180, 30, 130);
    float y = -sqrt(pow(50, 2) - pow(x - 80, 2)) + 120;
    
    tft.fillRect(0, 20, 120, 10, ST7735_BLACK);
    tft.setCursor(0, 20);
    tft.setTextColor(ST7735_CYAN);
    tft.setTextSize(2);
    tft.print(pos);

    tft.drawLine(80, 120, prev_x, prev_y, ST7735_BLACK); // Draw over previous line
    tft.drawLine(80, 120, x, y, ST7735_PWCTR6); // Draw current line
    prev_x = x; // Store current endpoint as previous endpoint for next iteration
    prev_y = y;
    delay(10);
  }

  // Move servo from 180 to 0
  for(int pos = 180; pos >= 0; pos--) {
    tft.drawCircle(80, 120, 30, ST7735_RED);
  tft.drawCircle(80, 120, 50, ST7735_RED);

    myservo.write(pos);
    delay(5);

    float x = map(pos, 0, 180, 30, 130);
    float y = -sqrt(pow(50, 2) - pow(x - 80, 2)) + 120;
    
    tft.fillRect(0, 20, 120, 10, ST7735_BLACK);
    tft.setCursor(0, 20);
    tft.setTextColor(ST7735_CYAN);
    tft.setTextSize(2);
    tft.print(pos);

    tft.drawLine(80, 120, prev_x, prev_y, ST7735_BLACK); // Draw over previous line
    tft.drawLine(80, 120, x, y, ST7735_PWCTR6); // Draw current line
    prev_x = x; // Store current endpoint as previous endpoint for next iteration
    prev_y = y;
    delay(10);
  }
}
