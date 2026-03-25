#pragma once

#include <string>
#include "exec.h"
#include "strings.h"

namespace detect::gpu {
    struct GPUInfo {
        std::string name;
        std::string driver;
        std::string vendor;
    };

    inline GPUInfo detectGPU() {
        GPUInfo info;
        
        // First try lspci - most reliable for GPU detection
        std::string lspci_out = core::exec::exec("lspci 2>/dev/null | grep -iE '(vga|3d|display|video)' | head -1");
        if (!lspci_out.empty()) {
            size_t colon_pos = lspci_out.find(": ");
            if (colon_pos != std::string::npos) {
                info.name = lspci_out.substr(colon_pos + 2);
            }
        }
        
        // Try nvidia-smi for NVIDIA GPUs
        if (info.name.empty() || info.name.find("NVIDIA") != std::string::npos) {
            std::string nvidia_out = core::exec::exec("nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null | head -1");
            if (!nvidia_out.empty() && nvidia_out[0] != '$') {
                return GPUInfo{nvidia_out, "", "NVIDIA"};
            }
        }
        
        // Try AMD rocm-smi
        if (info.name.empty() || info.name.find("AMD") != std::string::npos) {
            std::string amd_out = core::exec::exec("rocm-smi --showid 2>/dev/null | grep -v 'GPU' | head -1");
            if (!amd_out.empty() && amd_out[0] != '$') {
                return GPUInfo{amd_out, "", "AMD"};
            }
        }
        
        // Try glxinfo for additional info
        if (info.name.empty()) {
            std::string glx_out = core::exec::exec("glxinfo -B 2>/dev/null | grep 'Device:' | head -1");
            if (!glx_out.empty()) {
                size_t pos = glx_out.find("Device: ");
                if (pos != std::string::npos) {
                    info.name = glx_out.substr(pos + 8);
                }
            }
        }

        return info;
    }

    inline std::string getGPUString() {
        GPUInfo info = detectGPU();
        
        if (info.name.empty()) {
            return "N/A";
        }
        
        std::string name = info.name;
        
        // Clean up lspci output - remove vendor/device codes
        // Format: "VENDOR GPU_NAME [XXXX:XXXX]"
        size_t bracket_pos = name.rfind("[");
        if (bracket_pos != std::string::npos) {
            // Remove the [XXXX:XXXX] part and anything after
            name = name.substr(0, bracket_pos);
        }
        
        // Trim whitespace
        size_t end = name.find_last_not_of(" \t");
        if (end != std::string::npos) {
            name = name.substr(0, end + 1);
        }
        
        return name;
    }
}
