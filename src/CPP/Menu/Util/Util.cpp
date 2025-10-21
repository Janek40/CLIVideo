#include "Menu/Util/Util.hpp"


void clear_console() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}


std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

std::string expand_tilde(const std::string& p) {
    if (p.empty()) return p;
    if (p == "~") {
        const char* home = std::getenv("HOME");
        return home ? std::string(home) : p;
    }
    if (p.rfind("~/", 0) == 0) {
        const char* home = std::getenv("HOME");
        if (!home) return p;
        return std::string(home) + "/" + p.substr(2);
    }
    return p;
}