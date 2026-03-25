#pragma once

#include <string>
#include <vector>
#include "exec.h"
#include "strings.h"

namespace detect::network {
    struct NetworkInterface {
        std::string name;
        std::string ip;
        std::string mac;
        std::string status;
    };

    inline std::vector<NetworkInterface> detectNetworkInterfaces() {
        std::vector<NetworkInterface> interfaces;
        
        // Use ip command if available
        std::string ip_out = core::exec::exec("ip addr show 2>/dev/null");
        if (ip_out.empty()) {
            return interfaces;
        }

        std::istringstream iss(ip_out);
        std::string line;
        NetworkInterface current;
        
        while (std::getline(iss, line)) {
            if (line.empty()) continue;
            
            // Parse interface lines (start with number and colon)
            if (std::isdigit(line[0])) {
                if (!current.name.empty()) {
                    interfaces.push_back(current);
                }
                
                size_t colon_pos = line.find(':');
                if (colon_pos != std::string::npos) {
                    current.name = line.substr(colon_pos + 2);
                    // Remove trailing colon and status flags
                    size_t space_pos = current.name.find(' ');
                    if (space_pos != std::string::npos) {
                        current.name = current.name.substr(0, space_pos);
                    }
                }
                
                // Check if UP
                if (line.find("<UP") != std::string::npos) {
                    current.status = "UP";
                } else {
                    current.status = "DOWN";
                }
            }
            // Parse IPv4 addresses
            else if (line.find("inet ") != std::string::npos) {
                size_t inet_pos = line.find("inet ") + 5;
                size_t slash_pos = line.find('/', inet_pos);
                if (slash_pos != std::string::npos) {
                    current.ip = line.substr(inet_pos, slash_pos - inet_pos);
                }
            }
            // Parse MAC addresses
            else if (line.find("link/ether ") != std::string::npos) {
                size_t ether_pos = line.find("link/ether ") + 11;
                size_t space_pos = line.find(' ', ether_pos);
                if (space_pos != std::string::npos) {
                    current.mac = line.substr(ether_pos, space_pos - ether_pos);
                }
            }
        }
        
        if (!current.name.empty()) {
            interfaces.push_back(current);
        }
        
        return interfaces;
    }

    inline std::string getPrimaryIP() {
        // Try direct approach with hostname -I
        std::string ip = core::exec::exec("hostname -I 2>/dev/null | awk '{print $1}'");
        if (!ip.empty() && ip != "127.0.0.1" && ip[0] != '$') {
            return ip;
        }
        
        // Fallback: parse ip addr
        auto interfaces = detectNetworkInterfaces();
        
        for (const auto& iface : interfaces) {
            if (!iface.ip.empty() && iface.name != "lo") {
                return iface.ip;
            }
        }
        
        return "N/A";
    }
}
