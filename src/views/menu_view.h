#pragma once
#include <functional>
#include "../interfaces/IViewRenderer.h"
#include "../system/view_controller.h"
#include "view.h"

namespace Views {



  class FunctionView : public View {
  public:
    using SwitchViewCallback = std::function<void(DisplayMode)>;


    FunctionView(IViewRenderer& viewRenderer) : _renderer(viewRenderer) {}
    /**
     * @brief Set a callback function to be called when the view changes.
     * @param cb The callback to invoke
     */
    void setSwitchViewCallback(SwitchViewCallback cb);

    /**
     * @brief Draw the view upon entering the menu.
     */
    void onEnter() override;

    /**
     * @brief Handle IR back button by switching to default view.
     */
    void onBack() override;

    /**
     * @brief Handle digit presses to navigate to different views.
     */
    void onDigit(int digit) override;

    /**
     * @brief overridding on function while in the menu to close the menu.
     */
    void onFunction() override;

    void render() override;

  private:
    IViewRenderer& _renderer;
    SwitchViewCallback switchViewCallback = nullptr;
  };

}  // namespace Views
