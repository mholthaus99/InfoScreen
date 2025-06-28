#pragma once
// Abstract base class
#include "../interfaces/IViewRenderer.h"
class View
{
public:
     virtual ~View() {}

     // Called when the view is shown (optional)
     virtual void onEnter() {}

     // Called when the view is hidden (optional)
     virtual void onExit() {}

     // IR event handlers - override in subclasses
     virtual void onPower() {}
     virtual void onDigit(int digit) {}
     virtual void onFunction()
     {
          // ModeManager::setMode(MODE_DEFAULT);
     }
     virtual void onSkip() {}
     virtual void onBack() {}
     virtual void onVolumeUp() {}
     virtual void onVolumeDown() {}
     virtual void onChannelUp() {}
     virtual void onChannelDown() {}
     virtual void onPlayPause() {}
     virtual void onEQ() {}
     virtual void onRepeat() {}

     // Render the view
     virtual void render() = 0;

     void setViewController(IViewRenderer* viewRenderer)
     {
          _viewRenderer = viewRenderer;
     }
protected:
     IViewRenderer* _viewRenderer = nullptr; // Pointer to the view renderer managing this view
};
