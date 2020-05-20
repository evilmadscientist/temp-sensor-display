#include <LiquidCrystal.h>
#include "DHT.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, rw = 3, en = 4,
          d0 = 5, d1 = 6, d2 = 7, d3 = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12, // d7 was 12
          dhtpin = 13;

int cnt = 1;
float h;
float t;
float f;

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 500;

LiquidCrystal lcd(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7);
DHT dht(dhtpin, DHT22);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  dht.begin();
}

void loop() {
  if (cnt == 1) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    f = dht.readTemperature(true);
  }
  if (isnan(h) || isnan(t) || isnan(f)) {
    lcd.clear();
    lcd.print("Sensor read error!");
    delay(1000);
    return;
  }
  lcd.clear();
  lcd.print("TEMP    (");
  lcd.print(char(223));
  lcd.print("F) ");
  lcd.print(cnt % 2 == 0 ? ": " : "  ");
  lcd.print(f);
  lcd.setCursor(0,1);
  lcd.print("TEMP    (");
  lcd.print(char(223));
  lcd.print("C) ");
  lcd.print(cnt % 2 == 0 ? ": " : "  ");
  lcd.print(t);
  lcd.setCursor(0,3);
  lcd.print("HUMIDITY (%) ");
  lcd.print(cnt % 2 == 0 ? ": " : "  ");
  lcd.print(h);
  lcd.setCursor(0,0);
  cnt += 1;
  if (cnt == 3) {
    cnt = 1;
  }
  delay(1000);
}
