# Project Requirements

This document lists everything you need to successfully build and run the **Environmental Monitoring System (Phase 1)**.

---

## Hardware Requirements

| Component | Purpose | Quantity |
| :--- | :--- | :--- |
| **Arduino Uno R3** | Main microcontroller to process sensor data and control the OLED. | 1 |
| **DHT11 Sensor** | Measures ambient temperature and humidity levels. | 1 |
| **1.3" OLED (SH1106)** | Visualizes the real-time environmental data using I2C. | 1 |
| **830-Point Breadboard** | Used for prototyping and organizing component connections. | 1 |
| **Jumper Wires (M-M)** | Connects the sensors and display to the Arduino pins. | 4 |
| **USB Type-B Cable** | Powers the Arduino and allows for code uploads from a PC. | 1 |

---

## Software & Libraries

| Tool / Library | Purpose | Version |
| :--- | :--- | :--- |
| **Arduino IDE** | The development environment used to write and upload the code. | 2.0+ |
| **U8g2 Library** | Essential for driving the SH1106 OLED; must be used in **Page Buffer Mode** to save RAM. | Latest |
| **DHT Sensor Library** | Used to interface with the DHT11 and read temperature/humidity data. | Latest |
| **Adafruit Unified Sensor** | A dependency required by the DHT library to function correctly. | Latest |

---
