/* * PROJECT: Environmental Monitoring & Response System (V2.0)
 * AUTHOR: Chukwuemeka Ifeanyi (@emekabuilds_ on X)
 * DESCRIPTION: A multi-phase project that monitors temperature and humidity.
 * It features a live OLED dashboard and a non-blocking alarm system (RGB/Buzzer).
 * I ensured the comments are explanatory to aid understanding.
 */

#include <Arduino.h>
#include <U8g2lib.h> // Library for the OLED display
#include "DHT.h"     // Library for the Temp/Humidity sensor

// --- Hardware Pin Definitions ---
#define DHTPIN 2      // Sensor connected to Digital Pin 2
#define DHTTYPE DHT11 // Using the DHT11 sensor model
#define BUZZER_PIN 9  // Alarm buzzer
#define RED_PIN 3     // RGB Red channel
#define GREEN_PIN 5   // RGB Green channel
#define BLUE_PIN 6    // RGB Blue channel

// --- Safety Thresholds ---
// Change these values to suit your specific environment!
const float TEMP_HIGH = 27.50;  
const float TEMP_LOW  = 15.0; 
const float HUMID_HIGH = 75.0;

// --- Timing Variables (The secret to multitasking) ---
unsigned long prevDHTMillis = 0;   // Stores the last time the sensor was read
unsigned long prevAlarmMillis = 0; // Stores the last time the alarm pulsed
const long dhtInterval = 2000;     // Read sensor every 2 seconds (DHT11 limit)
const long alarmPulse = 150;       // Speed of the alarm flash/beep (in ms)

// --- System States ---
bool alarmToggle = false;   // Keeps track of the alarm "blink" state
bool isAlarmActive = false; // Is the environment currently unsafe?
String alarmMessage = "";   // Holds the text to show on screen during alerts

// Initialize the sensor and the OLED (SH1106 driver)
DHT dht(DHTPIN, DHTTYPE);
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Helper function to easily change RGB colors
void setRGB(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  dht.begin();
  u8g2.begin();
}

void loop() {
  // We use currentMillis to track time without stopping the code (non-blocking)
  unsigned long currentMillis = millis();
  static float h = 0, t = 0;

  // 1. SENSOR LOGIC
  // We only read the sensor every 2 seconds to avoid heating it up or getting errors
  if (currentMillis - prevDHTMillis >= dhtInterval) {
    prevDHTMillis = currentMillis;
    float newH = dht.readHumidity();
    float newT = dht.readTemperature();
    
    // Check if the sensor is actually working
    if (!isnan(newH) && !isnan(newT)) {
      h = newH;
      t = newT;
      
      // Compare readings against our set thresholds
      if (t > TEMP_HIGH) { 
        isAlarmActive = true; 
        alarmMessage = "TEMP TOO HIGH!"; 
      } else if (t < TEMP_LOW) { 
        isAlarmActive = true; 
        alarmMessage = "TEMP TOO LOW!"; 
      } else if (h > HUMID_HIGH) { 
        isAlarmActive = true; 
        alarmMessage = "HUMID TOO HIGH!"; 
      } else {
        isAlarmActive = false; // Environment is safe
        alarmMessage = "";
      }
    } else {
      alarmMessage = "SENSOR ERROR";
      isAlarmActive = true; // Trigger alarm if sensor fails
    }
  }

  // 2. ALARM & RGB LOGIC (Visual & Audio Feedback)
  if (isAlarmActive) {
    // This creates a pulsing effect without using delay()
    if (currentMillis - prevAlarmMillis >= alarmPulse) {
      prevAlarmMillis = currentMillis;
      alarmToggle = !alarmToggle; // Switch between true/false
      
      if (alarmToggle) {
        digitalWrite(BUZZER_PIN, HIGH);
        setRGB(255, 0, 0); // Flash Danger Red
      } else {
        digitalWrite(BUZZER_PIN, LOW);
        setRGB(0, 0, 0);   // LED Off
      }
    }
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    setRGB(0, 255, 0); // Solid Green when everything is OK
  }

  // 3. DISPLAY LOGIC (OLED Rendering)
  // Page Buffer Mode: Renders the screen in strips to save Arduino RAM
  u8g2.firstPage();
  do {
    // Header
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 12, "ENV MONITOR V2.0");
    u8g2.drawHLine(0, 14, 128); // Horizontal line
    
    // Live Data Display
    u8g2.setFont(u8g2_font_7x14_tf); 
    u8g2.setCursor(0, 35); u8g2.print("Temp: "); u8g2.print(t, 1); u8g2.print(" C");
    u8g2.setCursor(0, 50); u8g2.print("Humid: "); u8g2.print(h, 1); u8g2.print(" %");

    // Dynamic Status Bar
    if (isAlarmActive) {
      u8g2.drawBox(0, 54, 128, 10); // Draw a background box for the alert
      u8g2.setDrawColor(0);         // Change color to black for text
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.setCursor(2, 62); u8g2.print(alarmMessage);
      u8g2.setDrawColor(1);         // Reset color to white
    } else {
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.drawStr(0, 62, "SYSTEM STATUS: OK");
    }
  } while (u8g2.nextPage());
}
