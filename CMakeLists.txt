cmake_minimum_required(VERSION 3.10)
project(STG)

set(CMAKE_CXX_STANDARD 17)

# ソースファイル
file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include)

# JSONライブラリのインクルード
include_directories(third_party/json)

# SDL2とSDL2_ttfをpkg-configで探す
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})
link_directories(${SDL2_TTF_LIBRARY_DIRS})

# 実行ファイル作成
add_executable(STG ${SOURCES})

# ライブラリリンク
target_link_libraries(STG
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
