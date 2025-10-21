#include "MPV/MpvStarter.hpp"

MpvStarter::MpvStarter(const std::filesystem::path& videoFile,
                       const std::filesystem::path& defaultSettings,
                       const std::vector<std::filesystem::path>& extraSettings)
    : m_videoFile(videoFile),
      m_defaultSettings(defaultSettings),
      m_extraSettings(extraSettings) {}

std::string MpvStarter::buildCommand() const {
    std::ostringstream cmd;

    // Base mpv command
    cmd << "mpv";

    // Always include the defaults file
    cmd << " --include=\"" << m_defaultSettings.string() << "\"";

    // Append any additional (folder-specific) settings
    for (const auto& extra : m_extraSettings) {
        cmd << " --include=\"" << extra.string() << "\"";
    }

    // Finally, the target video file
    cmd << " \"" << m_videoFile.string() << "\"";

    return cmd.str();
}

void MpvStarter::play() const {
    std::string command = buildCommand();

    std::cout << "▶ Running command:\n" << command << "\n\n";
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "mpv exited with code " << result << "\n";
    }
}