#include "system_info.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

std::string SystemInfoGatherer::executeCommand(const std::string& command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "N/A";
    
    std::string result;
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    
    // Remove trailing newline
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }
    
    return result.empty() ? "N/A" : result;
}

std::string SystemInfoGatherer::getDistro() {
    std::ifstream os_release("/etc/os-release");
    if (os_release.is_open()) {
        std::string line;
        while (std::getline(os_release, line)) {
            if (line.find("PRETTY_NAME=") == 0) {
                std::string distro = line.substr(12);
                distro.erase(std::remove(distro.begin(), distro.end(), '"'), distro.end());
                return distro;
            }
        }
    }
    return "Linux";
}

std::string SystemInfoGatherer::getKernel() {
    return executeCommand("uname -r");
}

std::string SystemInfoGatherer::getCPU() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (cpuinfo.is_open()) {
        std::string line;
        int count = 0;
        while (std::getline(cpuinfo, line)) {
            if (line.find("model name") == 0) {
                count++;
                if (count == 1) {
                    size_t pos = line.find(':');
                    if (pos != std::string::npos) {
                        std::string cpu = line.substr(pos + 2);
                        if (cpu.find(" @ ") != std::string::npos) {
                            cpu = cpu.substr(0, cpu.find(" @ "));
                        }
                        // Get frequency
                        std::string freq = executeCommand("grep -m1 'cpu MHz' /proc/cpuinfo | awk '{print $4}'");
                        if (freq != "N/A") {
                            double mhz = std::stod(freq) / 1000.0;
                            char buf[20];
                            snprintf(buf, sizeof(buf), "%.2f", mhz);
                            cpu += " (" + std::string(buf) + " GHz)";
                        }
                        return cpu;
                    }
                }
            }
        }
    }
    return "N/A";
}

std::string SystemInfoGatherer::getGPU() {
    // Try to get GPU info from lspci
    std::string gpu = executeCommand("lspci | grep -i 'vga\\|3d\\|display' | sed 's/.*: //' | head -1");
    if (gpu != "N/A" && !gpu.empty()) {
        return gpu;
    }
    return "N/A";
}

std::string SystemInfoGatherer::getRAM() {
    std::ifstream meminfo("/proc/meminfo");
    if (meminfo.is_open()) {
        std::string line;
        long total_mem = 0, avail_mem = 0;
        
        while (std::getline(meminfo, line)) {
            if (line.find("MemTotal:") == 0) {
                std::istringstream iss(line.substr(9));
                iss >> total_mem;
            }
            if (line.find("MemAvailable:") == 0) {
                std::istringstream iss(line.substr(13));
                iss >> avail_mem;
            }
        }
        
        if (total_mem > 0) {
            long used_mem = total_mem - avail_mem;
            double used_gb = used_mem / (1024.0 * 1024.0);
            double total_gb = total_mem / (1024.0 * 1024.0);
            double percent = (used_mem * 100.0) / total_mem;
            
            char buf[64];
            snprintf(buf, sizeof(buf), "%.2f GiB / %.2f GiB (%.0f%%)", used_gb, total_gb, percent);
            return std::string(buf);
        }
    }
    return "N/A";
}

std::string SystemInfoGatherer::getSwap() {
    std::ifstream meminfo("/proc/meminfo");
    if (meminfo.is_open()) {
        std::string line;
        long swap_total = 0, swap_free = 0;
        
        while (std::getline(meminfo, line)) {
            if (line.find("SwapTotal:") == 0) {
                std::istringstream iss(line.substr(10));
                iss >> swap_total;
            }
            if (line.find("SwapFree:") == 0) {
                std::istringstream iss(line.substr(9));
                iss >> swap_free;
            }
        }
        
        if (swap_total > 0) {
            long swap_used = swap_total - swap_free;
            double used_gb = swap_used / (1024.0 * 1024.0);
            double total_gb = swap_total / (1024.0 * 1024.0);
            double percent = (swap_used * 100.0) / swap_total;
            
            char buf[64];
            snprintf(buf, sizeof(buf), "%.2f GiB / %.2f GiB (%.0f%%)", used_gb, total_gb, percent);
            return std::string(buf);
        } else {
            return "0 B / 0 B (0%)";
        }
    }
    return "N/A";
}

