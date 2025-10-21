#ifndef __h_Util_h__
#define __h_Util_h__

#include <string>
#include <algorithm>
#include <cstdlib>

void clear_console();

std::string to_lower(std::string s);
std::string expand_tilde(const std::string& p);


#endif