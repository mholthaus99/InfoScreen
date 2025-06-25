/**
 * @file network.cpp
 * @brief WiFi utility functions for ESP8266.
 *
 * This file provides a set of utility functions within the WiFiUtils namespace
 * to manage WiFi connectivity on the ESP8266 platform. It includes functions
 * for connecting to a WiFi network, checking connection status, and retrieving
 * network information such as SSID, password, IP address, DNS, gateway, and subnet.
 *
 * Dependencies:
 * - ESP8266WiFi.h: ESP8266 WiFi library.
 * - secrets.h: Header file containing WiFi credentials (WIFI_SSID, WIFI_PASS).
 * - network.h: Header file for this module.
 *
 * Functions:
 * - void wifi_connect(void (*statusCallback)(const char *)): Connects to WiFi and provides status
 * updates via callback.
 * - bool wifi_isConnected(): Checks if the device is connected to WiFi.
 * - const char *getprint_wifi_ssid(): Returns the configured WiFi SSID.
 * - const char *getprint_wifi_password(): Returns the configured WiFi password.
 * - const char *getprint_wifi_ip(): Returns the current local IP address as a string.
 * - const char *getprint_wifi_dns(): Returns the current DNS server IP as a string.
 * - const char *getprint_wifi_gateway(): Returns the current gateway IP as a string.
 * - const char *getprint_wifi_subnet(): Returns the current subnet mask as a string.
 *
 * @namespace WiFiUtils
 */
#include "network.h"

#include <ESP8266WiFi.h>

#include "secrets.h"

namespace WiFiUtils
{

     static const char* ssid = WIFI_SSID;
     static const char* password = WIFI_PASS;

     void wifi_connect(void (*statusCallback)(const char*))
     {
          Serial.println("Connecting to Wi-Fi...");

          WiFi.mode(WIFI_STA);
          WiFi.begin(ssid, password);
          WiFi.hostname("esp8266");

          IPAddress local_IP(192, 168, 0, 184);
          IPAddress gateway(192, 168, 0, 1);
          IPAddress subnet(255, 255, 255, 0);
          IPAddress primaryDNS(8, 8, 8, 8);
          WiFi.config(local_IP, gateway, subnet, primaryDNS);

          int attempts = 0;
          String statusMsg = "Starting WiFi.\n\nConnecting.";

          while (WiFi.status() != WL_CONNECTED)
          {
               delay(500);
               Serial.print(".");
               attempts++;
               statusMsg += ".";

               if (statusCallback) statusCallback(statusMsg.c_str());

               if (attempts > 40)
               {
                    Serial.println("\nFailed to connect to WiFi.");
                    if (statusCallback) statusCallback("WiFi Failed.");
                    return;
               }
          }

          Serial.println();
          Serial.printf("Connected! IP address: %s\n", WiFi.localIP().toString().c_str());

          if (statusCallback)
          {
               statusCallback("");
               String msg = "Connected!\n\nSSID:";
               msg += WiFi.SSID();
               msg += "\nIP:";
               msg += WiFi.localIP().toString();
               statusCallback(msg.c_str());
          }

          delay(2000);
     }

     bool wifi_isConnected() { return WiFi.status() == WL_CONNECTED; }

     const char* getprint_wifi_ssid() { return ssid; }

     const char* getprint_wifi_password() { return password; }

     const char* getprint_wifi_ip() { return WiFi.localIP().toString().c_str(); }

     const char* getprint_wifi_dns() { return WiFi.dnsIP().toString().c_str(); }

     const char* getprint_wifi_gateway() { return WiFi.gatewayIP().toString().c_str(); }

     const char* getprint_wifi_subnet() { return WiFi.subnetMask().toString().c_str(); }

}  // namespace WiFiUtils
