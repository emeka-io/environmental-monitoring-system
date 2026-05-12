# Project Requirements (Phase 2)

This document lists the hardware, software, and technical dependencies required to build the **Responsive Environmental Safety System**. Phase 2 builds upon the Phase 1 foundation by adding real-time, multi-tasking alert capabilities.

---

## Hardware Requirements

| Component | Purpose | Quantity |
| :--- | :--- | :--- |
| **Arduino Uno R3** | The "brain" of the system; handles sensor polling and multi-tasking logic. | 1 |
| **DHT11 Sensor** | Measures ambient temperature and humidity levels. | 1 |
| **1.3" OLED (SH1106)** | Displays the live dashboard and high-contrast system alerts. | 1 |
| **RGB LED Module** | Provides visual status (Green = OK, Flashing Red = Danger). | 1 |
| **Active Buzzer** | Provides auditory "staccato" pulses during environmental alerts. | 1 |
| **220Ω Resistors** | Essential for limiting current to protect the RGB LED channels. | 3 |
| **830-Point Breadboard** | Central hub for all component and power rail connections. | 1 |
| **Jumper Wires (M-M)** | Connects the sensors, display, and alert modules to the Arduino. | ~15 |

---

## Software & Libraries

| Tool / Library | Purpose | Version |
| :--- | :--- | :--- |
| **Arduino IDE(or any suitable alternative)** | Used to compile and upload the non-blocking Phase 2 code. | 2.0+ |
| **U8g2 Library** | Handles OLED rendering; **Page Buffer Mode** is mandatory for system stability. | Latest |
| **DHT Sensor Library** | Interfaces with the DHT11 to provide temperature/humidity floats. | Latest |
| **Adafruit Unified Sensor** | Backend dependency required by the DHT sensor library. | Latest |

---

## Technical Skills Covered

By completing Phase 2, you will implement:
* **Non-Blocking Logic:** Master the use of `millis()` for timing to keep the system responsive without using `delay()`.
* **I2C Protocol:** Managing a two-wire communication interface for the display.
* **Current Limiting:** Understanding the role of resistors in protecting sensitive components like the RGB module.

---
*Built and documented by **Chukwuemeka Ifeanyi** | Mechatronics Engineering Student | May 2026*
