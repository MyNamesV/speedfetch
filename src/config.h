#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <map>

class Config {
public:
    struct DisplayItem {
        std::string label;
        std::string key;
        bool enabled;
    };
    
    static void load();
    static bool isEnabled(const std::string& key);
    static std::vector<std::string> getEnabledItems();
    
private:
    static std::map<std::string, bool> config;
    static bool loaded;
    static std::string getConfigPath();
    static void createDefaultConfig();
};

#endif // CONFIG_H
