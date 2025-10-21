#ifndef __h_CliVideoReader_h__
#define __h_CliVideoReader_h__

#include <nlohmann/json.hpp>
#include "Objects/clivideo.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>

class CliVideoReader{

public:

    CliVideoReader();
    clivideo getSettings();

private:
    clivideo m_settings; 
};

#endif