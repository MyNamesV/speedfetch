#include "system_info.h"
#include "ascii_art.h"
#include "config.h"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <cstring>

// Color codes for terminal
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string WHITE = "\033[37m";
const std::string BOLD = "\033[1m";
const std::string BOLD_RED = "\033[1;31m";

std::vector<std::string> getArtLines(const std::string& art) {
    std::vector<std::string> lines;
    std::string line;
    std::istringstream iss(art);
    
    while (std::getline(iss, line)) {
        // Trim trailing spaces
        size_t end = line.find_last_not_of(" \t\r\n");
        if (end != std::string::npos) {
            line = line.substr(0, end + 1);
        }
        lines.push_back(line);
    }
    
    return lines;
}

// Get maximum art line length
int getMaxArtLineLength(const std::vector<std::string>& art_lines) {
    int max_len = 0;
    for (const auto& line : art_lines) {
        // Count length WITHOUT ANSI escape codes
        int visible_len = 0;
        size_t i = 0;
        while (i < line.length()) {
            // Check for ANSI escape sequence
            if (line[i] == '\033' && i + 1 < line.length() && line[i + 1] == '[') {
                // Skip until 'm'
                while (i < line.length() && line[i] != 'm') {
                    i++;
                }
                if (i < line.length()) i++;  // Skip the 'm'
            } else {
                visible_len++;
                i++;
            }
        }
        if (visible_len > max_len) {
            max_len = visible_len;
        }
    }
    return max_len + 3;  // +3 for small text offset
}

// Calculate visible length (excluding ANSI codes)
int getVisibleLength(const std::string& str) {
    int visible_len = 0;
    size_t i = 0;
    while (i < str.length()) {
        // Check for ANSI escape sequence
        if (str[i] == '\033' && i + 1 < str.length() && str[i + 1] == '[') {
            // Skip until 'm'
            while (i < str.length() && str[i] != 'm') {
                i++;
            }
            if (i < str.length()) i++;  // Skip the 'm'
        } else {
            visible_len++;
            i++;
        }
    }
    return visible_len;
}

// Format value with green highlighting for percentages
std::string formatValue(const std::string& value) {
    // Regular expression to find percentages (number%)
    std::regex percent_regex("(\\d+%)");
    std::string result;
    std::smatch match;
    std::string str = value;
    
    while (std::regex_search(str, match, percent_regex)) {
        // Add text before percentages
        result += match.prefix().str();
        // Add percentage in green color
        result += GREEN + match[0].str() + RESET;
        // Continue searching in the remaining part of the string
        str = match.suffix().str();
    }
    // Add the remaining part of the string
    result += str;
    
    return result;
}

