#pragma once

#include <string>
#include "exec.h"
#include "strings.h"

namespace detect::packages {
    inline int countPackages() {
        int count = 0;
        
        // Check for different package managers
        std::vector<std::pair<std::string, std::string>> managers = {
            {"dpkg", "dpkg -l 2>/dev/null | grep '^ii' | wc -l"},
            {"rpm", "rpm -qa 2>/dev/null | wc -l"},
            {"pacman", "pacman -Q 2>/dev/null | wc -l"},
            {"xbps-query", "xbps-query -l 2>/dev/null | wc -l"},
            {"apk", "apk info 2>/dev/null | wc -l"},
            {"brew", "brew list 2>/dev/null | wc -l"},
        };
        
        for (const auto& manager : managers) {
            if (core::exec::commandExists(manager.first)) {
                std::string count_str = core::exec::exec(manager.second);
                if (!count_str.empty()) {
                    try {
                        count = std::stoi(core::strings::trim(count_str));
                        if (count > 0) {
                            return count;
                        }
                    } catch (...) {
                        continue;
                    }
                }
            }
        }
        
        return 0;
    }

    inline std::string getPackageString() {
        int count = countPackages();
        if (count == 0) {
            return "N/A";
        }
        return std::to_string(count) + " packages";
    }
}
