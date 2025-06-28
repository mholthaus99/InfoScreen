#pragma once
#include <ESP8266WiFi.h>

class WiFiManager {
   public:
    void begin(const char* ssid, const char* password);
    bool isConnected();

    const char* getSSID() const;
    const char* getPassword() const;
    const char* getLocalIP();
    const char* getDNS();
    const char* getGateway();
    const char* getSubnet();

   private:
    const char* _ssid;
    const char* _password;
    String _ipBuffer;
};
