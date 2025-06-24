#pragma once

void wifi_connect(void (*statusCallback)(const char*));
bool wifi_isConnected();

const char* getprint_wifi_ssid();
const char* getprint_wifi_password();
const char* getprint_wifi_ip();
const char* getprint_wifi_dns();
const char* getprint_wifi_gateway();
const char* getprint_wifi_subnet();