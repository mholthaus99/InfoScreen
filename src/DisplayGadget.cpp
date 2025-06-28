#include "DisplayGadget.h"

DisplayGadget::DisplayGadget(IViewRenderer& renderer, IInputDevice& input)
     : _controller(renderer, input) {
}

void DisplayGadget::addView(View* view) {
     _controller.addView(view);
}

void DisplayGadget::loop() {
     _controller.loop();
}
