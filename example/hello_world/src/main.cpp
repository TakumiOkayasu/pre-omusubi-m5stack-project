/**
 * @file main.cpp
 * @brief M5Stack Hello World Example
 *
 * This example demonstrates the omusubi framework's design philosophy:
 * - SystemContext as the central DI container
 * - Displayable interface for display output
 * - Clean separation of interface and implementation
 *
 * The application uses the DI pattern to obtain the system context,
 * then accesses the display through the output context.
 */

#include "M5Stack_context.h"

using namespace omusubi;

void setup() {
    // Get the system context (DI container)
    auto& ctx = get_system_context();

    // Initialize the system
    ctx.begin();

    // Get display interface from output context and display message
    auto& output = ctx.get_output_context();
    auto& display = output.get_display();

    display.display("Hello, World!");
}

void loop() {
    // Get the system context
    auto& ctx = get_system_context();

    // Update system state
    ctx.update();

    // Delay to prevent busy loop
    ctx.delay(100);
}
