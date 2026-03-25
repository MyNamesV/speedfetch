#pragma once

#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

namespace core::math {
    // Format bytes to human-readable format
    inline std::string formatBytes(unsigned long bytes) {
        const char* units[] = {"B", "KB", "MB", "GB", "TB"};
        double size = static_cast<double>(bytes);
        int unitIdx = 0;
        
        while (size >= 1024.0 && unitIdx < 4) {
            size /= 1024.0;
            unitIdx++;
        }
        
        std::ostringstream oss;
        if (size >= 10.0) {
            oss << std::fixed << std::setprecision(0) << size << " " << units[unitIdx];
        } else {
            oss << std::fixed << std::setprecision(1) << size << " " << units[unitIdx];
        }
        return oss.str();
    }

    // Format frequency (MHz to GHz)
    inline std::string formatFreq(double mhz) {
        if (mhz >= 1000.0) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << (mhz / 1000.0) << " GHz";
            return oss.str();
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << mhz << " MHz";
        return oss.str();
    }

    // Format percentage
    inline std::string formatPercent(double value) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << value << "%";
        return oss.str();
    }

    // Clamp value between min and max
    template<typename T>
    inline T clamp(T value, T minVal, T maxVal) {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }
}
