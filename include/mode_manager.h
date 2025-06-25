#pragma once
#include "display.h"

enum DisplayMode {
  MODE_DEFAULT,
  MODE_NETWORK,
  MODE_MENU,
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
