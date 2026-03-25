#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace core::file {
    // Read entire file contents
    inline std::string readFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return "";

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    // Read file line by line
    inline std::vector<std::string> readLines(const std::string& path) {
        std::vector<std::string> lines;
        std::ifstream file(path);
        if (!file.is_open()) return lines;

        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    // Read first line of file
    inline std::string readFirstLine(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return "";

        std::string line;
        std::getline(file, line);
        return line;
    }

    // Check if file exists
    inline bool exists(const std::string& path) {
        return std::ifstream(path).good();
    }

    // Read /proc file (common on Linux systems)
    inline std::string readProcFile(const std::string& filename) {
        return readFile("/proc/" + filename);
    }

    // Read /sys file (sysfs)
    inline std::string readSysFile(const std::string& filename) {
        return readFile("/sys/" + filename);
    }

    // Extract key-value from file (format: KEY=VALUE or KEY: VALUE)
    inline std::string getKeyValue(const std::string& content, const std::string& key, char sep = '=') {
        std::istringstream iss(content);
        std::string line;
        while (std::getline(iss, line)) {
            if (line.find(key) == 0) {
                size_t pos = line.find(sep);
                if (pos != std::string::npos) {
                    std::string value = line.substr(pos + 1);
                    if (!value.empty() && value[0] == '"') {
                        value = value.substr(1, value.find_last_not_of('"') + 1 - 1);
                    }
                    return value;
                }
            }
        }
        return "";
    }
}
