#!/bin/sh
# Builds both versions of the project.
#   1. Command-line program ->  ./textool          (needs g++)
#   2. Web version          ->  docs/textool.js and docs/textool.wasm   (needs Emscripten: emcc)
set -e

echo "Building command-line version..."
g++ -std=c++11 -Wall -Wextra -o textool main.cpp core.cpp

if command -v emcc >/dev/null 2>&1; then
    echo "Building WebAssembly version..."
    emcc -std=c++11 -O2 --bind \
        -s MODULARIZE=1 -s EXPORT_NAME=createTextool -s ENVIRONMENT=web \
        -o docs/textool.js wasm_bridge.cpp core.cpp
    echo "Done: docs/textool.js and docs/textool.wasm"
else
    echo "emcc (Emscripten) not found - skipped the web version."
    echo "Install Emscripten, then run this script again."
fi
