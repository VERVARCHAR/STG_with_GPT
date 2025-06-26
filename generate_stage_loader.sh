#!/bin/bash

mkdir -p include/system src/system assets/stages

touch include/system/StageLoader.hpp
touch src/system/StageLoader.cpp
touch assets/stages/stage1.json

echo "✅ StageLoader.hpp / .cpp / JSON を作成しました！"
