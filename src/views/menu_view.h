#include "../system/view_controller.h"  // or wherever it's defined
#include "../interfaces/IViewRenderer.h"
#include "view.h"
#include <Arduino.h>
#include <functional>


  class FunctionView : public View {
  public:
    using SwitchViewCallback = std::function<void(int)>;

    void setSwitchViewCallback(SwitchViewCallback callback) {
        _switchViewCallback = callback;
    }

   

    void onEnter() override;
    void onBack() override;
    void onFunction() override;
    void onDigit(int digit) override;
    void render() override;



  private:

    void setViewControllerIndex(int index) {
      if (_switchViewCallback) {
        _switchViewCallback(index);
      }
    }
    
    SwitchViewCallback _switchViewCallback; // Callback to switch views
  };


