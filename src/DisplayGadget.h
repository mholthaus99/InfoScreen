#pragma once

#include "interfaces/IViewRenderer.h"
#include "interfaces/IInputDevice.h"
#include "interfaces/IView.h"
#include "system/controller.h"

class DisplayGadget {
public:
     DisplayGadget(IViewRenderer& renderer, IInputDevice& input);
     void addView(View* view);
     void loop();

private:
     Controller _controller;
};
