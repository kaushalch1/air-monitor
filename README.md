# Portable Air Quality Monitor

## Overview

this is a portable air quality monitoring device designed to measure particulate matter and environmental conditions in real time. it uses an ESP32 S3 microcontroller to collect sensor data,and display measurements, and store readings locally for later analysis.

The device supports offline data logging to a microsd card, allowing users to monitor air quality without requiring a continuous phone or internet connection.

## Features

- measures particulate matter, including pm1.0, pm2.5, and pm10, using a compatible particulate matter sensor.
- measures temperature and relative humidity using the SHT31 sensor.
- measures atmospheric pressure using the BMP280 sensor.
- displays the data by live sensor readings on an SSD1306 OLED display.
- records measurements to a microSD card in CSV format.
- uses a DS3231 real time clock for timestamps during offline logging.
- Supports Bluetooth Low Energy for wireless data monitoring.
- includes wi-fi capability for future wireless features.
  
## Hardware Components

| Name | Purpose | Quantity | Total Cost (USD) | Link | Distributor |
|---|---|---:|---:|---|---|
| DS3231M+TRL (SOIC-16W) | Real-time clock | 1 | 8.25 | [Link](https://www.lcsc.com/product-detail/C37663.html) | LCSC |
| BMP280 | Pressure sensor | 1 | 6.03 | [Link](https://www.lcsc.com/product-detail/C83291.html) | LCSC |
| ESP32-S3-WROOM-1-N16R8 | Main MCU (Wi-Fi/BLE) | 1 | 5.54 | [Link](https://www.lcsc.com/product-detail/C2913202.html) | LCSC |
| SHT31-DIS-B2.5kS | Temperature/humidity sensor | 1 | 3.41 | [Link](https://www.lcsc.com/product-detail/C80862.html) | LCSC |
| 0.91 inch OLED (ER-OLEDM0.91-1W-I2C) | Display | 1 | 2.80 | [Link](https://www.buydisplay.com/i2c-white-0-91-inch-oled-display-module-128x32-arduino-raspberry-pi) | BuyDisplay |
| BQ24074RGTR | Li-ion battery charger / power path | 1 | 1.59 | [Link](https://www.lcsc.com/product-detail/C54313.html) | LCSC |
| microSD socket (DM3AT-SF-PEJM5) | Data logging storage | 1 | 1.12 | [Link](https://www.lcsc.com/product-detail/C114218.html) | LCSC |
| USB-C receptacle (TYPE-C-31-M-12) | USB-C charging and data port | 1 | 0.19 | [Link](https://www.lcsc.com/product-detail/C165948.html) | LCSC |
| CR2032 holder (CR2032-BS-6-1) | RTC backup battery holder | 1 | 0.15 | [Link](https://www.lcsc.com/product-detail/C70377.html) | LCSC |
| AP2112K-3.3TRG1 | 3.3V LDO regulator | 1 | 0.13 | [Link](https://www.lcsc.com/product-detail/C51118.html) | LCSC |
| USBLC6-2SC6 | USB ESD protection | 1 | 0.13 | [Link](https://www.lcsc.com/product-detail/C7519.html) | LCSC |
| 4.7uH inductor 6.3x6.3mm (proxy: Chilisin MHCI06030-4R7M-R8) | Boost converter inductor | 1 | 0.11 | [Link](https://www.lcsc.com/product-detail/C108295.html) | LCSC |
| MT3608 | Boost converter | 1 | 0.08 | [Link](https://www.lcsc.com/product-detail/C84817.html) | LCSC |
| SS34 Schottky diode (SMA) | Power path / reverse protection diode | 1 | 0.07 | [Link](https://www.lcsc.com/product-detail/C2759883.html) | LCSC |
| Tact switch 6mm THT | User buttons | 3 | 0.10 | [Link](https://www.lcsc.com/search?q=tactile+switch+6x6+THT) | LCSC |
| 1x8 female socket header 2.54mm | Sensor/expansion header | 1 | 0.08 | [Link](https://www.lcsc.com/search?q=1x8+female+header+2.54mm) | LCSC |
| 10uF capacitor 0805 | Bulk/decoupling capacitors | 4 | 0.19 | [Link](https://www.lcsc.com/product-detail/C15850.html) | LCSC |
| Resistors 0805 (5.1k, 890, 1.5k, 10k, 100k, 75k) | Pull-ups, dividers, config resistors | 11 | 0.05 | [Link](https://www.lcsc.com/search?q=0805+1%25+resistor) | LCSC |
| 1uF capacitor 0805 | Filter capacitors | 3 | 0.04 | [Link](https://www.lcsc.com/search?q=CL21B105KBFNNNE) | LCSC |
| 4.7uF capacitor 0805 | Filter capacitor | 1 | 0.03 | [Link](https://www.lcsc.com/search?q=CL21A475KAQNNNE) | LCSC |
| 100nF capacitor 0805 | IC bypass capacitors | 4 | 0.03 | [Link](https://www.lcsc.com/product-detail/C1711.html) | LCSC |
| 1x2 pin header 2.54mm | Power/battery header | 1 | 0.02 | [Link](https://www.lcsc.com/search?q=1x2+pin+header+2.54mm) | LCSC |
| PCB (bare board) | Main PCB | 1 | 0.40 | [Link](https://jlcpcb.com/) | JLCPCB |
| PCB assembly (PCBA fees) | SMT + through-hole assembly fees | 1 | 8.17 | [Link](https://jlcpcb.com/) | JLCPCB |
## Software and Tools

- kica - Schematic capture and PCB design
- platformIO - Firmware development and building
- arduino framework for ESP32
- wokwi - Partial hardware simulation

## Data Logging

AirTrace records measurements locally so that monitoring can continue without a phone or internet connection.

The CSV log is intended to contain fields such as:

- Timestamp
- PM1.0 concentration
- PM2.5 concentration
- PM10 concentration
- Temperature
- Relative humidity
- Atmospheric pressure
- Battery voltage

## Hardware Assembly

1. Assemble the power supply, USB-C charging circuit, and battery connections.
2. Connect the ESP32-S3 and verify the regulated supply voltages.
3. Connect the environmental sensors to the I2C bus.
4. Connect the particulate matter sensor using its verified interface and pinout.
5. Connect the OLED display, microSD module, RTC, and buttons.
6. Check polarity, continuity, power rails, and signal connections before powering the complete circuit.
7. Test each peripheral individually before running the complete firmware.

# schematic
<img width="1132" height="796" alt="image" src="https://github.com/user-attachments/assets/6c2d3d72-e3c3-46b5-801b-355a0d9f41e2" />
# pcb img:
<img width="1171" height="782" alt="image" src="https://github.com/user-attachments/assets/bbb9d440-6bc1-4266-9c78-3080bf99bff3" />
# 3d view:
<img width="986" height="630" alt="image" src="https://github.com/user-attachments/assets/ee0b3d59-2c8a-4708-a806-034f5830e7a6" />
# 3d model:
<img width="1917" height="782" alt="image" src="https://github.com/user-attachments/assets/fdaf11a3-a4f4-4061-b908-233ae6757868" />
# assembly model:
![Uploading image.png…]()

