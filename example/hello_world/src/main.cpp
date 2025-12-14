/**
 * @file main.cpp
 * @brief M5Stack Hello World Example
 *
 * M5Unifiedを使用したシンプルなHello World表示サンプル。
 */

#include <M5Unified.h>

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);

    // 画面設定
    M5.Display.fillScreen(TFT_BLACK);
    M5.Display.setTextSize(2);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);

    // 中央に表示
    const char* text = "Hello, World!";
    int x = (M5.Display.width() - M5.Display.textWidth(text)) / 2;
    int y = (M5.Display.height() - M5.Display.fontHeight()) / 2;
    M5.Display.setCursor(x, y);
    M5.Display.print(text);
}

void loop() {
    M5.update();
    delay(100);
}
