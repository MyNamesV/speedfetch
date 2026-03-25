#pragma once

#include <string>
#include "strings.h"
#include "file.h"
#include "exec.h"

namespace detect::os {
    struct OSInfo {
        std::string name;
        std::string version;
        std::string pretty_name;
        std::string id;
        std::string id_like;
        std::string variant;
    };

    inline OSInfo detectOS() {
        OSInfo info;
        std::string content = core::file::readFile("/etc/os-release");
        
        if (content.empty()) {
            content = core::file::readFile("/usr/lib/os-release");
        }

        info.name = core::file::getKeyValue(content, "NAME");
        info.version = core::file::getKeyValue(content, "VERSION");
        info.pretty_name = core::file::getKeyValue(content, "PRETTY_NAME");
        info.id = core::file::getKeyValue(content, "ID");
        info.id_like = core::file::getKeyValue(content, "ID_LIKE");
        info.variant = core::file::getKeyValue(content, "VARIANT");

        if (info.name.empty()) {
            info.name = info.pretty_name.empty() ? "Linux" : info.pretty_name;
        }

        return info;
    }

    inline std::string getKernel() {
        std::string kernel = core::exec::exec("uname -r");
        return kernel.empty() ? "N/A" : kernel;
    }

    inline std::string getKernelVersion() {
        std::string version = core::exec::exec("uname -v");
        return version.empty() ? "N/A" : version;
    }

    inline std::string getArch() {
        std::string arch = core::exec::exec("uname -m");
        return arch.empty() ? "N/A" : arch;
    }

    inline std::string getDesktopEnv() {
        std::string de = core::exec::exec("echo $XDG_CURRENT_DESKTOP");
        if (de.empty()) {
            de = core::exec::exec("echo $DESKTOP_SESSION");
        }
        return de.empty() ? "N/A" : de;
    }

    inline std::string getWindowManager() {
        // Check for GNOME environment variable
        std::string de = core::exec::exec("echo $XDG_CURRENT_DESKTOP 2>/dev/null");
        if (de.find("GNOME") != std::string::npos) return "GNOME (Mutter)";
        if (de.find("KDE") != std::string::npos) return "KDE (KWin)";
        if (de.find("XFCE") != std::string::npos) return "Xfce (xfwm4)";
        if (de.find("MATE") != std::string::npos) return "MATE (Marco)";
        
        // Try wmctrl
        std::string wm = core::exec::exec("wmctrl -m 2>/dev/null | head -1");
        if (!wm.empty() && wm[0] != '$') {
            return wm;
        }
        
        // Try to detect from running processes
        std::vector<std::string> wms = {
            "mutter", "kwin", "xfwm4", "marco",
            "i3", "openbox", "fluxbox", "awesome", "compiz"
        };
        
        for (const auto& wm_name : wms) {
            if (core::exec::commandExists(wm_name)) {
                return wm_name;
            }
        }
        
        return "N/A";
    }

    inline std::string getHostname() {
        std::string hostname = core::file::readFirstLine("/etc/hostname");
        if (hostname.empty()) {
            hostname = core::exec::exec("hostname");
        }
        return hostname.empty() ? "N/A" : hostname;
    }

    inline std::string getUptime() {
        std::string content = core::file::readProcFile("uptime");
        if (content.empty()) return "N/A";
        
        unsigned long uptime_secs = 0;
        if (sscanf(content.c_str(), "%lu", &uptime_secs) != 1) {
            return "N/A";
        }
        
        unsigned long days = uptime_secs / 86400;
        unsigned long hours = (uptime_secs % 86400) / 3600;
        unsigned long minutes = (uptime_secs % 3600) / 60;
        
        std::string result;
        if (days > 0) {
            result += std::to_string(days) + "d ";
        }
        result += std::to_string(hours) + "h " + std::to_string(minutes) + "m";
        
        return result;
    }

    inline std::string getUsername() {
        const char* user = std::getenv("USER");
        return user ? std::string(user) : "N/A";
    }

    inline std::string getWMTheme() {
        std::string theme = core::exec::exec("dconf read /org/gnome/desktop/interface/gtk-theme 2>/dev/null | tr -d \"'\"");
        if (theme.empty() || theme == "N/A") {
            theme = core::exec::exec("kreadconfig5 --file kdeglobals --group General --key ColorScheme 2>/dev/null");
        }
        return theme.empty() ? "N/A" : theme;
    }

