#pragma once

#include <string>
#include <vector>
#include "file.h"
#include "math.h"
#include "strings.h"
#include "exec.h"

namespace detect::disk {
    struct DiskInfo {
        std::string mount;
        unsigned long total;
        unsigned long used;
        unsigned long available;
        unsigned long percent;
    };

    inline std::vector<DiskInfo> detectDisks() {
        std::vector<DiskInfo> disks;
        
        // Use df command for disk info
        std::string df_out = core::exec::exec("df -B1 2>/dev/null | tail -n +2");
        if (df_out.empty()) {
            return disks;
        }

        std::istringstream iss(df_out);
        std::string line;
        
        while (std::getline(iss, line)) {
            if (line.empty()) continue;
            
            DiskInfo disk{};
            std::istringstream tokens(line);
            std::string device;
            unsigned long percent = 0;
            
            try {
                tokens >> device >> disk.total >> disk.used >> disk.available >> percent;
                
                // Parse the mount point (everything after percent and spaces)
                std::string remaining;
                std::getline(tokens, remaining);
                
                // Trim whitespace from remaining
                size_t start = remaining.find_first_not_of(" \t");
                if (start != std::string::npos) {
                    disk.mount = remaining.substr(start);
                } else {
                    continue; // Skip if no mount point
                }
                
                disk.percent = percent;
                
                // Calculate percent if not provided
                if (disk.total > 0 && disk.percent == 0) {
                    disk.percent = (disk.used * 100) / disk.total;
                }
                
                disks.push_back(disk);
            } catch (...) {
                continue; // Skip malformed lines
            }
        }

        return disks;
    }

    inline DiskInfo detectRootDisk() {
        auto disks = detectDisks();
        for (const auto& disk : disks) {
            if (disk.mount == "/") {
                return disk;
            }
        }
        if (!disks.empty()) {
            return disks[0];
        }
        return DiskInfo{};
    }

    inline std::string getRootDiskString() {
        // Use df -h for most accurate results
        std::string df_out = core::exec::exec("df -h / 2>/dev/null | tail -1");
        if (!df_out.empty()) {
            std::istringstream tokens(df_out);
            std::string fs, size_str, used_str, avail_str, percent_str, mount;
            
            if ((tokens >> fs >> size_str >> used_str >> avail_str >> percent_str >> mount)) {
                // Remove % from percent
                if (!percent_str.empty() && percent_str.back() == '%') {
                    percent_str.pop_back();
                }
                if (!percent_str.empty()) {
                    return used_str + " / " + size_str + " (" + percent_str + "%)";
                }
            }
        }
        
        return "N/A";
    }
}
