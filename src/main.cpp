
#include <Arduino.h>

#include "system/controller.h"

Controller controller;

void setup() { controller.init(); }

void loop() { controller.loop(); }