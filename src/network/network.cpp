#include "network.h"
#include <Arduino.h>

void WiFiManager::setCredentials(const char* ssid, const char* password){
      _ssid = ssid;
      _password = password;
}



void WiFiManager::init(){
     connect();
}

void WiFiManager::connect() {
     Serial.println("Connecting to Wi-Fi...");

     WiFi.mode(WIFI_STA);
     WiFi.begin(_ssid, _password);
     WiFi.hostname("esp8266");

     IPAddress local_IP(192, 168, 0, 184);
     IPAddress gateway(192, 168, 0, 1);
     IPAddress subnet(255, 255, 255, 0);
     IPAddress primaryDNS(8, 8, 8, 8);
     WiFi.config(local_IP, gateway, subnet, primaryDNS);

     int attempts = 0;
     while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
          if (++attempts > 40) {
               Serial.println("\nFailed to connect to WiFi.");
               return;
          }
     }

     Serial.println();
     Serial.printf("Connected! IP address: %s\n", WiFi.localIP().toString().c_str());
     delay(2000);
}

bool WiFiManager::isConnected() {
     return WiFi.status() == WL_CONNECTED;
}

const char* WiFiManager::getSSID() const {
     return _ssid;
}

const char* WiFiManager::getPassword() const {
     return _password;
}

const char* WiFiManager::getLocalIP() {
     _ipBuffer = WiFi.localIP().toString();
     return _ipBuffer.c_str();
}

const char* WiFiManager::getDNS() {
     _ipBuffer = WiFi.dnsIP().toString();
     return _ipBuffer.c_str();
}

const char* WiFiManager::getGateway() {
     _ipBuffer = WiFi.gatewayIP().toString();
     return _ipBuffer.c_str();
}

const char* WiFiManager::getSubnet() {
     _ipBuffer = WiFi.subnetMask().toString();
     return _ipBuffer.c_str();
}
