/**
 * @file M5Stack_impl.cpp
 * @brief M5Stack platform implementation for omusubi framework
 *
 * This file provides the M5Stack-specific implementations:
 * - M5StackDisplayable: Display output using M5Unified
 * - M5StackOutputContext: Output context with display access
 * - M5StackSystemContext: System context with M5Stack initialization
 * - get_system_context(): Global access to system context
 */

#include "M5Stack_context.h"
#include <M5Unified.h>

namespace omusubi {

// =============================================================================
// M5StackDisplayable Implementation
// =============================================================================

void M5StackDisplayable::display(std::string_view text) {
    // Clear screen and set up display
    M5.Display.fillScreen(TFT_BLACK);
    M5.Display.setTextSize(2);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);

    // Calculate center position
    int displayWidth = M5.Display.width();
    int displayHeight = M5.Display.height();
    int textWidth = M5.Display.textWidth(text.data());
    int textHeight = M5.Display.fontHeight();
    int x = (displayWidth - textWidth) / 2;
    int y = (displayHeight - textHeight) / 2;

    // Display the text
    M5.Display.setCursor(x, y);
    M5.Display.print(text.data());
}

// =============================================================================
// M5StackOutputContext Implementation
// =============================================================================

Displayable& M5StackOutputContext::get_display() {
    return display_;
}

// =============================================================================
// M5StackSystemContext Implementation
// =============================================================================

void M5StackSystemContext::begin() {
    auto cfg = M5.config();
    M5.begin(cfg);
}

void M5StackSystemContext::update() {
    M5.update();
}

void M5StackSystemContext::delay(uint32_t ms) {
    ::delay(ms);
}

void M5StackSystemContext::reset() {
    ESP.restart();
}

M5StackOutputContext& M5StackSystemContext::get_output_context() {
    return output_context_;
}

ConnectableContext& M5StackSystemContext::get_connectable_context() const {
    static ConnectableContext ctx;
    return ctx;
}

ScannableContext& M5StackSystemContext::get_scannable_context() const {
    static ScannableContext ctx;
    return ctx;
}

SensorContext& M5StackSystemContext::get_sensor_context() const {
    static SensorContext ctx;
    return ctx;
}

InputContext& M5StackSystemContext::get_input_context() const {
    static InputContext ctx;
    return ctx;
}

SystemInfoContext& M5StackSystemContext::get_system_info_context() const {
    static SystemInfoContext ctx;
    return ctx;
}

PowerContext& M5StackSystemContext::get_power_context() const {
    static PowerContext ctx;
    return ctx;
}

// =============================================================================
// Global System Context
// =============================================================================

static M5StackSystemContext g_system_context;

M5StackSystemContext& get_system_context() {
    return g_system_context;
}

} // namespace omusubi
