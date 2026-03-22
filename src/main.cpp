#include "system_info.h"
#include "ascii_art.h"
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

std::vector<std::string> getArtLines(const std::string& art) {
    std::vector<std::string> lines;
    std::string line;
    std::istringstream iss(art);
    
    while (std::getline(iss, line)) {
        // Обрезаем конечные пробелы
        size_t end = line.find_last_not_of(" \t\r\n");
        if (end != std::string::npos) {
            line = line.substr(0, end + 1);
        }
        lines.push_back(line);
    }
    
    return lines;
}

// Получить максимальную длину строки арта
int getMaxArtLineLength(const std::vector<std::string>& art_lines) {
    int max_len = 0;
    for (const auto& line : art_lines) {
        // Считаем длину БЕЗ конечных пробелов
        size_t len = line.find_last_not_of(" \t\r\n");
        if (len != std::string::npos) {
            len = len + 1;
        } else {
            len = 0;
        }
        if (len > max_len) {
            max_len = len;
        }
    }
    return max_len + 3;  // +3 для небольшого отступа от текста
}

// Форматирование значения с выделением процентов зеленым
std::string formatValue(const std::string& value) {
    // Регулярное выражение для поиска процентов (число%)
    std::regex percent_regex("(\\d+%)");
    std::string result;
    std::smatch match;
    std::string str = value;
    
    while (std::regex_search(str, match, percent_regex)) {
        // Добавляем текст до процентов
        result += match.prefix().str();
        // Добавляем процент зеленым цветом
        result += GREEN + match[0].str() + RESET;
        // Продолжаем поиск в остальной части строки
        str = match.suffix().str();
    }
    // Добавляем оставшуюся часть строки
    result += str;
    
    return result;
}

int main(int argc, char* argv[]) {
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
    std::vector<std::string> art_lines = getArtLines(art);
    
    // Вычисляем максимальную длину ASCII арта
    int art_width = getMaxArtLineLength(art_lines) + 2;  // +2 для небольших отступа
    
    // Display output
    std::cout << std::endl;
    
    // Prepare info items
    std::vector<std::pair<std::string, std::string>> info_items = {
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
    
    // Print art and info side by side
    size_t max_lines = std::max(art_lines.size(), info_items.size());
    
    for (size_t i = 0; i < max_lines; ++i) {
        // Print ASCII art without color
        if (i < art_lines.size()) {
            // Используем printf для точного контроля форматирования
            printf("%-*s", art_width, art_lines[i].c_str());
        } else {
            printf("%-*s", art_width, "");
        }
        
        // Print system info with red labels and white/green values
        if (i < info_items.size()) {
            const auto& item = info_items[i];
            
            // Лейбел красный, потом выравнивание пробелами белым, двоеточие белым, значение белым
            std::string formatted = formatValue(item.second);
            printf("%s%s%s%*s: %s%s\n", 
                   RED.c_str(), 
                   item.first.c_str(), 
                   WHITE.c_str(),
                   (int)(14 - item.first.length()), 
                   "", 
                   formatted.c_str(), 
                   RESET.c_str());
        } else {
            printf("\n");
        }
    }
    
    std::cout << std::endl;
    
    return 0;
}
