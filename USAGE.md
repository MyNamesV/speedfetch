# SpeedFetch Usage Guide

## Quick Start

### First Build

```bash
cd speedfetch
make build

# Or via script
./build.sh
```

### First Run

```bash
# From build folder
./build/speedfetch

# Or via make
make run
```

### System Installation (optional)

```bash
# Via make
make install

# Or via script
sudo ./install.sh
```

## Usage Examples

After installation, you can use it in various contexts:

### In .bash_profile or .bashrc

Add to the end of the file:
```bash
echo "System Info:"
speedfetch
```

Now speedfetch will be displayed when opening a new terminal.

### In scripts

```bash
#!/bin/bash
speedfetch > system_info.txt
```

### Integration with other applications

SpeedFetch can be redirected to a file:
```bash
speedfetch > report.txt
speedfetch | xclip -selection clipboard  # Copy to clipboard
```

## Program Features

**Speed** - written in C++, starts instantly
**Minimal dependencies** - uses only standard Linux utilities
**Complete information** - collects main system parameters
**Beautiful output** - supports colors and terminal formatting
**Easy extensibility** - just add new ASCII art!

## Troubleshooting

### Program doesn't compile
```bash
# Make sure necessary packages are installed
sudo apt install build-essential cmake

# Clean old build
make clean
make build
```

### Distribution not recognized correctly
Check `/etc/os-release`:
```bash
cat /etc/os-release
```

If the distribution was identified incorrectly, add a check in `system_info.cpp`.

### Incorrect information output
Make sure standard commands work on your system:
```bash
uname -r              # Kernel version
hostname             # Host name
whoami               # Current user
```

## Performance

SpeedFetch is a very fast program:
- Startup time: < 100ms
- Memory usage: < 1MB
- No additional dependencies

## License

MIT License - see LICENSE file for details

---

**Version:** 1.0  
**Platform:** Linux only  
**Language:** C++17
