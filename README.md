# Environmental Monitoring System (Phase 1)

This project is a real-time temperature and humidity dashboard designed to monitor room environments. It utilizes a **DHT11 sensor** for data acquisition and a **1.3" OLED (SH1106)** for clear, live visualization.

---

## The Build
*   **Refresh Rate:** 2 seconds — specifically optimized to match the physical sampling limits of the DHT11 sensor.
*   **Communication:** The 1.3" OLED utilizes the **I2C protocol** (SDA/SCL) for a clean, two-wire data interface.
*   **Optimization:** The system was originally hitting a **92% RAM usage error** on the Arduino Uno due to full frame buffering. I successfully resolved this by switching to **Page Buffer Mode** (`u8g2.firstPage()`), significantly reducing the memory footprint.

## Components
*   **Microcontroller:** Arduino Uno Rev3
*   **Display:** 1.3" OLED Display (SH1106 Driver)
*   **Sensor:** DHT11 Temperature & Humidity Sensor
*   **Prototyping:** 830-point Breadboard & Jumper Wires

## Wiring photo
![Prototype Wiring](IMG_4919.jpg)
*Live dashboard showing temperature and humidity readings.*

---
*Next steps: Integrating RGB alerts and buzzer notifications (Phase 2).*
