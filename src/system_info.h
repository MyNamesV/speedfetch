#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <string>
#include <vector>

struct SystemInfo {
    // Basic info
    std::string user;
    std::string host;
    std::string distro;
    
    // Hardware
    std::string kernel;
    std::string cpu;
    std::string gpu;
    std::string ram;
    std::string swap;
    std::string disk;
    std::string uptime;
    
    // Environment
    std::string shell;
    std::string terminal;
    std::string terminal_font;
    std::string de;           // Desktop Environment
    std::string wm;           // Window Manager
    std::string wm_theme;     // WM Theme
    std::string theme;        // GTK Theme
    std::string icons;        // Icons theme
    std::string font;         // GTK Font
    std::string cursor;       // Cursor theme
    std::string display;      // Display info (resolution, refresh rate)
    
    // Network & Locale
    std::string ip_address;   // Local IP
    std::string locale;       // System locale
    std::string packages;     // Package managers info
};

class SystemInfoGatherer {
public:
    static SystemInfo gather();
    
private:
    static std::string getDistro();
    static std::string getKernel();
    static std::string getCPU();
    static std::string getGPU();
    static std::string getRAM();
    static std::string getSwap();
    static std::string getDisk();
    static std::string getUptime();
    static std::string getShell();
    static std::string getHost();
    static std::string getUser();
    static std::string getTerminal();
    static std::string getTerminalFont();
    static std::string getDE();
    static std::string getWM();
    static std::string getWMTheme();
    static std::string getTheme();
    static std::string getIcons();
    static std::string getFont();
    static std::string getCursor();
    static std::string getDisplay();
    static std::string getIPAddress();
    static std::string getLocale();
    static std::string getPackages();
    static std::string executeCommand(const std::string& command);
};

#endif // SYSTEM_INFO_H
