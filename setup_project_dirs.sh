#!/bin/bash

# プロジェクトのルートディレクトリ（任意で変更可）
ROOT_DIR="."

# ディレクトリリスト
DIRS=(
    "$ROOT_DIR/include/object"
    "$ROOT_DIR/include/scene"
    "$ROOT_DIR/include/system"
    "$ROOT_DIR/src/object"
    "$ROOT_DIR/src/scene"
    "$ROOT_DIR/src/system"
    "$ROOT_DIR/assets/images"
    "$ROOT_DIR/assets/sounds"
    "$ROOT_DIR/assets/stages"
    "$ROOT_DIR/third_party/json"
)

# ディレクトリ作成
for dir in "${DIRS[@]}"; do
    mkdir -p "$dir"
    echo "Created: $dir"
done

echo "✅ ディレクトリ構造の作成が完了しました。"

