# omusubi-m5stack

M5Stack platform implementation for the [omusubi](https://github.com/TakumiOkayasu/pre-omusubi) framework.

## Features

- M5Stack向けのomusubiフレームワーク実装
- M5Unified対応（Core2, CoreS3, Basic/Gray等）
- DIパターンによるクリーンアーキテクチャ

## Requirements

- [PlatformIO](https://platformio.org/)
- M5Stack デバイス (Core2, CoreS3, Basic, Gray等)

## Installation

`platformio.ini`に以下を追加:

```ini
lib_deps =
    m5stack/M5Unified@^0.1.17
    https://github.com/TakumiOkayasu/pre-omusubi.git
```

## Quick Start

```cpp
#include "m5stack_context.h"

using namespace omusubi;

void setup() {
    auto& ctx = get_system_context();
    ctx.begin();

    auto& display = ctx.get_output_context().get_display();
    display.display("Hello, World!");
}

void loop() {
    auto& ctx = get_system_context();
    ctx.update();
    ctx.delay(100);
}
```

## Examples

### Hello World

```bash
cd example/hello_world
pio run -e m5stack-core2 -t upload
```

## Architecture

```
┌─────────────────────────────────────┐
│           Application               │
├─────────────────────────────────────┤
│  SystemContext (DI Container)       │
│    ├── OutputContext                │
│    │     └── Displayable            │
│    ├── InputContext                 │
│    ├── SensorContext                │
│    └── ...                          │
├─────────────────────────────────────┤
│  pre-omusubi (Interface Layer)      │
├─────────────────────────────────────┤
│  M5Unified / ESP-IDF                │
└─────────────────────────────────────┘
```

## Supported Devices

| Device | Environment | Status |
|--------|-------------|--------|
| M5Stack Core2 | `m5stack-core2` | Supported |
| M5Stack CoreS3 | `m5stack-cores3` | Supported |
| M5Stack Basic/Gray | `m5stack-basic` | Supported |

## License

MIT

## Related Projects

- [pre-omusubi](https://github.com/TakumiOkayasu/pre-omusubi) - Core interface definitions
