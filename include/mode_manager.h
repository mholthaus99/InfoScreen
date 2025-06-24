#pragma once
#include "display.h"

enum DisplayMode {
  MODE_DEFAULT,
  MODE_WEATHER,
  MODE_CLIMATE,
  MODE_INFO,
  MODE_FUNC,
  MODE_NEWS,
  MODE_COUNT
};

class ModeManager {
public:
  void markUpdated();
  void flagForUpdate(DisplayMode mode);
  bool shouldUpdate(DisplayMode mode);
  void flagForSkip();

  DisplayMode lastMode = MODE_COUNT;
  bool needsUpdateFlag = true;
};

extern ModeManager displayMgr;
extern DisplayMode currentMode;

void setMode(DisplayMode mode);
