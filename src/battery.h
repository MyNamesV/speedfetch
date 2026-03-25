#pragma once

#include <string>
#include <vector>
#include "file.h"
#include "exec.h"
#include "strings.h"

namespace detect::battery {
    struct BatteryInfo {
        std::string status;
        int percent;
        std::string health;
        std::string technology;
    };

    inline std::vector<BatteryInfo> detectBatteries() {
        std::vector<BatteryInfo> batteries;
        
        // Check /sys/class/power_supply
        std::string power_supply_dir = "/sys/class/power_supply";
        std::string ls_out = core::exec::exec("ls " + power_supply_dir + " 2>/dev/null | grep -i bat");
        
        std::istringstream iss(ls_out);
        std::string battery;
        
        while (std::getline(iss, battery)) {
            if (battery.empty()) continue;
            
            BatteryInfo bat{};
            std::string base = power_supply_dir + "/" + battery + "/";
            
            bat.status = core::file::readFirstLine(base + "status");
            bat.health = core::file::readFirstLine(base + "health");
            bat.technology = core::file::readFirstLine(base + "technology");
            
            // Get capacity
            std::string capacity_str = core::file::readFirstLine(base + "capacity");
            bat.percent = capacity_str.empty() ? 0 : std::stoi(capacity_str);
            
            if (bat.percent > 0 || !bat.status.empty()) {
                batteries.push_back(bat);
            }
        }
        
        return batteries;
    }

    inline std::string getBatteryString() {
        auto batteries = detectBatteries();
        
        if (batteries.empty()) {
            return "N/A";
        }
        
        std::string result;
        for (size_t i = 0; i < batteries.size(); ++i) {
            result += batteries[i].status;
            if (batteries[i].percent > 0) {
                result += " (" + std::to_string(batteries[i].percent) + "%)";
            }
            if (i < batteries.size() - 1) {
                result += ", ";
            }
        }
        
        return result;
    }
}