int main(int argc, char* argv[]) {
    // Load configuration
    Config::load();
    
    // Get system information
    SystemInfo info = SystemInfoGatherer::gather();
    
    // Parse command line arguments
    std::string distro_to_display = info.distro;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        // Check for --logo-<distro> flag
        if (arg.find("--logo-") == 0) {
            distro_to_display = arg.substr(7);  // Remove "--logo-" prefix
        }
        // Help flag
        else if (arg == "--help" || arg == "-h") {
            std::cout << "speedfetch - Linux system information fetcher\n\n";
            std::cout << "Usage: speedfetch [OPTION]\n\n";
            std::cout << "Options:\n";
            std::cout << "  --logo-ubuntu           Display Ubuntu ASCII logo\n";
            std::cout << "  --logo-fedora           Display Fedora ASCII logo\n";
            std::cout << "  --logo-debian           Display Debian ASCII logo\n";
            std::cout << "  --logo-arch             Display Arch Linux ASCII logo\n";
            std::cout << "  --logo-manjaro          Display Manjaro ASCII logo\n";
            std::cout << "  --logo-opensuse         Display openSUSE ASCII logo\n";
            std::cout << "  --logo-centos           Display CentOS ASCII logo\n";
            std::cout << "  --logo-elementary       Display Elementary ASCII logo\n";
            std::cout << "  --logo-pop-os           Display Pop!_OS ASCII logo\n";
            std::cout << "  --logo-ubuntu-budgie    Display Ubuntu Budgie ASCII logo\n";
            std::cout << "  --logo-tux              Display Tux ASCII logo\n";
            std::cout << "  --help, -h              Show this help message\n";
            return 0;
        }
    }
    
    // Get ASCII art for the distro
    std::string art = ASCIIArt::getArt(distro_to_display);
    
    // Get logo info and colorize the art
    const LogoInfo* logo_info = ASCIIArt::getLogoInfo(distro_to_display);
    if (logo_info) {
        art = ASCIIArt::colorizeArt(art, logo_info->colors);
    }
    
    std::vector<std::string> art_lines = getArtLines(art);
    
    // Use fixed width for all logos (45 characters)
    int art_width = 45;
    
    // Display output
    std::cout << std::endl;
    
    // Prepare info items
    std::vector<std::pair<std::string, std::string>> all_items = {
        {"User", info.user + "@" + info.host},
        {"OS", info.distro},
        {"Host", info.host},
        {"Kernel", info.kernel},
        {"Uptime", info.uptime},
        {"Packages", info.packages},
        {"Shell", info.shell},
        {"Display", info.display},
        {"DE", info.de},
        {"WM", info.wm},
        {"WM Theme", info.wm_theme},
        {"Theme", info.theme},
        {"Icons", info.icons},
        {"Font", info.font},
        {"Cursor", info.cursor},
        {"Terminal", info.terminal},
        {"Terminal Font", info.terminal_font},
        {"CPU", info.cpu},
        {"GPU", info.gpu},
        {"Memory", info.ram},
        {"Swap", info.swap},
        {"Disk (/)", info.disk},
        {"Local IP", info.ip_address},
        {"Locale", info.locale}
    };
    
    // Filter items based on config
    std::vector<std::pair<std::string, std::string>> info_items;
    std::vector<std::pair<std::string, std::string>> config_map = {
        {"User", "user"},
        {"OS", "os"},
        {"Host", "host"},
        {"Kernel", "kernel"},
        {"Uptime", "uptime"},
        {"Packages", "packages"},
        {"Shell", "shell"},
        {"Display", "display"},
        {"DE", "de"},
        {"WM", "wm"},
        {"WM Theme", "wm_theme"},
        {"Theme", "theme"},
        {"Icons", "icons"},
        {"Font", "font"},
        {"Cursor", "cursor"},
        {"Terminal", "terminal"},
        {"Terminal Font", "terminal_font"},
        {"CPU", "cpu"},
        {"GPU", "gpu"},
        {"Memory", "memory"},
        {"Swap", "swap"},
        {"Disk (/)", "disk"},
        {"Local IP", "local_ip"},
        {"Locale", "locale"}
    };
    
    for (const auto& item : all_items) {
        // Find config key for this item
        std::string config_key = "";
        for (const auto& mapping : config_map) {
            if (mapping.first == item.first) {
                config_key = mapping.second;
                break;
            }
        }
        
        // Check if enabled in config
        if (config_key.empty() || Config::isEnabled(config_key)) {
            info_items.push_back(item);
        }
    }
    
    // Print art and info side by side
    size_t max_lines = std::max(art_lines.size(), info_items.size());
    
    for (size_t i = 0; i < max_lines; ++i) {
        // Print ASCII art with color
        if (i < art_lines.size()) {
            // Get the visible (non-ANSI) length
            int visible_len = getVisibleLength(art_lines[i]);
            int padding = art_width - visible_len;
            
            // Print the art line with ANSI codes
            std::cout << art_lines[i];
            
            // Add padding to align info text
            if (padding > 0) {
                for (int p = 0; p < padding; ++p) {
                    std::cout << " ";
                }
            }
        } else {
            // Print empty space if no more art lines
            for (int j = 0; j < art_width; ++j) {
                std::cout << " ";
            }
        }
        
        // Print system info with bold red labels and white/green values
        if (i < info_items.size()) {
            const auto& item = info_items[i];
            
            // Label bold red, colon white, value white
            std::string formatted = formatValue(item.second);
            printf("%s%s%s: %s%s\n", 
                   BOLD_RED.c_str(), 
                   item.first.c_str(), 
                   WHITE.c_str(),
                   formatted.c_str(), 
                   RESET.c_str());
        } else {
            printf("\n");
        }
    }
    
    std::cout << std::endl;
    
    return 0;
}
