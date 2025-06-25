#include <ESP8266WiFi.h>
#include "secrets.h"
#include "network.h"

// Replace these with your network credentials
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

/**
 * @brief Connects to the Wi-Fi network using the provided credentials.
 * 
 * Attempts to connect to the Wi-Fi network and provides status updates via the callback.
 * If connection fails after 40 attempts, notifies via callback and returns.
 * 
 * @param statusCallback Optional callback to report connection status messages.
 */
void wifi_connect(void (*statusCallback)(const char *))
{
  Serial.println("Connecting to Wi-Fi...");
  // if (statusCallback) statusCallback("Connecting to WiFi...");

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

    if (statusCallback)
    {
      statusCallback(statusMsg.c_str());
    }

    if (attempts > 40)
    {
      Serial.println("\nFailed to connect to WiFi.");
      if (statusCallback)
        statusCallback("WiFi Failed.");
      return;
    }
  }

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.dnsIP());

  statusMsg = "Connected!\n\nSSID:";
  statusMsg += WiFi.SSID();
  statusMsg += "\nIP:";
  statusMsg += WiFi.localIP().toString();

  if (statusCallback)
  {
    statusCallback("");
    statusCallback(statusMsg.c_str());

    // static char ipBuf[32];
    // snprintf(ipBuf, sizeof(ipBuf), "IP: %s", WiFi.localIP().toString().c_str());
    // statusCallback(ipBuf);
  }

  delay(2000); // Optional: let the user see the success message
}

/**
 * @brief Checks if the device is currently connected to Wi-Fi.
 * 
 * @return true if connected, false otherwise.
 */
bool wifi_isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

/**
 * @brief Gets the Wi-Fi SSID as a string.
 * 
 * @return Pointer to the SSID string.
 */
const char *getprint_wifi_ssid()
{
  return WIFI_SSID;
}

/**
 * @brief Gets the Wi-Fi password as a string.
 * 
 * @return Pointer to the password string.
 */
const char *getprint_wifi_password()
{
  return WIFI_PASS;
}

/**
 * @brief Gets the local IP address as a string.
 * 
 * @return Pointer to the IP address string.
 */
const char *getprint_wifi_ip()
{
  return WiFi.localIP().toString().c_str();
}

/**
 * @brief Gets the DNS server IP address as a string.
 * 
 * @return Pointer to the DNS IP address string.
 */
const char *getprint_wifi_dns()
{
  return WiFi.dnsIP().toString().c_str();
}

/**
 * @brief Gets the gateway IP address as a string.
 * 
 * @return Pointer to the gateway IP address string.
 */
const char *getprint_wifi_gateway()
{
  return WiFi.gatewayIP().toString().c_str();
}

/**
 * @brief Gets the subnet mask as a string.
 * 
 * @return Pointer to the subnet mask string.
 */
const char *getprint_wifi_subnet()
{
  return WiFi.subnetMask().toString().c_str();
}