std::string SystemInfoGatherer::getDisk() {
    std::string result = executeCommand("df -h / | tail -1 | awk '{print $3 \" / \" $2 \" (\" $5 \")\"}'");
    return result;
}

std::string SystemInfoGatherer::getUptime() {
    std::ifstream uptime_file("/proc/uptime");
    if (uptime_file.is_open()) {
        double uptime_seconds;
        uptime_file >> uptime_seconds;
        
        long days = (long)uptime_seconds / 86400;
        long hours = ((long)uptime_seconds % 86400) / 3600;
        long minutes = ((long)uptime_seconds % 3600) / 60;
        
        std::stringstream ss;
        if (days > 0) ss << days << " day";
        if (days > 1) ss << "s";
        if (days > 0) ss << " ";
        ss << hours << " hr";
        if (hours != 1) ss << "s";
        ss << " " << minutes << " min";
        
        return ss.str();
    }
    return "N/A";
}

std::string SystemInfoGatherer::getShell() {
    const char* shell_env = std::getenv("SHELL");
    if (shell_env) {
        std::string shell_path(shell_env);
        size_t pos = shell_path.find_last_of('/');
        if (pos != std::string::npos) {
            std::string shell_name = shell_path.substr(pos + 1);
            // Get version
            std::string cmd = shell_name + " --version 2>&1 | head -1 | awk '{print $NF}'";
            std::string version = executeCommand(cmd);
            if (version != "N/A" && !version.empty()) {
                return shell_name + " " + version;
            }
            return shell_name;
        }
    }
    return "N/A";
}

std::string SystemInfoGatherer::getHost() {
    return executeCommand("hostname");
}

std::string SystemInfoGatherer::getUser() {
    const char* user = std::getenv("USER");
    return user ? std::string(user) : "N/A";
}

std::string SystemInfoGatherer::getTerminal() {
    const char* term = std::getenv("TERM");
    return term ? std::string(term) : "N/A";
}

std::string SystemInfoGatherer::getTerminalFont() {
    // Try different ways to get terminal font
    
    // Method 1: Try gsettings (works with many terminals)
    std::string font = executeCommand("gsettings get org.gnome.desktop.interface monospace-font-name 2>/dev/null | tr -d \"'\"");
    if (font != "N/A" && !font.empty()) {
        return font;
    }
    
    // Method 2: Try dconf with dynamic profile lookup
    std::string profiles = executeCommand("dconf list /org/gnome/terminal/legacy/profiles:/ 2>/dev/null | head -1");
    if (profiles != "N/A" && !profiles.empty()) {
        // profiles contains something like ":uuid/"
        std::string uuid = profiles;
        // Clean up UUID
        size_t start = uuid.find(':');
        size_t end = uuid.find('/');
        if (start != std::string::npos && end != std::string::npos && start < end) {
            uuid = uuid.substr(start + 1, end - start - 1);
            std::string font_cmd = "dconf read /org/gnome/terminal/legacy/profiles:/" + uuid + "/font 2>/dev/null | tr -d \"'\"";
            font = executeCommand(font_cmd);
            if (font != "N/A" && !font.empty()) {
                return font;
            }
        }
    }
    
    // Method 3: Check $TERMINALFONT environment variable or try common alternatives
    const char* term_font = std::getenv("TERMINALFONT");
    if (term_font) {
        return std::string(term_font);
    }
    
    return "N/A";
}

std::string SystemInfoGatherer::getDE() {
    const char* xdg_de = std::getenv("XDG_CURRENT_DESKTOP");
    if (xdg_de) {
        std::string de(xdg_de);
        if (de.find("GNOME") != std::string::npos) {
            std::string version = executeCommand("gnome-shell --version 2>/dev/null | awk '{print $NF}'");
            if (version != "N/A") return "GNOME " + version;
            return "GNOME";
        }
        if (de.find("KDE") != std::string::npos) return "KDE Plasma";
        if (de.find("XFCE") != std::string::npos) return "Xfce";
        if (de.find("UNITY") != std::string::npos) return "Unity";
        return de;
    }
    return "N/A";
}

