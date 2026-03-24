# SpeedFetch - Complete Documentation

A minimalistic and fast C++ utility for displaying Linux system information with beautiful ASCII art of your distribution.

---

## Table of Contents

1. [Quick Start](#quick-start)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Configuration](#configuration)
6. [Project Information](#project-information)
7. [Technical Details](#technical-details)
8. [Troubleshooting](#troubleshooting)
9. [Building from Source](#building-from-source)
10. [License](#license)

---

## Quick Start

### Run immediately:
```bash
./build/speedfetch
```

### Install system-wide:
```bash
make install
speedfetch  # Use from anywhere
```

### Build and run:
```bash
cd speedfetch
make build
make run
```

---

## Features

✅ **Fast** - Lightning-fast startup (< 100ms)  
✅ **Lightweight** - ~150-200KB binary, minimal dependencies  
✅ **Beautiful** - Colored ASCII art for 10+ distributions  
✅ **Informative** - Displays CPU, RAM, disk, shell, and more  
✅ **Configurable** - JSON config to show/hide fields  
✅ **Written in C++17** - Modern, efficient code  

### What It Shows

- User@Host
- Operating system and kernel version
- CPU, RAM, disk space, uptime
- Shell and terminal information
- Display/monitor info
- Desktop environment and theme settings
- Plus many more system details!

---

## Installation

### Requirements
- GCC/Clang compiler with C++17 support
- CMake 3.10 or higher
- Linux system
- make (optional, but recommended)

### Method 1: Using Makefile (Easiest)

```bash
cd speedfetch
make build      # Compile the program
make run        # Compile and run
make install    # Install to /usr/local/bin (requires sudo)
make clean      # Clean build directory
```

### Method 2: Using CMake

```bash
cd speedfetch
mkdir build
cd build
cmake ..
make
sudo make install  # Optional: install to system
```

### Method 3: Using Build Scripts

```bash
chmod +x build.sh install.sh
./build.sh              # Build
sudo ./install.sh       # Install
```

---

## Usage

### Basic Command
```bash
speedfetch
```

### Choose Custom Logo
```bash
speedfetch --logo-ubuntu      # Ubuntu
speedfetch --logo-arch        # Arch Linux
speedfetch --logo-fedora      # Fedora
speedfetch --logo-debian      # Debian
speedfetch --logo-manjaro     # Manjaro
speedfetch --logo-opensuse    # openSUSE
speedfetch --logo-centos      # CentOS
speedfetch --logo-elementary  # Elementary
speedfetch --logo-pop-os      # Pop!_OS
speedfetch --logo-tux         # Tux
speedfetch --logo-ubuntu-budgie # Ubuntu Budgie
```

### Redirect Output
```bash
speedfetch > system_info.txt
speedfetch | xclip -selection clipboard  # Copy to clipboard (requires xclip)
```

### Use in Scripts
```bash
#!/bin/bash
speedfetch > report.txt
./speedfetch | head -10
```

### Integrate into Shell
Add to `~/.bashrc` or `~/.bash_profile`:
```bash
echo "=== System Information ==="
speedfetch
```

---

## Configuration

SpeedFetch supports JSON configuration to customize which fields are displayed.

### Setup Configuration

Create the config directory and file:
```bash
mkdir -p ~/.config/speedfetch
cp config.example.json ~/.config/speedfetch/config.json
```

### Available Configuration Fields

```
user              - User@Host display
os                - Operating system
host              - Computer hostname
kernel            - Kernel version
uptime            - System uptime
packages          - Installed packages count
shell             - Shell and version
display           - Display resolution and refresh rate
de                - Desktop environment
wm                - Window manager
wm_theme          - Window manager theme
theme             - GTK theme
icons             - Icon theme
font              - System font
cursor            - Cursor theme
terminal          - Terminal emulator
terminal_font     - Terminal font
cpu               - CPU model and frequency
gpu               - Graphics processor
memory            - RAM usage
swap              - Swap memory usage
disk              - Disk usage
local_ip          - Local IP address
locale            - System locale
```

### Example: Minimal Configuration

Show only essential information:
```json
{
  "user": true,
  "os": true,
  "kernel": true,
  "uptime": true,
  "cpu": true,
  "memory": true,
  "disk": true,
  
  "host": false,
  "packages": false,
  "shell": false,
  "display": false,
  "de": false,
  "wm": false,
  "wm_theme": false,
  "theme": false,
  "icons": false,
  "font": false,
  "cursor": false,
  "terminal": false,
  "terminal_font": false,
  "gpu": false,
  "swap": false,
  "local_ip": false,
  "locale": false
}
```

### Default Behavior

If no configuration file is found, all fields are enabled by default.

---

## Project Information

### About SpeedFetch

**SpeedFetch** is ideal for:
- Quick system information overview
- Beautiful terminal output (convenient for screenshots)
- Embedding in other applications
- Output to logs and reports
- Learning C++17 programming

### Comparison with Similar Tools

| Feature | SpeedFetch | Neofetch | Fastfetch |
|---------|-----------|----------|-----------|
| Speed | ⚡ Lightning fast | Slow | Fast |
| Size | 🎯 < 200KB | Medium | Medium |
| Language | C++ | Bash | C |
| Minimal dependencies | ✅ Yes | ❌ No | ✅ Yes |
| ASCII arts | ✅ Yes | ✅ Yes | ✅ Yes |

### Supported Distributions

- Ubuntu (and variants like Budgie)
- Fedora
- Debian
- Arch Linux
- Manjaro
- openSUSE
- CentOS
- Elementary OS
- Pop!_OS
- And other Linux systems

---

## Technical Details

### Project Structure

```
speedfetch/
├── src/
│   ├── main.cpp              # Main program (UI and output)
│   ├── system_info.h/cpp     # System information gathering
│   ├── ascii_art.h/cpp       # Distribution ASCII arts
│   └── config.h/cpp          # Configuration system
├── debian/                   # Debian package files
├── CMakeLists.txt            # CMake configuration
├── Makefile                  # Make targets
├── build-deb.sh              # DEB package build script
├── build.sh                  # Build script
├── install.sh                # Installation script
├── DOCUMENTATION.md          # This file
├── config.example.json       # Example configuration
└── LICENSE                   # GNU GPLv3 license
```

### Collected System Information

1. **User@Host** - Current user and computer name
2. **OS** - Linux distribution name
3. **Kernel** - System kernel version
4. **CPU** - Processor model and frequency
5. **GPU** - Graphics processor information
6. **RAM** - Used/Total memory with percentage
7. **Swap** - Used/Total swap memory
8. **Disk** - Used/Total disk space for root partition
9. **Uptime** - How long the system has been running
10. **Shell** - Current shell and version
11. **Terminal** - Terminal emulator type
12. **Display** - Monitor resolution and refresh rate
13. **Desktop Environment** - GNOME, KDE, Xfce, etc.
14. **Window Manager** - Mutter, i3, openbox, etc.
15. **Themes** - GTK theme, icon theme, cursor theme
16. **And more!** - Font, locale, IP address, etc.

### Technical Specifications

- **Language:** C++17
- **Compiler:** GCC 7+ / Clang 5+
- **Build System:** CMake 3.10+
- **OS:** Linux (x86_64)
- **Binary Size:** ~150-200KB
- **Memory Usage:** < 1MB
- **Startup Time:** < 100ms
- **Dependencies:** Standard Linux utilities (uname, hostname, etc.)
- **License:** GNU GPLv3

### Performance Characteristics

- ⚡ **Startup time:** < 100ms
- 💾 **Memory usage:** < 1MB
- 🔧 **No external library dependencies** (except system utilities)
- 📦 **Small binary size** (~150KB)

---

## Troubleshooting

### Program doesn't compile

Make sure you have required packages:
```bash
sudo apt install build-essential cmake

# Then try again
make clean
make build
```

### Distribution not recognized correctly

Check your distribution info:
```bash
cat /etc/os-release
```

If the distribution is not detected, you may need to modify the `getDistroType()` function in `src/ascii_art.cpp`.

### Incorrect information output

Verify that standard Linux commands work on your system:
```bash
uname -r              # Should show kernel version
hostname              # Should show hostname
whoami                # Should show username
```

### Permission denied during installation

Use `sudo` for system-wide installation:
```bash
sudo make install
```

### Config file not being read

Ensure the configuration file is in the correct location:
```bash
~/.config/speedfetch/config.json
```

And verify the JSON syntax is valid:
```bash
cat ~/.config/speedfetch/config.json
```

---

## Building from Source

### Step 1: Clone the Repository

```bash
git clone https://github.com/MyNamesV/speedfetch.git
cd speedfetch
```

### Step 2: Build the Project

#### Option A: Using Makefile
```bash
make build
```

#### Option B: Using CMake
```bash
mkdir build
cd build
cmake ..
make
cd ..
```

#### Option C: Using Build Script
```bash
chmod +x build.sh
./build.sh
```

### Step 3: Run the Program

```bash
./build/speedfetch
```

### Step 4: Install (Optional)

```bash
sudo make install
# or
sudo ./install.sh
```

Now you can use `speedfetch` command from anywhere!

### Step 5: Create DEB Package (Optional)

```bash
./build-deb.sh
# Creates: speedfetch_1.0-1_amd64.deb

# Install the DEB package
sudo dpkg -i speedfetch_1.0-1_amd64.deb
```

---

## How to Extend

### Adding a New Distribution Logo

1. **Create the ASCII art** - Design your 45-character wide ASCII art
2. **Edit `src/ascii_art.cpp`** 
3. **Add to the `arts` map:**
```cpp
{"mydistro", R"(
    YOUR ASCII ART HERE
    45 characters max width
)"},
```
4. **Add detection in `getDistroType()`:**
```cpp
if (lower.find("mydistro") != std::string::npos) return "mydistro";
if (lower.find("mydistroname") != std::string::npos) return "mydistro";
```
5. **Recompile:** `make build`

### Contributing

Feel free to submit pull requests with:
- New distribution support
- ASCII art improvements
- Feature additions
- Bug fixes

---

## Command Reference

### Makefile Targets

```bash
make build                  # Compile the program
make run                    # Build and run
make install                # Install system-wide (requires sudo)
make uninstall              # Remove from system
make clean                  # Clean build artifacts
make help                   # Show help
```

### Program Options

```bash
speedfetch                  # Show with system's distribution logo
speedfetch --logo-DIST      # Show with specific distribution logo
speedfetch --help           # Show help message
speedfetch -h               # Show help message
```

---

## Frequently Asked Questions

**Q: Can I use this on non-Linux systems?**  
A: Not yet. The program is designed specifically for Linux.

**Q: How do I uninstall SpeedFetch?**  
A: Use `sudo make uninstall` or `sudo dpkg -r speedfetch` if installed via DEB.

**Q: Can I customize the output?**  
A: Yes! Use the `~/.config/speedfetch/config.json` file to enable/disable fields.

**Q: Which Linux distributions are supported?**  
A: All major distributions are supported. See the supported list above.

**Q: Can I add my custom distribution?**  
A: Yes! See the "How to Extend" section above.

**Q: Is there a dark mode or light mode?**  
A: The colors are determined by your terminal theme. SpeedFetch uses standard terminal colors.

---

## License

SpeedFetch is licensed under the **GNU General Public License v3.0 (GPLv3)**.

This means:
- ✅ You can freely use, modify, and distribute this software
- ✅ You must include the license when distributing
- ✅ Any modifications must also be open source under GPLv3
- ℹ️ See LICENSE file for full details

---

## Links and Resources

- **GitHub Repository:** https://github.com/MyNamesV/speedfetch
- **Issues:** https://github.com/MyNamesV/speedfetch/issues
- **License:** GNU GPLv3 (see LICENSE file)

## Author

**MyNameIsV**

---

## Credits

- Built with C++17
- Uses system utilities for information gathering
- ASCII art inspired by neofetch and fastfetch
- Community contributions welcome!

---

## Changelog

### Version 1.0 (Current)
- Initial release
- Support for 10+ Linux distributions
- JSON configuration system
- DEB package support
- Full English documentation
- Colored ASCII art logos

---

**Last Updated:** March 24, 2026  
**Version:** 1.0  
**Status:** Stable

Enjoy using SpeedFetch! 🚀
