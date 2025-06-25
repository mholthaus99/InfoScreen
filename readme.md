# InfoScreen

**InfoScreen** is a modular, extensible dashboard for ESP8266-based microcontrollers with a 20x4 I2C LCD display. It provides real-time data such as weather, time, Wi-Fi status, news headlines, and indoor climate. Users can navigate views and trigger actions using an infrared (IR) remote.

<!-- ![Front view of InfoScreen](assets/front.jpg)
![Body render](assets/body_render.jpg) -->

<div style="display: flex; justify-content: center; gap: 20px; align-items: flex-start;">
  <img src="assets/front.jpg" alt="Front View" style="height: 230px; object-fit: contain;">
  <img src="assets/body_render.jpg" alt="Body Render" style="height: 230px; object-fit: contain;">
</div>

---

## ✨ Features

- **Weather Display:** Current conditions from OpenWeatherMap  
- **Time Sync:** Accurate time via NIST time servers  
- **News Headlines:** Displays RSS news feeds  
- **Indoor Climate:** Temperature and humidity from a DHT11 sensor  
- **Wi-Fi Status:** SSID, IP, and signal strength info  
- **IR Remote Control:** Navigate menus and trigger functions  
- **Modular Architecture:** Add new views and data sources easily  
- **Pixel Art & Custom Characters:** Fun, animated display options  

---

## 🛠️ Hardware Setup

| Component               | ESP8266 Pin |
|------------------------|-------------|
| LCD SDA                | D2          |
| LCD SCL                | D1          |
| IR Receiver Data       | D5          |
| DHT11 Sensor Data      | D6          |

Supported boards include NodeMCU, Wemos D1 mini, and other ESP8266 variants.

---

## 🧰 External Libraries

- **LCD I2C:** [`duinowitchery/hd44780@^1.3.2`](https://github.com/duinoWitchery/hd44780)
- **IR Receiver:** [`crankyoldgit/IRremoteESP8266@^2.8.6`](https://github.com/crankyoldgit/IRremoteESP8266)
- **DHT Sensor:**
  - [`adafruit/Adafruit Unified Sensor @ ^1.1.15`](https://github.com/adafruit/Adafruit_Sensor)
  - [`adafruit/DHT sensor library @ ^1.4.6`](https://github.com/adafruit/DHT-sensor-library)
- **Data Parsing:** [`bblanchon/ArduinoJson @ ^7.4.2`](https://github.com/bblanchon/ArduinoJson)

---

## 🧱 Project Structure

'''
src/
main.cpp ; Arduino entry point
system/
controller.*; Main application logic
view_controller.* ; View switching and rendering
display.*; LCD abstraction layer
ir_receiver.* ; IR input handler
views/
view.*; Abstract base view
default_view.* ; Default info (weather, time, climate)
news_view.*; RSS news headlines
menu_view.* ; Menu / actions interface
network/
network.*; Wi-Fi utilities
weather.* ; OpenWeatherMap integration
time_utils.*; NIST time sync
rss_reader.* ; RSS feed handling
sensors/
dht_sensor.* ; DHT11 interface
secrets.h ; Wi-Fi & API credentials (excluded from git)

'''

## 🚀 Getting Started

1. **Clone this repository**
2. **Install [PlatformIO](https://platformio.org/)** (recommended via VS Code)
3. **Configure your `secrets.h`:**

    ```cpp
    #define WIFI_SSID "your-ssid"
    #define WIFI_PASS "your-password"
    #define OPENWEATHERMAP_API_KEY "your-api-key"
    #define NEWS_URL "your-rss-url"
    #define TIMEZONE_OFFSET -5 // e.g., CST
    #define DAYLIGHT_SAVING_TIME 1
    ```

4. **Wire your hardware** according to the diagram above
5. **Build and upload** to your ESP8266 board

---

## 🧪 Planned Features & TODOs

- [ ] Local server to push messages remotely  
- [ ] Pixel art & fun LCD animations  
- [ ] Custom character support  
- [ ] Wi-Fi AP setup  
- [ ] EEPROM settings storage  
- [ ] View pagination and transitions  
- [ ] Wi-Fi signal strength indicator  
- [ ] `secrets.h` auto-generator for easier setup  

---

## 📄 License

[MIT License](LICENSE)

---

**InfoScreen** is built to be extensible and hackable—customize views, add sensors, and make the interface your own!
