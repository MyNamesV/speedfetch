# SpeedFetch - System Information Fetcher

Minimalistic and fast C++ program for displaying your Linux system information with beautiful ASCII art of the distribution.

## Features

- Fast system information output
- Support for major Linux distributions (Ubuntu, Fedora, Debian, Arch, Manjaro, openSUSE, etc.)
- Beautiful ASCII art for each distribution
- User and hostname
- Operating system
- Kernel version
- Processor
- RAM
- Free disk space
- System uptime
- Shell and terminal

## Building

### Requirements:
- GCC/Clang compiler with C++17 support
- CMake 3.10 or higher
- Linux system
- make (optional, but recommended)

### Quick build (with Makefile):

```bash
cd speedfetch
make build      # Compiles the program
make run        # Compiles and runs
make install    # Installs to system (requires sudo)
make clean      # Removes build directory
```

### Manual build (via CMake):

```bash
cd speedfetch
mkdir build
cd build
cmake ..
make
./speedfetch
```

### Using scripts:

```bash
# Give execute permissions
chmod +x build.sh install.sh

# Build
./build.sh

# Install (requires sudo)
sudo ./install.sh
```

## Usage

### Running from build folder:
```bash
./build/speedfetch
```

### After system installation:
```bash
speedfetch
```

Just run the program in any folder!

## Project Structure

```
speedfetch/
├── CMakeLists.txt          # CMake configuration
├── src/
│   ├── main.cpp            # Main program
│   ├── system_info.h       # Header for information gathering
│   ├── system_info.cpp     # Implementation of information gathering
│   ├── ascii_art.h         # Header for ASCII arts
│   └── ascii_art.cpp       # Implementation of ASCII arts
└── README.md               # This file
```

## Supported Distributions

- Ubuntu
- Fedora
- Debian
- Arch Linux
- Manjaro
- openSUSE
- CentOS
- Pop!_OS

## About the program

SpeedFetch is written in pure C++ with minimal dependencies. The program uses system files `/proc` and standard Linux commands to obtain system information.

## License

GNU GPLv3

---

**Author:** MyNameIsV
