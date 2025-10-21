#include "JSON/CliVideoReader.hpp"

CliVideoReader::CliVideoReader() {

    std::ifstream configFile(CLIVIDEO_JSON);
    if (!configFile.is_open()) {
        std::ostringstream oss;
        oss << "Failed to open config file: " << CLIVIDEO_JSON;
        throw std::runtime_error(oss.str());
    }

    nlohmann::json j;
    try {
        configFile >> j;
    } catch (const nlohmann::json::parse_error& e) {
        std::ostringstream oss;
        oss << "JSON parse error in " << CLIVIDEO_JSON
            << ": " << e.what();
        throw std::runtime_error(oss.str());
    }

    configFile.close();

    // Required key check
    if (!j.contains("base")) {
        throw std::runtime_error("Missing required key 'base' in config file");
    }

    if (!j.contains("mpvDefaults")) {
        throw std::runtime_error("Missing required key 'mpvDefaults' in config file");
    }

    m_settings.base = j["base"].get<std::string>();
    m_settings.mpvDefaults = j["mpvDefaults"].get<std::string>();

    m_settings.whitelist.clear();

    if (j.contains("whitelist")) {
        if (!j["whitelist"].is_array()) {
            throw std::runtime_error("'whitelist' must be an array in config file");
        }

        for (const auto& item : j["whitelist"]) {
            if (!item.is_string()) {
                throw std::runtime_error("All elements of 'whitelist' must be strings");
            }
            m_settings.whitelist.push_back(item.get<std::string>());
        }
    } else {
        throw std::runtime_error("Warning: 'whitelist' not found in config file");
    }
}


clivideo CliVideoReader::getSettings(){
    return m_settings;
}

