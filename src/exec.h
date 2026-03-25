#pragma once

#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>

namespace core::exec {
    // Execute shell command and get output
    inline std::string exec(const std::string& cmd) {
        FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe) return "";

        std::string result;
        char buffer[512];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        pclose(pipe);

        // Remove trailing newlines
        while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
            result.pop_back();
        }

        return result;
    }

    // Execute command and return exit code
    inline int execCode(const std::string& cmd) {
        return system(cmd.c_str());
    }

    // Check if command exists
    inline bool commandExists(const std::string& cmd) {
        std::string check = "which " + cmd + " 2>/dev/null >/dev/null";
        return system(check.c_str()) == 0;
    }

    // Get output of multiple variations of a command (first to succeed)
    inline std::string execMultiple(const std::vector<std::string>& commands) {
        for (const auto& cmd : commands) {
            std::string result = exec(cmd);
            if (!result.empty() && result != "N/A") {
                return result;
            }
        }
        return "N/A";
    }
}
