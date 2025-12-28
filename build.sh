#!/bin/bash
# Build script for Playfair Cipher
# Usage: ./build.sh

# Create build directory if it doesn't exist
mkdir -p build

# Compile with g++
echo "Compiling Playfair Cipher..."
g++ -o build/playfair src/playfair.cpp -std=c++11 -O2

if [ $? -eq 0 ]; then
    echo "✓ Build successful! Executable: build/playfair"
else
    echo "✗ Build failed!"
    exit 1
fi