    inline std::string getTheme() {
        std::string theme = core::exec::exec("dconf read /org/gnome/desktop/interface/gtk-theme 2>/dev/null | tr -d \"'\"");
        if (!theme.empty() && theme != "N/A") {
            return theme + " [GTK]";
        }
        
        std::string kde_theme = core::exec::exec("kreadconfig5 --file kdeglobals --group General --key ColorScheme 2>/dev/null");
        if (!kde_theme.empty() && kde_theme != "N/A") {
            return kde_theme + " [KDE]";
        }
        
        return "N/A";
    }

    inline std::string getIcons() {
        std::string icons = core::exec::exec("dconf read /org/gnome/desktop/interface/icon-theme 2>/dev/null | tr -d \"'\"");
        if (!icons.empty() && icons != "N/A") {
            return icons + " [GTK]";
        }
        
        std::string kde_icons = core::exec::exec("kreadconfig5 --file kdeglobals --group Icons --key Theme 2>/dev/null");
        if (!kde_icons.empty() && kde_icons != "N/A") {
            return kde_icons + " [KDE]";
        }
        
        return "N/A";
    }

    inline std::string getFont() {
        std::string font = core::exec::exec("dconf read /org/gnome/desktop/interface/font-name 2>/dev/null | tr -d \"'\"");
        if (!font.empty() && font != "N/A") {
            return font + " [GTK]";
        }
        
        std::string kde_font = core::exec::exec("kreadconfig5 --file kdeglobals --group General --key font 2>/dev/null");
        if (!kde_font.empty() && kde_font != "N/A") {
            return kde_font + " [KDE]";
        }
        
        return "N/A";
    }

    inline std::string getCursor() {
        std::string cursor = core::exec::exec("dconf read /org/gnome/desktop/interface/cursor-theme 2>/dev/null | tr -d \"'\"");
        if (!cursor.empty() && cursor != "N/A") {
            std::string size = core::exec::exec("dconf read /org/gnome/desktop/interface/cursor-size 2>/dev/null");
            if (!size.empty() && size != "N/A") {
                return cursor + " (" + size + "px)";
            }
            return cursor;
        }
        return "N/A";
    }

    inline std::string getDisplay() {
        std::string output = core::exec::exec("xrandr --query 2>/dev/null | grep ' connected' | head -1");
        if (output.empty() || output == "N/A") {
            return "N/A";
        }

        // Parse the xrandr output to extract resolution and refresh rate
        size_t res_pos = output.find(" ");
        if (res_pos == std::string::npos) return "N/A";

        size_t start = output.find_first_of("0123456789", res_pos);
        if (start == std::string::npos) return "N/A";

        size_t end = start;
        while (end < output.length() && (std::isdigit(output[end]) || output[end] == 'x')) {
            end++;
        }

        if (end > start) {
            std::string res = output.substr(start, end - start);
            
            // Get refresh rate
            std::string rate_output = core::exec::exec("xrandr --query 2>/dev/null | grep -oP '\\d+\\.\\d+\\*' | head -1");
            if (!rate_output.empty() && rate_output != "N/A") {
                rate_output.pop_back(); // Remove asterisk
                return res + " @ " + rate_output + " Hz";
            }
            return res;
        }

        return "N/A";
    }

    inline std::string getTerminalFont() {
        // Try gsettings first
        std::string font = core::exec::exec("gsettings get org.gnome.desktop.interface monospace-font-name 2>/dev/null | tr -d \"'\"");
        if (!font.empty() && font != "N/A") {
            return font;
        }
        
        // Try dconf for GNOME terminal
        std::string profiles = core::exec::exec("dconf list /org/gnome/terminal/legacy/profiles:/ 2>/dev/null | head -1");
        if (!profiles.empty() && profiles != "N/A") {
            size_t start = profiles.find(':');
            size_t end = profiles.find('/');
            if (start != std::string::npos && end != std::string::npos && start < end) {
                std::string uuid = profiles.substr(start + 1, end - start - 1);
                std::string cmd = "dconf read /org/gnome/terminal/legacy/profiles:/" + uuid + "/font 2>/dev/null | tr -d \"'\"";
                font = core::exec::exec(cmd);
                if (!font.empty() && font != "N/A") {
                    return font;
                }
            }
        }
        
        return "N/A";
    }

    inline std::string getLocale() {
        const char* lang = std::getenv("LANG");
        return lang ? std::string(lang) : "N/A";
    }
}
