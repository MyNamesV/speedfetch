#ifndef ASCII_ART_H
#define ASCII_ART_H

#include <string>
#include <map>
#include <vector>
#include <cstdint>

// Color constants (0-15 basic ANSI, 16-255 extended 256-color palette)
using LogoColor = uint8_t;
constexpr LogoColor COLOR_DEFAULT = 0;
constexpr LogoColor COLOR_RED = 1;
constexpr LogoColor COLOR_GREEN = 2;
constexpr LogoColor COLOR_YELLOW = 3;
constexpr LogoColor COLOR_BLUE = 4;
constexpr LogoColor COLOR_MAGENTA = 5;
constexpr LogoColor COLOR_CYAN = 6;
constexpr LogoColor COLOR_WHITE = 7;
constexpr LogoColor COLOR_BLACK = 8;
constexpr LogoColor COLOR_LIGHT_RED = 9;
constexpr LogoColor COLOR_LIGHT_GREEN = 10;
constexpr LogoColor COLOR_LIGHT_YELLOW = 11;
constexpr LogoColor COLOR_LIGHT_BLUE = 12;
constexpr LogoColor COLOR_LIGHT_MAGENTA = 13;
constexpr LogoColor COLOR_LIGHT_CYAN = 14;

// Macro for 256-color palette (colors 16-255)
#define COLOR_256(x) static_cast<LogoColor>(x)

// Logo information structure
struct LogoInfo {
    std::string art;
    std::vector<LogoColor> colors;
};

class ASCIIArt {
public:
    static std::string getArt(const std::string& distro);
    static std::string getDistroType(const std::string& distro_name);
    static const LogoInfo* getLogoInfo(const std::string& distro);
    static std::string colorizeArt(const std::string& art, const std::vector<LogoColor>& colors);
    
private:
    static const std::map<std::string, LogoInfo> arts;
    static std::string colorToAnsi(LogoColor color);
};

#endif // ASCII_ART_H
