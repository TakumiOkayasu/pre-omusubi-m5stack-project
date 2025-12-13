# M5Stack Project for Omusubi Framework

## Overview

M5Stack向けのomusubiフレームワーク実装。pre-omusubiのインターフェース定義に基づき、M5Stack固有の機能を提供する。

## Design Philosophy (設計思想)

pre-omusubiの設計思想に従う:

- **ゼロオーバーヘッド抽象化**: 動的メモリ確保なし、例外なし
- **クリーンアーキテクチャ**: SystemContextを中心としたDIパターン
- **インターフェースと実装の分離**: `*able`インターフェースと`m5stack*`実装

### Layer Structure

1. **Interface Layer** (pre-omusubi): `Displayable`, `Connectable`等の抽象インターフェース
2. **Context Layer** (pre-omusubi): `SystemContext`, `OutputContext`等のDIコンテナ
3. **Platform Layer** (このリポジトリ): `m5stackDisplayable`, `m5stackSystemContext`等のM5Stack実装

## Project Structure

```
m5stack-project/
├── include/           # ヘッダーファイル (自動生成、編集不可)
├── src/               # 実装ファイル (自動生成、編集不可)
├── example/           # サンプルプロジェクト
│   └── hello_world/   # Hello World表示サンプル
└── CLAUDE.md
```

## Dependencies

- [pre-omusubi](https://github.com/TakumiOkayasu/pre-omusubi): コアインターフェース定義
- [M5Unified](https://github.com/m5stack/M5Unified): M5Stack統合ライブラリ

## Build (example)

```bash
cd example/hello_world
pio run -e m5stack-core2      # Core2用ビルド
pio run -e m5stack-cores3     # CoreS3用ビルド
pio run -e m5stack-basic      # Basic/Gray用ビルド
```

## Code Style

- C++17準拠
- namespaceは`omusubi`を使用
- クラス名: `m5stack` + インターフェース名 (例: `m5stackDisplayable`)
- コピー・ムーブ禁止のシングルトンパターン

## Important Notes

- `include/`と`src/`のファイルは自動生成のため直接編集しない
- 新機能追加時はpre-omusubiのインターフェースに従う
- exampleは独立したPlatformIOプロジェクトとして構成