std::string SystemInfoGatherer::getWM() {
    const char* wayland = std::getenv("WAYLAND_DISPLAY");
    if (wayland) {
        return "Mutter (Wayland)";
    }
    std::string wm = executeCommand("wmctrl -m 2>/dev/null | head -1 | sed 's/Name: //'");
    if (wm != "N/A" && !wm.empty()) {
        return wm;
    }
    return "N/A";
}

std::string SystemInfoGatherer::getWMTheme() {
    std::string theme = executeCommand("dconf read /org/gnome/desktop/interface/gtk-theme 2>/dev/null | tr -d \"'\"");
    if (theme != "N/A" && !theme.empty()) {
        return theme;
    }
    return "N/A";
}

std::string SystemInfoGatherer::getTheme() {
    std::string theme = executeCommand("dconf read /org/gnome/desktop/interface/gtk-theme 2>/dev/null | tr -d \"'\"");
    if (theme != "N/A" && !theme.empty()) {
        return theme + " [GTK2/3/4]";
    }
    return "N/A";
}

std::string SystemInfoGatherer::getIcons() {
    std::string icons = executeCommand("dconf read /org/gnome/desktop/interface/icon-theme 2>/dev/null | tr -d \"'\"");
    if (icons != "N/A" && !icons.empty()) {
        return icons + " [GTK2/3/4]";
    }
    return "N/A";
}

std::string SystemInfoGatherer::getFont() {
    // Method 1: Try gsettings for system font
    std::string font = executeCommand("gsettings get org.gnome.desktop.interface font-name 2>/dev/null | tr -d \"'\"");
    if (font != "N/A" && !font.empty()) {
        return font + " [GTK]";
    }
    
    // Method 2: Try dconf for GNOME font settings
    font = executeCommand("dconf read /org/gnome/desktop/interface/font-name 2>/dev/null | tr -d \"'\"");
    if (font != "N/A" && !font.empty()) {
        return font + " [GTK2/3/4]";
    }
    
    // Method 3: Try KDE settings
    std::string kde_font = executeCommand("kreadconfig5 --file kdeglobals --group General --key font 2>/dev/null");
    if (kde_font != "N/A" && !kde_font.empty()) {
        return kde_font + " [KDE]";
    }
    
    // Method 4: Check XFT_FONT environment variable
    const char* xft_font = std::getenv("XFT_FONT");
    if (xft_font) {
        return std::string(xft_font);
    }
    
    return "N/A";
}

std::string SystemInfoGatherer::getCursor() {
    std::string cursor = executeCommand("dconf read /org/gnome/desktop/interface/cursor-theme 2>/dev/null | tr -d \"'\"");
    if (cursor != "N/A" && !cursor.empty()) {
        std::string size = executeCommand("dconf read /org/gnome/desktop/interface/cursor-size 2>/dev/null");
        if (size != "N/A" && !size.empty()) {
            return cursor + " (" + size + "px)";
        }
        return cursor;
    }
    return "N/A";
}

std::string SystemInfoGatherer::getDisplay() {
    // Try to get display info using xrandr
    std::string output = executeCommand("xrandr --query 2>/dev/null | grep ' connected' | head -1");
    if (output != "N/A" && !output.empty()) {
        // Parse: "HDMI-1 connected primary 1920x1080+0+0 (normal left inverted right x axis y axis) 510mm x 287mm"
        // We want: 1920x1080 @ 60 Hz (example)
        
        // Extract resolution without position offsets (+0+0)
        size_t res_pos = output.find(" ");
        if (res_pos != std::string::npos) {
            // Find the resolution part (1920x1080)
            size_t start = output.find_first_of("0123456789", res_pos);
            if (start != std::string::npos) {
                // Find the end of resolution (format: 1920x1080+0+0)
                size_t end = start;
                while (end < output.length() && 
                       (isdigit(output[end]) || output[end] == 'x')) {
                    end++;
                }
                
                // Skip the +0+0 part
                if (end < output.length() && output[end] == '+') {
                    while (end < output.length() && output[end] != ' ') {
                        end++;
                    }
                }
                
                if (end > start) {
                    std::string res = output.substr(start, end - start);
                    // Remove any trailing +0+0 if still there
                    size_t plus_pos = res.find('+');
                    if (plus_pos != std::string::npos) {
                        res = res.substr(0, plus_pos);
                    }
                    
                    // Get refresh rate from xrandr
                    std::string rate_output = executeCommand("xrandr --query 2>/dev/null | grep -oP '\\d+\\.\\d+\\*' | head -1");
                    if (rate_output != "N/A" && !rate_output.empty()) {
                        // Remove the asterisk
                        rate_output.pop_back();
                        return res + " @ " + rate_output + " Hz";
                    }
                    return res;
                }
            }
        }
    }
    return "N/A";
}

