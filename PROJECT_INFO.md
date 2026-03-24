# 📖 SpeedFetch Project Information

## About the Project

**SpeedFetch** is a fast and minimalist utility for displaying Linux system information with beautiful ASCII art of the distribution.

### How it differs from others?

| Feature | SpeedFetch | Neofetch | Fastfetch |
|---------|-----------|----------|-----------|
| Speed |  Lightning fast | Slow | Fast |
| Size |  < 200KB | Medium | Medium |
| Language | C++ | Bash | C |
| Minimal dependencies | ✅ Yes | ❌ No | ✅ Yes |
| ASCII arts | ✅ Yes | ✅ Yes | ✅ Yes |

## What is it for?

SpeedFetch is ideal for:
- Quick system information overview
- Beautiful terminal output (convenient for screenshots)
- Embedding in other applications
- Output to logs and reports

## Technical Specifications

- **Language:** C++17
- **Compiler:** GCC 7+ / Clang 5+
- **OS:** Linux (only)
- **Dependencies:** System utilities (uname, hostname, etc.)
- **Binary size:** ~150-200KB
- **Startup time:** < 100ms

## Collected Information

SpeedFetch collects the following system data:

1. **User@Host** - Current user and computer name
2. **OS** - Linux distribution
3. **Kernel** - System kernel version
4. **CPU** - Processor model
5. **RAM** - Used/Total RAM
6. **Disk** - Used/Total disk space
7. **Uptime** - System uptime
8. **Shell** - Current shell environment
9. **Terminal** - Terminal emulator

## Supported Distributions

- Ubuntu
- Fedora
- Debian
- Arch Linux
- Manjaro
- openSUSE
- CentOS
- Pop!_OS

## Project Files

```
speedfetch/
├── src/
│   ├── main.cpp              # Main program (UI and output)
│   ├── system_info.h/cpp     # System information gathering
│   └── ascii_art.h/cpp       # Distribution ASCII arts
├── CMakeLists.txt            # CMake configuration
├── Makefile                  # Make targets for convenience
├── README.md                 # Main documentation
├── USAGE.md                  # User guide
├── ASCII_ART_GUIDE.md        # How to add new ASCII arts
├── build.sh                  # Build script
└── install.sh                # Installation script
```

## How to Use

### Just run:
```bash
./build/speedfetch
```

### Install system-wide:
```bash
make install
speedfetch  # Anywhere
```

### Redirect to file:
```bash
speedfetch > system_info.txt
```

## Author and License

**Author:** MyNameIsV

**License:** GPL License

**Status:** Active development 🚀

---

**Last update:** 2026-03-22  
**Version:** 1.0  
**Platform:** Linux x86_64
