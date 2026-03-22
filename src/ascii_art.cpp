#include "ascii_art.h"
#include <algorithm>

const std::map<std::string, std::string> ASCIIArt::arts = {
    {"ubuntu", R"(
                MMMMM   MMMMMM       
           MMMMMMMMM  MMMMMMMMMM     
         MMMMMMMMMMM  MMMMMMMMMM     
       MMMMMM         MMMMMMMMMM     
     MMMMMM            MMMMMMMM      
                          MMM    MM  
   MMMMM                       MMMMM 
 MMMMMMMMM                      MMMMM
MMMMMMMMMM                       MMMM
MMMMMMMMMM                       MMMM
 MMMMMMMMM                       MMMM
   MMMMM                        MMMMM
                               MMMMM 
    MMMMM               MMMM    MMM  
     MMMMMM           MMMMMMMM   M   
       MMMMMMM       MMMMMMMMMM      
         MMMMMMMMM   MMMMMMMMMM      
           MMMMMMMM  MMMMMMMMMM      
                 MMM   MMMMMM        
)"},
    
    {"fedora", R"(
             ###########             
         ###################         
      ################....#####      
    ##############..........++###    
   ##############..........++++###   
  ##############....#######+++++###  
 ##############....#########+++++### 
 ##############....#########+++++### 
###############....#########++++#####
###############.....#####++++++######
#####+++++...............+++++#######
####++++++..............+++##########
###++++########....################# 
##++++#########....################# 
##++++#########....################  
##+++++########....###############   
###++++++###......###############    
#####++..........##############      
#######+......##############         
  ######################             
)"},
    
    {"debian", R"(
                                           
             00000000000             
          0000000000000000000        
         0000            00000       
       0000                0000O     
      000                   0000     
     000         00    0     00      
     00         0            00      
     00        0             00      
     00        0        O    000     
     00         0    O0     0        
     00        0 00       00         
     00           0000000            
      000                            
       000                           
        00                           
         000                         
           000                       
              00                     
                                     
)"},
    
    {"arch", R"(
        /\\
       /  \\
      /    \\
     /      \\
    /   ||   \\
   /____||____\\)"},
    
    {"manjaro", R"(
      |||||||||
      |||||||||
      ||     ||
      ||  M  ||
      ||     ||
      |||||||||
      |||||||||)"},
    
    {"opensuse", R"(
        /   \\
       / SLE \\
      /   /   \\
     |   /  O  |
     |  /       |
      \\ \\     /
       \\_____/)"},
    
    {"centos", R"(
        __
       /  \\
      | CentOS |
      | _______ |
        \\    /
         \\__/)"},
    
    {"ubuntu-budgie", R"(
           *
          **
         ***
        ****
       *****
      *** ***
     **     **
    **       **)"},
    
    {"elementary", R"(
        ___
       /   \\
      / /* \\\\
     | [] (*) |
      \\   _  /
       \\_____/)"},
    
    {"pop-os", R"(
        /\\  pop!_
       /  \\  /
      /    \\/
     /    /\\
    /____/  \\)"},
    
    {"tux", R"(
        _____
       /     \\
      | Linux |
       \\_____/
        |   |
        |   |)"}
};

std::string ASCIIArt::getDistroType(const std::string& distro_name) {
    std::string lower = distro_name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    // Check for specific distros
    if (lower.find("ubuntu") != std::string::npos) {
        if (lower.find("budgie") != std::string::npos) return "ubuntu-budgie";
        return "ubuntu";
    }
    if (lower.find("fedora") != std::string::npos) return "fedora";
    if (lower.find("debian") != std::string::npos) return "debian";
    if (lower.find("arch") != std::string::npos) return "arch";
    if (lower.find("manjaro") != std::string::npos) return "manjaro";
    if (lower.find("suse") != std::string::npos || lower.find("opensuse") != std::string::npos) return "opensuse";
    if (lower.find("centos") != std::string::npos) return "centos";
    if (lower.find("elementary") != std::string::npos) return "elementary";
    if (lower.find("pop") != std::string::npos) return "pop-os";
    
    return "linux";
}

std::string ASCIIArt::getArt(const std::string& distro) {
    std::string distro_type = getDistroType(distro);
    
    auto it = arts.find(distro_type);
    if (it != arts.end()) {
        return it->second;
    }
    
    return arts.at("linux");
}
