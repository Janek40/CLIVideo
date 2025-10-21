#include "Menu/Menu.hpp"


std::vector<MenuItem> list_items(const std::filesystem::path& dir, const std::vector<std::string>& whitelist) {

    std::set<std::string> allow;
    for (auto& ext : whitelist) {
        // Normalize to ".ext" lowercase to match filesystem extensions
        std::string e = ext;
        if (!e.empty() && e[0] != '.') e = "." + e;
        allow.insert(to_lower(e));
    }

    std::vector<MenuItem> dirs;
    std::vector<MenuItem> files;

    for (auto& entry : std::filesystem::directory_iterator(dir)) {
        const std::filesystem::path p = entry.path();
        std::string name = p.filename().string();

        if (entry.is_directory()) {
            dirs.push_back({name, p, true});
        } else if (entry.is_regular_file()) {
            std::string e = to_lower(p.extension().string());
            if (allow.empty() || allow.count(e)) {
                files.push_back({name, p, false});
            }
        }
        // ignore other types (symlinks, sockets, etc.) for simplicity
    }

    std::sort(dirs.begin(), dirs.end(),
              [](const MenuItem& a, const MenuItem& b){ return a.label < b.label; });
    std::sort(files.begin(), files.end(),
              [](const MenuItem& a, const MenuItem& b){ return a.label < b.label; });

    std::vector<MenuItem> out;
    out.reserve(dirs.size() + files.size());
    out.insert(out.end(), dirs.begin(), dirs.end());
    out.insert(out.end(), files.begin(), files.end());
    return out;
}


void print_menu(const std::filesystem::path& cur, const std::vector<MenuItem>& items) {

    std::cout << "\n📂 " << cur.string() << "\n";
    std::cout << "----------------------------------------\n";
    if (items.empty()) {
        std::cout << "(no items)\n";
    } else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << (i + 1) << ". " << items[i].label
                      << (items[i].is_dir ? " /" : "") << "\n";
        }
    }
    std::cout << "\n[b] back   [q] quit\n";
    std::cout << "Select: ";
}

std::optional<size_t> parse_selection(const std::string& s, size_t maxN) {
    // return zero-based index if valid
    try {
        size_t pos = 0;
        int n = std::stoi(s, &pos);
        if (pos != s.size()) return std::nullopt; // had junk
        if (n >= 1 && (size_t)n <= maxN) return (size_t)(n - 1);
        return std::nullopt;
    } catch (...) {
        return std::nullopt;
    }
}



std::optional<std::filesystem::path> find_nearest_mpv_settings(const std::vector<std::filesystem::path>& stack) {

    // Walk from the deepest folder back to the base
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        std::filesystem::path candidate = *it / MPV_SETTINGS_NAME;
        std::error_code ec;
        if (std::filesystem::exists(candidate, ec) &&
            std::filesystem::is_regular_file(candidate, ec)) {
            return candidate;
        }
    }
    return std::nullopt;
}
