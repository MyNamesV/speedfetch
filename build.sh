#!/bin/bash

# SpeedFetch Build and Install Script

echo "🚀 Building SpeedFetch..."

# Check if build directory exists
if [ -d "build" ]; then
    echo "Cleaning previous build..."
    rm -rf build
fi

# Create build directory
mkdir build
cd build

# Run CMake and Make
echo "Running CMake..."
cmake ..

echo "Compiling..."
make

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Build successful!"
    echo ""
    echo "Usage:"
    echo "  ./build/speedfetch              # Run speedfetch"
    echo "  make install                    # Install to system (requires sudo)"
    echo ""
    echo "To add to PATH:"
    echo "  sudo cp ./speedfetch /usr/local/bin/"
    echo ""
else
    echo "❌ Build failed!"
    exit 1
fi
