/**
 * @file m5stack_context.h
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
class m5stackDisplayable : public Displayable {
public:
    m5stackDisplayable() = default;
    ~m5stackDisplayable() noexcept override = default;

    m5stackDisplayable(const m5stackDisplayable&) = delete;
    m5stackDisplayable& operator=(const m5stackDisplayable&) = delete;
    m5stackDisplayable(m5stackDisplayable&&) = delete;
    m5stackDisplayable& operator=(m5stackDisplayable&&) = delete;

    void display(std::string_view text) override;
};

/**
 * @brief M5Stack implementation of OutputContext
 *
 * Provides access to display output device.
 */
class m5stackOutputContext : public OutputContext {
public:
    m5stackOutputContext() = default;
    ~m5stackOutputContext() noexcept override = default;

    m5stackOutputContext(const m5stackOutputContext&) = delete;
    m5stackOutputContext& operator=(const m5stackOutputContext&) = delete;
    m5stackOutputContext(m5stackOutputContext&&) = delete;
    m5stackOutputContext& operator=(m5stackOutputContext&&) = delete;

    /**
     * @brief Get the display interface
     * @return Reference to the Displayable implementation
     */
    Displayable& get_display();

private:
    m5stackDisplayable display_;
};

/**
 * @brief M5Stack implementation of SystemContext
 *
 * Provides the main entry point for M5Stack system initialization
 * and context access following the DI pattern.
 */
class m5stackSystemContext : public SystemContext {
public:
    m5stackSystemContext() = default;
    ~m5stackSystemContext() noexcept override = default;

    m5stackSystemContext(const m5stackSystemContext&) = delete;
    m5stackSystemContext& operator=(const m5stackSystemContext&) = delete;
    m5stackSystemContext(m5stackSystemContext&&) = delete;
    m5stackSystemContext& operator=(m5stackSystemContext&&) = delete;

    void begin() override;
    void update() override;
    void delay(uint32_t ms) override;
    void reset() override;

    /**
     * @brief Get the output context
     * @return Reference to the M5Stack output context
     */
    m5stackOutputContext& get_output_context();

    // Base class context accessors (placeholder implementations)
    ConnectableContext& get_connectable_context() const override;
    ScannableContext& get_scannable_context() const override;
    SensorContext& get_sensor_context() const override;
    InputContext& get_input_context() const override;
    SystemInfoContext& get_system_info_context() const override;
    PowerContext& get_power_context() const override;

private:
    m5stackOutputContext output_context_;
};

/**
 * @brief Get the global M5Stack system context instance
 * @return Reference to the system context
 */
m5stackSystemContext& get_system_context();

} // namespace omusubi
