#include <Arduino.h>
#include <U8g2lib.h>
#include "DHT.h"

#define DHTPIN 2     
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Changed _F_ to _1_ to save RAM (Page Buffer Mode)
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

bool toggle = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  u8g2.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Page Buffer loop: This is the standard way to save RAM with U8g2
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr); 
    u8g2.drawStr(0, 10, "ROOM ENVIRONMENT");
    u8g2.drawHLine(0, 12, 128);

    if (isnan(h) || isnan(t)) {
      u8g2.drawStr(0, 40, "Sensor Error!");
    } else {
      u8g2.setCursor(0, 35);
      u8g2.print("Temp:  "); u8g2.print(t, 1); u8g2.print(" C");
      u8g2.setCursor(0, 55);
      u8g2.print("Humid: "); u8g2.print(h, 1); u8g2.print(" %");

      if (toggle) {
        u8g2.setFont(u8g2_font_u8glib_4_tf);
        u8g2.drawStr(90, 62, "READING...");
      }
    }
  } while ( u8g2.nextPage() );

  toggle = !toggle;
  
  // Debugging output
  Serial.print("T: "); Serial.print(t); 
  Serial.print("C | H: "); Serial.print(h); Serial.println("%");
  
  delay(2000); 
}
