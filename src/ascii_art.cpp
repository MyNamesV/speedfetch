#include "ascii_art.h"
#include <algorithm>

const std::map<std::string, std::string> ASCIIArt::arts = {
    {"ubuntu", R"(
                00000   MMMMMM       
           0MMMMMMMM  MMMMMMMMMM     
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
                                           
             ddddddddddddd             
          ddddddddddddddddddd        
         dddd            ddddd       
       dddd                ddddd     
      ddd                   dddd     
     ddd         dd    d     dd      
     dd         d            dd      
     dd        d             dd      
     dd        d        d    ddd     
     dd         d    dd     d        
     dd        d dd       dd         
     dd           ddddddd            
      ddd                            
       ddd                           
        dd                           
         dddd                         
           ddd                       
              dd                     
                                     
)"},
    
    {"arch", R"(
                  A                  
                 AAA                 
                 AAA                 
                AAAAA                
               AAAAAAA               
               AAAAAAAA              
                AAAAAAAA             
            AAAAAAAAAAAAA            
            AAAAAAAAAAAAA            
           AAAAAAAAAAAAAAA           
          AAAAAAAAAAAAAAAAA          
         AAAAAAAA   AAAAAAAA         
        AAAAAAA       AAAAAAA        
       AAAAAAA         AAAAAAA       
      AAAAAAAA         AAAAA         
     AAAAAAAAA         AAAAAAAA      
    AAAAAAAAAA         AAAAAAAAAA    
   AAAAAA                   AAAAAA   
  AAA                           AAAA 
AA                                 AA
)"},
    
    {"manjaro", R"(
QQQQQQQQQQQQQQQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQQQQQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQQQQQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQQQQQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQQQQQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQQQQQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ               QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
QQQQQQQQQQQ  QQQQQQQQQQQ  QQQQQQQQQQQ
)"},
    
    {"opensuse", R"(
                                             
              UUUUUUUUU              
          UUUUUUUUUUUUUUUUU          
        UUUUUUU       UUUUUUU        
      UUUUU               UUUUU      
     UUUU   RQQQQQ          UUUU     
    UUUUUUUQUUUUUUUUUQQQ      UUU    
   UUUUUUUUUUUUUUUU      UQ   XUUU   
   UUUUUUUUUUUUUUU  UU  Q UQ   UUUU  
  UUUUUUUUUUUUUUUU UUQQQU UU   TUUU  
  UUUUUUUUUUUU UUUQ  UU  QUUU   UUU  
  AUUUUUUUUUUUQ    UQQQQUUUU   SUUC  
   UUUUUUUUUUUUUSQQ        QQ  UUU   
   AUUUUUUUUUUUUUUUUUTQQQUUT  QUUA   
    AUUUUUUUUUUUUUUUUUU      QUUA    
     AUUUQ                 QUUUA     
      AAUUUQQ           SQUUUAA      
        AAUUUUSQQQQQQQQUUUUAA        
           AAAAUUUUUUUEAAA           
                                     
)"},
    
    {"centos", R"(
                                                 
                 ..                  
                .===.                
              .=======.              
     .======.====.=.####.######:     
     .====.======.=.######.####:     
     .==:==.-====.=.####+.##:##:     
     .-.==.==.===.=.###.##.##.+:     
     .======.==.=.=.#.##.*#####.     
   .#-=======::==.=.##::#######=%.   
 .###=:::::::::.:: ::.:::::::::=%%%. 
 .###-:::::::::.:. .:.:::::::::=%%%. 
   .#-%%%%%%%:-%%.=.==::========%.   
     .%%%%%#.%%.%.=.=.==.-=====.     
     .*.%%.%%.%%%.=.===.==.==.-:     
     .%%:%%.*%%%%.=.====-.==:==:     
     .%%%%.%%%%%%.=.======.====:     
     .%%%%%%.%%%%.=.====.======:     
              .=======.              
                .===.                
                  .                  
   
)"},

    {"pop-os", R"(
             AAAAAAAAAAA             
         AAAAAAAAAAAAAAAAAAA         
      AAAAAAAAA AAAAAAAAAAAAAAA      
    AAAAAA         AAAAAAAAAAAAAA    
   AAAAA     A       AAAAAAAAAAAAA   
  AAAAAA     AAA     AAAAAAAAAAAAAA  
 AAAAAAA     AAAA    AAAA   AAAAAAAA 
AAAAAAAAA     AAA    AAA     AAAAAAA 
AAAAAAAAAA          AAAA    AAAAAAAAA
AAAAAAAAAAA       AAAAAA   AAAAAAAAAA
AAAAAAAAAAAA     AAAAAA   AAAAAAAAAAA
AAAAAAAAAAAAA    AAAAAA  AAAAAAAAAAAA
AAAAAAAAAAAAAA    AAAAAAAAAAAAAAAAAAA
 AAAAAAAAAAAAAA   AAAA  AAAAAAAAAAAA 
  AAAAAAAAAAAAAAAAAAAAA AAAAAAAAAAA  
   AAAAAA                   AAAAAA   
    AAAAA                   AAAAA    
      AAAAAAAAAAAAAAAAAAAAAAAAA      
         AAAAAAAAAAAAAAAAAAA         
            AAAAAAAAAAAAA            
)"},
    
    {"tux", R"(
               AAAAAAA               
             AAAAAAAAAAA             
            AAAAAAAAAAAAA            
            AAAAAAAAAAAAA            
            A A AA AA AAA            
            AAAAAAAAA AAAA           
            AAAAAAAAAAAAAA           
             AAAAAAAAAAAAAA          
            A  AAAA    AAAAA         
          AA            AAAAA        
         AA              AAAAAA      
        AAA               AAAAAA     
       AAA                 AAAAA     
      AAA                  AAAAAA    
     AAAA                  AAAAAA    
     AAAA                  AAAAAA    
     AAAAA               AAAAAAAA    
 AAAAAAAAAAA             AAAAAAAAA   
 AAAAAAAAAAAAA           AAAAAAAAAA  
 AAAAAAAAAAA           AAAAAAAAAAAAAA
AAAAAAAAAAAAAAA     AAAAAAAAAAAAAAA  
 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA     
        AAAAA            AAAAA       
)"}
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
