# ESP8266 LCD Dashboard

This project is a feature-rich 20x4 LCD dashboard powered by an ESP8266 microcontroller. It can display weather, news, indoor climate data, and custom messages.

## 🔧 Features
- Weather display using a public API
- Local news via RSS
- DHT11 temperature and humidity readings
- Remote control via infrared remote

## 🧰 Tech Stack
- C++ with Arduino framework
- ESP8266 WiFi + SPI LCD
- DHT sensor
- IR remote

## Hardware Setup
- LCD SDA pin -> ESP8266 D2 pin
- LCD SCL pin -> ESP8266 D1 pin
- IR Reciever data pin -> ESP8266 D5 pin
- DHT11 Sensor data pin -> ESP8266 D6 pin

## TODO
- Local server to update messages remotely
- RSS Feeds
- Pixel art / fun animations
- Power-saving modes and auto-cycling display
- Custom character LCD handling
- AP wifi Setup
- EEPROM
- Pagination
- Wi-Fi signal monitoring