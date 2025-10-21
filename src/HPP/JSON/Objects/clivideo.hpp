#ifndef __h_clivideo_h__
#define __h_clivideo_h__

#include <string>

//config file
#define CLIVIDEO_JSON "clivideo.json"

struct clivideo{
    std::string base;
    std::string mpvDefaults;
    std::vector<std::string> whitelist;
};


#endif