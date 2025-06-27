#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include "../interfaces/INetwork.h"
#include "../interfaces/IObject.h"
class WiFiManager : public INetwork , public IObject {
public:
     //WiFiManager(const char* ssid, const char* password);


     void init() override;

     void setCredentials(const char* ssid, const char* password);
     void connect() override;
     bool isConnected()  override;

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

#endif // WIFI_MANAGER_H
