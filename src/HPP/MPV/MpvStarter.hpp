#ifndef __h_MpvStarter_h__
#define __h_MpvStarter_h__


#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <cstdlib>

class MpvStarter {
public:
    MpvStarter(const std::filesystem::path& videoFile,
               const std::filesystem::path& defaultSettings,
               const std::vector<std::filesystem::path>& extraSettings = {});

    // Build and return the full MPV command string
    std::string buildCommand() const;

    // Launch mpv using the current command
    void play() const;

private:
    std::filesystem::path m_videoFile;
    std::filesystem::path m_defaultSettings;
    std::vector<std::filesystem::path> m_extraSettings;
};

#endif
