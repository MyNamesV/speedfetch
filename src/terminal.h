#pragma once

#include <string>
#include "exec.h"

namespace detect::terminal {
    inline std::string getTerminal() {
        std::string term = core::exec::exec("echo $TERM");
        if (term.empty() || term == "$TERM") {
            term = core::exec::exec("echo $COLORTERM");
        }
        return term.empty() || term[0] == '$' ? "N/A" : term;
    }

    inline std::string getTerminalProgram() {
        // Try to get actual terminal program from parent process
        std::string ppid_term = core::exec::exec("ps -p $PPID -o comm= 2>/dev/null | head -1");
        
        if (!ppid_term.empty() && ppid_term[0] != '$') {
            // Clean up common terminal names
            if (ppid_term.find("bash") != std::string::npos) return "Bash";
            if (ppid_term.find("zsh") != std::string::npos) return "Zsh";
            if (ppid_term.find("fish") != std::string::npos) return "Fish";
            if (ppid_term.find("sh") != std::string::npos) return "Shell";
            if (ppid_term.find("tmux") != std::string::npos) return "Tmux";
            if (ppid_term.find("screen") != std::string::npos) return "Screen";
            if (ppid_term.find("konsole") != std::string::npos) return "Konsole";
            if (ppid_term.find("gnome-terminal") != std::string::npos) return "GNOME Terminal";
            if (ppid_term.find("xterm") != std::string::npos) return "XTerm";
            if (ppid_term.find("qterminal") != std::string::npos) return "QTerminal";
            if (ppid_term.find("termite") != std::string::npos) return "Termite";
            if (ppid_term.find("kitty") != std::string::npos) return "Kitty";
            if (ppid_term.find("alacritty") != std::string::npos) return "Alacritty";
            
            // Return as-is if recognized
            return ppid_term;
        }
        
        return "N/A";
    }
}
