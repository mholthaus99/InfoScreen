#include "news_view.h"

void NewsView::render() {
    if (millis() - timeOfLastTitleChange >= 5000) {
        drawNextHeadline();
        timeOfLastTitleChange = millis();
    }
}

void NewsView::onSkip() {
    drawNextHeadline();
}

void NewsView::drawNextHeadline() {
    const char* headline = RSS::getNextHeadline();

    if (headline && headline[0] != '\0') {
        _viewRenderer->drawWrap(headline);
    } else {
        _viewRenderer->drawText(0, "no headlines");
    }
}