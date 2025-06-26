#!/bin/bash

# プロジェクトルート
ROOT_DIR="."

# ファイル生成
declare -A FILES=(
    ["$ROOT_DIR/src/main.cpp"]="main.cpp"
    ["$ROOT_DIR/include/system/Application.hpp"]="Application.hpp"
    ["$ROOT_DIR/src/system/Application.cpp"]="Application.cpp"
    ["$ROOT_DIR/include/system/SceneManager.hpp"]="SceneManager.hpp"
    ["$ROOT_DIR/src/system/SceneManager.cpp"]="SceneManager.cpp"
    ["$ROOT_DIR/include/scene/Scene.hpp"]="Scene.hpp"
    ["$ROOT_DIR/include/scene/TitleScene.hpp"]="TitleScene.hpp"
    ["$ROOT_DIR/src/scene/TitleScene.cpp"]="TitleScene.cpp"
    ["$ROOT_DIR/include/scene/GameScene.hpp"]="GameScene.hpp"
    ["$ROOT_DIR/src/scene/GameScene.cpp"]="GameScene.cpp"
    ["$ROOT_DIR/CMakeLists.txt"]="CMakeLists.txt"
)

for path in "${!FILES[@]}"; do
    mkdir -p "$(dirname "$path")"
    touch "$path"
    echo "Created: $path"
done

echo "✅ 基本ファイルを作成しました。中身をこれから追加します。"
