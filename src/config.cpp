#include "config.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

std::map<std::string, bool> Config::config;
bool Config::loaded = false;

std::string Config::getConfigPath() {
    const char* home = std::getenv("HOME");
    if (!home) home = "/root";
    return std::string(home) + "/.config/speedfetch/config.json";
}

void Config::createDefaultConfig() {
    // Create default config with all items enabled
    config = {
        {"user", true},
        {"os", true},
        {"host", true},
        {"kernel", true},
        {"uptime", true},
        {"packages", true},
        {"shell", true},
        {"display", true},
        {"de", true},
        {"wm", true},
        {"wm_theme", true},
        {"theme", true},
        {"icons", true},
        {"font", true},
        {"cursor", true},
        {"terminal", true},
        {"terminal_font", true},
        {"cpu", true},
        {"gpu", true},
        {"memory", true},
        {"swap", true},
        {"disk", true},
        {"local_ip", true},
        {"locale", true}
    };
}

void Config::load() {
    if (loaded) return;
    
    createDefaultConfig();
    
    std::string config_path = getConfigPath();
    std::ifstream config_file(config_path);
    
    if (!config_file.is_open()) {
        // Config doesn't exist, use defaults
        loaded = true;
        return;
    }
    
    // Simple JSON parsing (without external library)
    std::string line;
    while (std::getline(config_file, line)) {
        // Look for "key": true/false patterns
        size_t quote_pos = line.find("\"");
        if (quote_pos == std::string::npos) continue;
        
        size_t quote_end = line.find("\"", quote_pos + 1);
        if (quote_end == std::string::npos) continue;
        
        std::string key = line.substr(quote_pos + 1, quote_end - quote_pos - 1);
        
        // Check if key exists in our default config
        if (config.find(key) != config.end()) {
            // Find the value (true or false)
            size_t true_pos = line.find("true", quote_end);
            size_t false_pos = line.find("false", quote_end);
            
            if (true_pos != std::string::npos && true_pos < false_pos) {
                config[key] = true;
            } else if (false_pos != std::string::npos) {
                config[key] = false;
            }
        }
    }
    
    config_file.close();
    loaded = true;
}

bool Config::isEnabled(const std::string& key) {
    if (!loaded) load();
    
    auto it = config.find(key);
    if (it != config.end()) {
        return it->second;
    }
    return true; // Default to enabled if key not found
}

std::vector<std::string> Config::getEnabledItems() {
    if (!loaded) load();
    
    std::vector<std::string> enabled;
    for (const auto& item : config) {
        if (item.second) {
            enabled.push_back(item.first);
        }
    }
    return enabled;
}
