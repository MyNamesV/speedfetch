#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>

namespace core::strings {
    // String trimming
    inline std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, last - first + 1);
    }

    inline std::string ltrim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        return str.substr(first);
    }

    inline std::string rtrim(const std::string& str) {
        size_t last = str.find_last_not_of(" \t\r\n");
        if (last == std::string::npos) return "";
        return str.substr(0, last + 1);
    }

    // Case conversion
    inline std::string toLower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    inline std::string toUpper(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    // String operations
    inline bool startsWith(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
    }

    inline bool endsWith(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    inline bool contains(const std::string& str, const std::string& substr) {
        return str.find(substr) != std::string::npos;
    }

    inline std::string replace(std::string str, const std::string& from, const std::string& to) {
        size_t pos = 0;
        while ((pos = str.find(from, pos)) != std::string::npos) {
            str.replace(pos, from.length(), to);
            pos += to.length();
        }
        return str;
    }

    // String splitting
    inline std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> result;
        std::istringstream stream(str);
        std::string item;
        while (std::getline(stream, item, delimiter)) {
            result.push_back(item);
        }
        return result;
    }

    inline std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = str.find(delimiter);
        while (end != std::string::npos) {
            result.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }
        result.push_back(str.substr(start));
        return result;
    }

    // String joining
    inline std::string join(const std::vector<std::string>& items, const std::string& delimiter = " ") {
        std::string result;
        for (size_t i = 0; i < items.size(); ++i) {
            result += items[i];
            if (i < items.size() - 1) result += delimiter;
        }
        return result;
    }
}
