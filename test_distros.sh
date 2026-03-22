#!/bin/bash

# Test ASCII art widths
echo "Unicode widths of different ASCII arts:"
echo "========================================"
echo ""

grep -A 50 '"ubuntu"' src/ascii_art.cpp | head -25 | wc -L && echo " Ubuntu art max width"
grep -A 5 '"fedora"' src/ascii_art.cpp | head -7 | wc -L && echo " Fedora art max width"
grep -A 5 '"arch"' src/ascii_art.cpp | head -8 | wc -L && echo " Arch art max width"
