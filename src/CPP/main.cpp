#include <stdio.h>
#include <string>

#include "JSON/CliVideoReader.hpp"
#include "Menu/Menu.hpp"
#include "MPV/MpvStarter.hpp"


int main() {
    try {
        CliVideoReader reader;
        clivideo cfg = reader.getSettings();

        //path to defaults file
        std::filesystem::path mpvDefaultsPath = expand_tilde(cfg.mpvDefaults);

        std::filesystem::path base = expand_tilde(cfg.base);
        if (!std::filesystem::exists(base) || !std::filesystem::is_directory(base)) {
            std::cerr << "Base path is not a directory: " << base << "\n";
            return 2;
        }

        std::vector<std::filesystem::path> stack;
        stack.push_back(base);

        while (!stack.empty()) {
            std::filesystem::path cur = stack.back();

            clear_console();

            // compute active local settings for current location
            auto localMpv = find_nearest_mpv_settings(stack);

            std::cout << "Defaults: " << mpvDefaultsPath.string() << "\n";
            if (localMpv) {
                std::cout << "Local   : " << localMpv->string() << " (applies here)\n";
            } else {
                std::cout << "Local   : (none)\n";
            }


            std::vector<MenuItem> items = list_items(cur, cfg.whitelist);

            print_menu(cur, items);

            std::string input;
            std::getline(std::cin, input);
            if (input == "q" || input == "Q") break;
            if (input == "b" || input == "B") {
                if (stack.size() > 1) stack.pop_back();
                continue;
            }

            std::optional<size_t> idx = parse_selection(input, items.size());
            if (!idx) {
                std::cout << "Invalid selection.\n";
                continue;
            }
            const auto& picked = items[*idx];

            if (picked.is_dir) {
                stack.push_back(picked.path);
            } else {

                auto localMpv = find_nearest_mpv_settings(stack);

                std::vector<std::filesystem::path> extraSettings;
                if (localMpv) extraSettings.push_back(*localMpv);

                MpvStarter player(picked.path, mpvDefaultsPath, extraSettings);
                player.play();
            }
        }

        std::cout << "Bye.\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}