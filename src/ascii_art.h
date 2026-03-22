#ifndef ASCII_ART_H
#define ASCII_ART_H

#include <string>
#include <map>

class ASCIIArt {
public:
    static std::string getArt(const std::string& distro);
    static std::string getDistroType(const std::string& distro_name);
    
private:
    static const std::map<std::string, std::string> arts;
};

#endif // ASCII_ART_H
