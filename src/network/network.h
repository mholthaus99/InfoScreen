#pragma once

namespace WiFiUtils
{
    /**
     * @file network.h
     * @brief Wi-Fi connection utilities for ESP8266.
     */

    /// @brief Connect to Wi-Fi with status updates via callback.
    void wifi_connect(void (*statusCallback)(const char *));

    /// @brief Returns whether Wi-Fi is connected.
    bool wifi_isConnected();

    /// @brief Returns current Wi-Fi SSID.
    const char *getprint_wifi_ssid();

    /// @brief Returns current Wi-Fi password.
    const char *getprint_wifi_password();

    /// @brief Returns device's local IP.
    const char *getprint_wifi_ip();

    /// @brief Returns DNS server IP.
    const char *getprint_wifi_dns();

    /// @brief Returns default gateway IP.
    const char *getprint_wifi_gateway();

    /// @brief Returns subnet mask.
    const char *getprint_wifi_subnet();
}