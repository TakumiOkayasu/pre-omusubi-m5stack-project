/**
 * @file main.cpp
 * @brief M5Stack Hello World Example (pre-omusubi形式)
 *
 * pre-omusubiのSystemContext/Displayableインターフェースを使用した
 * Hello World表示サンプル。
 */

#include <omusubi/omusubi.h>
#include <omusubi/core/format.hpp>
#include <M5Unified.h>

// ArduinoのEXTERNALマクロをundefしてpre-omusubiのPowerState::EXTERNALを優先
#undef EXTERNAL

using namespace std::literals;

namespace omusubi::m5stack {

// ============================================================================
// M5Stack Displayable 実装
// ============================================================================
class M5StackDisplayable : public Displayable {
public:
    M5StackDisplayable() = default;
    ~M5StackDisplayable() noexcept override = default;
    M5StackDisplayable(const M5StackDisplayable&) = delete;
    M5StackDisplayable& operator=(const M5StackDisplayable&) = delete;
    M5StackDisplayable(M5StackDisplayable&&) = delete;
    M5StackDisplayable& operator=(M5StackDisplayable&&) = delete;

    void display(std::string_view text) override {
        M5.Display.fillScreen(TFT_BLACK);
        M5.Display.setFont(&fonts::efontJA_16);  // 日本語フォント
        M5.Display.setTextSize(1);
        M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);

        int x = (M5.Display.width() - M5.Display.textWidth(text.data())) / 2;
        int y = (M5.Display.height() - M5.Display.fontHeight()) / 2;
        M5.Display.setCursor(x, y);
        M5.Display.print(text.data());
    }
};

// ============================================================================
// M5Stack Context 実装（簡易版）
// ============================================================================
class M5StackSystemContext : public SystemContext {
public:
    M5StackSystemContext() = default;
    ~M5StackSystemContext() noexcept override = default;
    M5StackSystemContext(const M5StackSystemContext&) = delete;
    M5StackSystemContext& operator=(const M5StackSystemContext&) = delete;
    M5StackSystemContext(M5StackSystemContext&&) = delete;
    M5StackSystemContext& operator=(M5StackSystemContext&&) = delete;

    void begin() override {
        auto cfg = M5.config();
        M5.begin(cfg);
    }

    void update() override {
        M5.update();
    }

    void delay(uint32_t ms) override {
        ::delay(ms);
    }

    void reset() override {
        ESP.restart();
    }

    // 以下は未実装（Hello Worldでは使用しない）
    [[nodiscard]] ConnectableContext& get_connectable_context() const override {
        static ConnectableContext* dummy = nullptr;
        return *dummy; // TODO: 実装
    }

    [[nodiscard]] ScannableContext& get_scannable_context() const override {
        static ScannableContext* dummy = nullptr;
        return *dummy; // TODO: 実装
    }

    [[nodiscard]] SensorContext& get_sensor_context() const override {
        return sensor_context_;
    }

    [[nodiscard]] InputContext& get_input_context() const override {
        return input_context_;
    }

    [[nodiscard]] OutputContext& get_output_context() const override {
        return output_context_;
    }

    [[nodiscard]] SystemInfoContext& get_system_info_context() const override {
        static SystemInfoContext* dummy = nullptr;
        return *dummy; // TODO: 実装
    }

    [[nodiscard]] PowerContext& get_power_context() const override {
        static PowerContext* dummy = nullptr;
        return *dummy; // TODO: 実装
    }

    // Hello World用の追加メソッド
    [[nodiscard]] Displayable& get_displayable() {
        return displayable_;
    }

private:
    mutable M5StackDisplayable displayable_;
    mutable SensorContext sensor_context_;
    mutable InputContext input_context_;
    mutable OutputContext output_context_;
};

// グローバルSystemContext
static M5StackSystemContext system_context;

SystemContext& get_system_context() {
    return system_context;
}

M5StackSystemContext& get_m5stack_context() {
    return system_context;
}

} // namespace omusubi::m5stack

auto& context = omusubi::m5stack::get_m5stack_context();


void setup() {
    context.begin();

    context.get_displayable()
            .display(
                omusubi::format("{}\n{:X}\n{:d}\n{}",
                                "Hello, Omusubi World!"sv,
                                42,
                                1145141919810,
                                "イフェクサー"sv
                )
            );
}

void loop() {
    context.update();
    context.delay(100);
}
