#!/bin/bash

# SpeedFetch Installation Script

if [ ! -f "build/speedfetch" ]; then
    echo "❌ Error: speedfetch binary not found!"
    echo "Please run './build.sh' first to compile the program."
    exit 1
fi

echo "📦 Installing SpeedFetch..."

if [ "$EUID" -ne 0 ]; then 
    echo "⚠️  This script requires root privileges for system-wide installation."
    echo "Run with: sudo $0"
    exit 1
fi

# Copy binary to system path
cp build/speedfetch /usr/local/bin/
chmod +x /usr/local/bin/speedfetch

echo "✅ SpeedFetch installed successfully!"
echo ""
echo "Usage: Just type 'speedfetch' in your terminal"
