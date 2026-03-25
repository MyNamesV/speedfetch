#pragma once

#include <string>
#include "file.h"
#include "math.h"
#include "strings.h"

namespace detect::memory {
    struct MemoryInfo {
        unsigned long total;
        unsigned long available;
        unsigned long used;
        unsigned long percent;
    };

    inline MemoryInfo detectMemory() {
        MemoryInfo info{};
        
        std::string content = core::file::readProcFile("meminfo");
        if (content.empty()) {
            return info;
        }

        std::istringstream iss(content);
        std::string line;
        
        while (std::getline(iss, line)) {
            try {
                if (line.find("MemTotal:") == 0) {
                    size_t colon_pos = line.find(':');
                    if (colon_pos != std::string::npos) {
                        std::string num_str = line.substr(colon_pos + 1);
                        info.total = std::stoul(core::strings::trim(num_str));
                    }
                } else if (line.find("MemAvailable:") == 0) {
                    size_t colon_pos = line.find(':');
                    if (colon_pos != std::string::npos) {
                        std::string num_str = line.substr(colon_pos + 1);
                        info.available = std::stoul(core::strings::trim(num_str));
                    }
                }
            } catch (...) {
                continue; // Skip parsing errors
            }
        }

        info.used = info.total > info.available ? info.total - info.available : 0;
        info.percent = info.total > 0 ? (info.used * 100) / info.total : 0;

        return info;
    }

    inline std::string getMemoryString() {
        MemoryInfo mem = detectMemory();
        
        // If no data, return N/A
        if (mem.total == 0) {
            return "N/A";
        }
        
        std::string result = core::math::formatBytes(mem.used * 1024);
        result += " / " + core::math::formatBytes(mem.total * 1024);
        result += " (" + std::to_string(mem.percent) + "%)";
        
        return result;
    }

    inline std::string getMemoryPercent() {
        MemoryInfo mem = detectMemory();
        return std::to_string(mem.percent) + "%";
    }

    inline std::string getSwapString() {
        std::string content = core::file::readProcFile("meminfo");
        if (content.empty()) {
            return "N/A";
        }

        unsigned long swap_total = 0;
        unsigned long swap_free = 0;

        std::istringstream iss(content);
        std::string line;
        
        while (std::getline(iss, line)) {
            try {
                if (line.find("SwapTotal:") == 0) {
                    size_t colon_pos = line.find(':');
                    if (colon_pos != std::string::npos) {
                        std::string num_str = line.substr(colon_pos + 1);
                        swap_total = std::stoul(core::strings::trim(num_str));
                    }
                } else if (line.find("SwapFree:") == 0) {
                    size_t colon_pos = line.find(':');
                    if (colon_pos != std::string::npos) {
                        std::string num_str = line.substr(colon_pos + 1);
                        swap_free = std::stoul(core::strings::trim(num_str));
                    }
                }
            } catch (...) {
                continue; // Skip parsing errors
            }
        }

        if (swap_total == 0) {
            return "0 B / 0 B (0%)";
        }

        unsigned long swap_used = swap_total - swap_free;
        unsigned long swap_percent = (swap_used * 100) / swap_total;
        
        std::string result = core::math::formatBytes(swap_used * 1024);
        result += " / " + core::math::formatBytes(swap_total * 1024);
        result += " (" + std::to_string(swap_percent) + "%)";
        
        return result;
    }
}
