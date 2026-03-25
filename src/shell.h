#pragma once

#include <string>
#include "exec.h"
#include "file.h"

namespace detect::shell {
    inline std::string getShell() {
        std::string shell_env = core::exec::exec("echo $SHELL");
        if (shell_env.empty()) {
            return "N/A";
        }
        
        // Get just the shell name (e.g., bash from /bin/bash)
        size_t last_slash = shell_env.find_last_of('/');
        if (last_slash != std::string::npos) {
            return shell_env.substr(last_slash + 1);
        }
        
        return shell_env;
    }

    inline std::string getShellVersion() {
        std::string shell = getShell();
        if (shell == "N/A" || shell.empty()) {
            return "N/A";
        }
        
        // Get version of shell
        std::string version = core::exec::exec(shell + " --version 2>/dev/null | head -1");
        if (version.empty()) {
            return "N/A";
        }
        
        return version;
    }
}
