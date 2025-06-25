#include "news_view.h"

#include "../network/rss_reader.h"
#include "../system/display_instance.h"
#include "../system/view_controller.h"

namespace Views {

  void NewsView::render() {
    if (millis() - timeOfLastTitleChange >= 5000) {
      const char* headline = RSS::getNextHeadline();

      if (headline && headline[0] != '\0') {
        lcd.printWrapped(headline);
      }
      else {
        lcd.printAt("No headlines", 1);
      }

      timeOfLastTitleChange = millis();
    }
  }

  void NewsView::onSkip() {
    const char* headline = RSS::getNextHeadline();

    if (headline && headline[0] != '\0') {
      lcd.printWrapped(headline);
    }
    else {
      lcd.printAt("No headlines", 1);
    }
  }

}  // namespace Views