std::string SystemInfoGatherer::getIPAddress() {
    struct ifaddrs *ifaddr, *ifa;
    std::string ip = "N/A";
    
    if (getifaddrs(&ifaddr) == -1) {
        return "N/A";
    }
    
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) continue;
        
        if (ifa->ifa_addr->sa_family == AF_INET) {
            std::string ifname(ifa->ifa_name);
            if (ifname != "lo") {
                char addr_buf[INET_ADDRSTRLEN];
                struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
                inet_ntop(AF_INET, &addr->sin_addr, addr_buf, INET_ADDRSTRLEN);
                
                struct sockaddr_in *netmask = (struct sockaddr_in *)ifa->ifa_netmask;
                if (netmask) {
                    int mask = inet_network(inet_ntoa(netmask->sin_addr));
                    int prefix = 0;
                    for (int i = 0; i < 32; i++) {
                        if (mask & (1 << i)) prefix++;
                    }
                    
                    char subnet_buf[50];
                    snprintf(subnet_buf, sizeof(subnet_buf), "%s/%d", addr_buf, 32 - prefix);
                    
                    char result[100];
                    snprintf(result, sizeof(result), "(%s): %s", ifname.c_str(), subnet_buf);
                    freeifaddrs(ifaddr);
                    return std::string(result);
                }
            }
        }
    }
    
    freeifaddrs(ifaddr);
    return ip;
}

std::string SystemInfoGatherer::getLocale() {
    const char* lang = std::getenv("LANG");
    return lang ? std::string(lang) : "N/A";
}

std::string SystemInfoGatherer::getPackages() {
    std::stringstream ss;
    bool first = true;
    
    std::string dpkg = executeCommand("dpkg -l 2>/dev/null | wc -l");
    if (dpkg != "N/A") {
        if (!first) ss << ", ";
        ss << dpkg << " (dpkg)";
        first = false;
    }
    
    std::string flatpak = executeCommand("flatpak list --app 2>/dev/null | wc -l");
    if (flatpak != "N/A" && flatpak != "0") {
        if (!first) ss << ", ";
        ss << flatpak << " (flatpak)";
        first = false;
    }
    
    std::string snap = executeCommand("snap list 2>/dev/null | tail -n +2 | wc -l");
    if (snap != "N/A" && snap != "0") {
        if (!first) ss << ", ";
        ss << snap << " (snap)";
        first = false;
    }
    
    return ss.str().empty() ? "N/A" : ss.str();
}

SystemInfo SystemInfoGatherer::gather() {
    SystemInfo info;
    info.user = getUser();
    info.host = getHost();
    info.distro = getDistro();
    info.kernel = getKernel();
    info.cpu = getCPU();
    info.gpu = getGPU();
    info.ram = getRAM();
    info.swap = getSwap();
    info.disk = getDisk();
    info.uptime = getUptime();
    info.shell = getShell();
    info.terminal = getTerminal();
    info.terminal_font = getTerminalFont();
    info.display = getDisplay();
    info.de = getDE();
    info.wm = getWM();
    info.wm_theme = getWMTheme();
    info.theme = getTheme();
    info.icons = getIcons();
    info.font = getFont();
    info.cursor = getCursor();
    info.ip_address = getIPAddress();
    info.locale = getLocale();
    info.packages = getPackages();
    return info;
}
