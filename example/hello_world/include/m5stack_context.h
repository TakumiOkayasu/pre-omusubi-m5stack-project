/**
 * @file M5Stack_context.h
 * @brief M5Stack platform context declarations for omusubi framework
 *
 * This header provides declarations for M5Stack-specific implementations
 * of the omusubi framework contexts.
 */

#pragma once

#include <omusubi/interface/displayable.h>
#include <omusubi/context/output_context.h>
#include <omusubi/system_context.h>

namespace omusubi {

/**
 * @brief M5Stack implementation of Displayable interface
 */
class M5StackDisplayable : public Displayable {
public:
    M5StackDisplayable() = default;
    ~M5StackDisplayable() noexcept override = default;

    M5StackDisplayable(const M5StackDisplayable&) = delete;
    M5StackDisplayable& operator=(const M5StackDisplayable&) = delete;
    M5StackDisplayable(M5StackDisplayable&&) = delete;
    M5StackDisplayable& operator=(M5StackDisplayable&&) = delete;

    void display(std::string_view text) override;
};

/**
 * @brief M5Stack implementation of OutputContext
 *
 * Provides access to display output device.
 */
class M5StackOutputContext : public OutputContext {
public:
    M5StackOutputContext() = default;
    ~M5StackOutputContext() noexcept override = default;

    M5StackOutputContext(const M5StackOutputContext&) = delete;
    M5StackOutputContext& operator=(const M5StackOutputContext&) = delete;
    M5StackOutputContext(M5StackOutputContext&&) = delete;
    M5StackOutputContext& operator=(M5StackOutputContext&&) = delete;

    /**
     * @brief Get the display interface
     * @return Reference to the Displayable implementation
     */
    Displayable& get_display();

private:
    M5StackDisplayable display_;
};

/**
 * @brief M5Stack implementation of SystemContext
 *
 * Provides the main entry point for M5Stack system initialization
 * and context access following the DI pattern.
 */
class M5StackSystemContext : public SystemContext {
public:
    M5StackSystemContext() = default;
    ~M5StackSystemContext() noexcept override = default;

    M5StackSystemContext(const M5StackSystemContext&) = delete;
    M5StackSystemContext& operator=(const M5StackSystemContext&) = delete;
    M5StackSystemContext(M5StackSystemContext&&) = delete;
    M5StackSystemContext& operator=(M5StackSystemContext&&) = delete;

    void begin() override;
    void update() override;
    void delay(uint32_t ms) override;
    void reset() override;

    /**
     * @brief Get the output context
     * @return Reference to the M5Stack output context
     */
    M5StackOutputContext& get_output_context();

    // Base class context accessors (placeholder implementations)
    ConnectableContext& get_connectable_context() const override;
    ScannableContext& get_scannable_context() const override;
    SensorContext& get_sensor_context() const override;
    InputContext& get_input_context() const override;
    SystemInfoContext& get_system_info_context() const override;
    PowerContext& get_power_context() const override;

private:
    M5StackOutputContext output_context_;
};

/**
 * @brief Get the global M5Stack system context instance
 * @return Reference to the system context
 */
M5StackSystemContext& get_system_context();

} // namespace omusubi
