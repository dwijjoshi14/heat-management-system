#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

// LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// NeoPixel Strip
#define LED_PIN    9
#define LED_COUNT  80
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Fan & Temp
#define FAN_PIN   6
#define TEMP_PIN  A0

void setStripColor(int r, int g, int b) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void setup() {
  lcd.begin(16, 2);
  strip.begin();
  strip.show();
  pinMode(FAN_PIN, OUTPUT);
  analogWrite(FAN_PIN, 255); // PMOS off at startup
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  // TMP36 temperature conversion
  int raw = analogRead(TEMP_PIN);
  float voltage = raw * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0;

  int fanSpeed;

  if (tempC > 85) {
    fanSpeed = 255;
    setStripColor(255, 0, 0);       // RED — critical
  } else if (tempC > 60) {
    fanSpeed = 180;
    setStripColor(255, 180, 0);     // YELLOW — hot
  } else if (tempC > 30) {
    fanSpeed = 120;
    setStripColor(0, 255, 0);       // GREEN — warm
  } else {
    fanSpeed = 0;
    setStripColor(0, 0, 255);       // BLUE — safe
  }

  // Invert PWM for PMOS high-side driver
  analogWrite(FAN_PIN, 255 - fanSpeed);

  // Update LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print("C  ");
  lcd.setCursor(0, 1);
  lcd.print("Fan: ");
  lcd.print(map(fanSpeed, 0, 255, 0, 100));
  lcd.print("%  ");

  delay(200);
}
