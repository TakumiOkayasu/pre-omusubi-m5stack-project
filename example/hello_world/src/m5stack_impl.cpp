/**
 * @file m5stack_impl.cpp
 * @brief M5Stack platform implementation for omusubi framework
 *
 * This file provides the M5Stack-specific implementations:
 * - m5stackDisplayable: Display output using M5Unified
 * - m5stackOutputContext: Output context with display access
 * - m5stackSystemContext: System context with M5Stack initialization
 * - get_system_context(): Global access to system context
 */

#include "m5stack_context.h"
#include <M5Unified.h>

namespace omusubi {

// =============================================================================
// m5stackDisplayable Implementation
// =============================================================================

void m5stackDisplayable::display(std::string_view text) {
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
// m5stackOutputContext Implementation
// =============================================================================

Displayable& m5stackOutputContext::get_display() {
    return display_;
}

// =============================================================================
// m5stackSystemContext Implementation
// =============================================================================

void m5stackSystemContext::begin() {
    auto cfg = M5.config();
    M5.begin(cfg);
}

void m5stackSystemContext::update() {
    M5.update();
}

void m5stackSystemContext::delay(uint32_t ms) {
    ::delay(ms);
}

void m5stackSystemContext::reset() {
    ESP.restart();
}

m5stackOutputContext& m5stackSystemContext::get_output_context() {
    return output_context_;
}

ConnectableContext& m5stackSystemContext::get_connectable_context() const {
    static ConnectableContext ctx;
    return ctx;
}

ScannableContext& m5stackSystemContext::get_scannable_context() const {
    static ScannableContext ctx;
    return ctx;
}

SensorContext& m5stackSystemContext::get_sensor_context() const {
    static SensorContext ctx;
    return ctx;
}

InputContext& m5stackSystemContext::get_input_context() const {
    static InputContext ctx;
    return ctx;
}

SystemInfoContext& m5stackSystemContext::get_system_info_context() const {
    static SystemInfoContext ctx;
    return ctx;
}

PowerContext& m5stackSystemContext::get_power_context() const {
    static PowerContext ctx;
    return ctx;
}

// =============================================================================
// Global System Context
// =============================================================================

static m5stackSystemContext g_system_context;

m5stackSystemContext& get_system_context() {
    return g_system_context;
}

} // namespace omusubi
