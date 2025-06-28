#include "news_view.h"

  void NewsView::render() {
    if (millis() - timeOfLastTitleChange >= 5000) {
      const char* headline = RSS::getNextHeadline();

      if (headline && headline[0] != '\0') {
        _viewRenderer->drawWrap(headline);
      }
      else {
        _viewRenderer->drawText(0, "no headlines");
      }

      timeOfLastTitleChange = millis();
    }
  }

  void NewsView::onSkip() {
    const char* headline = RSS::getNextHeadline();

    if (headline && headline[0] != '\0') {
      _viewRenderer->drawWrap(headline);
    }
    else {
      _viewRenderer->drawText(0, "no headlines");
    }
  }
