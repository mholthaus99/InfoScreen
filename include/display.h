#include <Arduino.h>
#pragma once
void lcd_init();
void print(const char *message);
void printAt(const char *message, byte line);
void printAt(const char *message, byte line, byte col);
void printMultiLine(const char *message);
void printWrapped(const char *message);
void lcd_toggleBacklight();
void lcd_clear();

