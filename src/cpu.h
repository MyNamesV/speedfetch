#pragma once

#include <string>
#include <vector>
#include "file.h"
#include "exec.h"
#include "math.h"
#include "strings.h"

namespace detect::cpu {
    struct CPUInfo {
        std::string model;
        std::string brand;
        unsigned int cores;
        unsigned int threads;
        double frequency;
        std::string cache;
    };

    inline CPUInfo detectCPU() {
        CPUInfo info{};
        info.cores = 1;
        info.threads = 1;
        info.frequency = 0.0;

        std::string content = core::file::readProcFile("cpuinfo");
        if (content.empty()) {
            return info;
        }

        std::istringstream iss(content);
        std::string line;
        bool found_model = false;
        
        while (std::getline(iss, line)) {
            try {
                if (!found_model && line.find("model name") != std::string::npos) {
                    size_t pos = line.find(':');
                    if (pos != std::string::npos) {
                        info.model = core::strings::trim(line.substr(pos + 1));
                        // Remove frequency suffix if present
                        size_t at_pos = info.model.find(" @ ");
                        if (at_pos != std::string::npos) {
                            info.model = info.model.substr(0, at_pos);
                        }
                        found_model = true;
                    }
                }
                
                if (line.find("cpu cores") != std::string::npos) {
                    size_t pos = line.find(':');
                    if (pos != std::string::npos) {
                        info.cores = std::stoi(core::strings::trim(line.substr(pos + 1)));
                    }
                }
                
                if (line.find("siblings") != std::string::npos) {
                    size_t pos = line.find(':');
                    if (pos != std::string::npos) {
                        info.threads = std::stoi(core::strings::trim(line.substr(pos + 1)));
                    }
                }
                
                if (line.find("cpu MHz") != std::string::npos) {
                    size_t pos = line.find(':');
                    if (pos != std::string::npos) {
                        info.frequency = std::stod(core::strings::trim(line.substr(pos + 1)));
                    }
                }
                
                if (line.find("cache size") != std::string::npos && info.cache.empty()) {
                    size_t pos = line.find(':');
                    if (pos != std::string::npos) {
                        info.cache = core::strings::trim(line.substr(pos + 1));
                    }
                }
            } catch (...) {
                continue; // Skip any parsing errors
            }
        }

        return info;
    }

    inline std::string getCPUString() {
        CPUInfo info = detectCPU();
        std::string result = info.model.empty() ? "N/A" : info.model;
        
        if (info.cores > 1) {
            result += " (" + std::to_string(info.cores) + " cores";
            if (info.threads > info.cores) {
                result += ", " + std::to_string(info.threads) + " threads";
            }
            result += ")";
        }
        
        return result;
    }

    inline std::string getCPUFrequency() {
        CPUInfo info = detectCPU();
        if (info.frequency > 0.0) {
            return core::math::formatFreq(info.frequency);
        }
        return "N/A";
    }
}
