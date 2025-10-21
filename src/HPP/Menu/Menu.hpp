#ifndef __h_menu_h__
#define __h_menu_h__

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <filesystem>
#include <cctype>
#include <cstdlib>     // getenv
#include <optional>

#include "Util/Util.hpp"

// Which filename to look for in folders:
#define MPV_SETTINGS_NAME "mpv.settings"

struct MenuItem {
    std::string label; // what to print
    std::filesystem::path path;
    bool is_dir;
};

    std::vector<MenuItem> list_items(const std::filesystem::path& dir, const std::vector<std::string>& whitelist);
    void print_menu(const std::filesystem::path& cur, const std::vector<MenuItem>& items);
    std::optional<size_t> parse_selection(const std::string& s, size_t maxN);

    std::optional<std::filesystem::path> find_nearest_mpv_settings(const std::vector<std::filesystem::path>& stack);


#endif