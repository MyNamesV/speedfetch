#pragma once

#include <string>
#include <vector>
#include "os.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"
#include "disk.h"
#include "battery.h"
#include "network.h"
#include "packages.h"
#include "shell.h"
#include "terminal.h"

struct SystemInformation {
    // User & System
    std::string user;
    std::string hostname;
    std::string os_name;
    std::string os_version;
    std::string kernel;
    std::string arch;
    std::string uptime;
    
    // Desktop Environment
    std::string desktop_env;
    std::string window_manager;
    std::string wm_theme;
    std::string theme;
    std::string icons;
    std::string font;
    std::string cursor;
    std::string display;
    
    // Shell & Terminal
    std::string shell;
    std::string terminal;
    std::string terminal_font;
    
    // Hardware
    std::string cpu;
    std::string gpu;
    std::string memory;
    std::string swap;
    std::string disk;
    std::string battery;
    
    // Network & Locale
    std::string ip_address;
    std::string locale;
    std::string packages;
};

class SystemInfoGatherer {
public:
    static SystemInformation gatherAll() {
        SystemInformation info;
        
        // User & System Information
        info.user = detect::os::getUsername();
        info.hostname = detect::os::getHostname();
        
        detect::os::OSInfo os_info = detect::os::detectOS();
        info.os_name = os_info.name;
        info.os_version = os_info.version;
        info.kernel = detect::os::getKernel();
        info.arch = detect::os::getArch();
        info.uptime = detect::os::getUptime();
        
        // Desktop Environment Information
        info.desktop_env = detect::os::getDesktopEnv();
        info.window_manager = detect::os::getWindowManager();
        info.wm_theme = detect::os::getWMTheme();
        info.theme = detect::os::getTheme();
        info.icons = detect::os::getIcons();
        info.font = detect::os::getFont();
        info.cursor = detect::os::getCursor();
        info.display = detect::os::getDisplay();
        
        // Shell & Terminal Information
        info.shell = detect::shell::getShell();
        info.terminal = detect::terminal::getTerminalProgram();
        info.terminal_font = detect::os::getTerminalFont();
        info.locale = detect::os::getLocale();
        
        // Hardware Information
        info.cpu = detect::cpu::getCPUString();
        info.gpu = detect::gpu::getGPUString();
        info.memory = detect::memory::getMemoryString();
        info.swap = detect::memory::getSwapString();
        info.disk = detect::disk::getRootDiskString();
        info.battery = detect::battery::getBatteryString();
        
        // Software Information
        info.packages = detect::packages::getPackageString();
        info.ip_address = detect::network::getPrimaryIP();
        
        return info;
    }
    
    // Legacy interface for compatibility
    static std::string getDistro() {
        detect::os::OSInfo os_info = detect::os::detectOS();
        return os_info.name;
    }

    static std::string getKernel() {
        return detect::os::getKernel();
    }

    static std::string getCPU() {
        return detect::cpu::getCPUString();
    }

    static std::string getGPU() {
        return detect::gpu::getGPUString();
    }

    static std::string getRAM() {
        return detect::memory::getMemoryString();
    }

    static std::string getDisk() {
        return detect::disk::getRootDiskString();
    }

    static std::string getHostname() {
        return detect::os::getHostname();
    }

    static std::string getDesktopEnv() {
        return detect::os::getDesktopEnv();
    }

    static std::string getWindowManager() {
        return detect::os::getWindowManager();
    }

    static std::string getPackages() {
        return detect::packages::getPackageString();
    }

    static std::string getShell() {
        return detect::shell::getShell();
    }

    static std::string getTerminal() {
        return detect::terminal::getTerminalProgram();
    }

    static std::string getIPAddress() {
        return detect::network::getPrimaryIP();
    }

    static std::string getUptime() {
        return detect::os::getUptime();
    }

    static std::string getArchitecture() {
        return detect::os::getArch();
    }

    static std::string getBattery() {
        return detect::battery::getBatteryString();
    }
};
