#pragma once
#include "view.h"

namespace Views {

/**
 * @brief A view that presents a menu of selectable functions.
 */
class FunctionView : public View
{
public:
    using SwitchViewCallback = void (*)(DisplayMode); ///< Function pointer type for view switching

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
    SwitchViewCallback switchViewCallback = nullptr;
};

}  // namespace Views
