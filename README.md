🎬 CLIVideo — Terminal-Based Media Browser & MPV Launcher

CLIVideo is a lightweight, console-based media navigator and playback tool designed for organizing and watching video libraries directly from the terminal. It provides a simple text-driven interface to browse folders, apply playback configurations, and launch videos in mpv with both global and per-folder settings.

✨ Key Features

Interactive CLI Browser
Navigate your media collection through numbered menus — explore folders, go back, or quit at any time.
Example:
1. BBC Red Dwarf
2. BBC Doctor Who
3. BBC Blackadder

Per-Folder Settings System
Each folder can include its own mpv.settings file that overrides or adds to global defaults (mpv.default.settings).
For example, brightness or zoom preferences can differ per show.

Smart Settings Inheritance
When navigating subfolders, the program automatically keeps track of the nearest mpv.settings file.
If a folder doesn’t have one, CLIVideo falls back to the default global configuration.

MPV Integration
Videos are launched via the MpvStarter class, which builds and executes an mpv command with the correct settings.
Example command:
mpv --include="mpv.default.settings" --include="BBC Red Dwarf/mpv.settings" "S01E02.mkv"

Configurable via JSON
Settings are stored in a simple clivideo.json file:
{
    "base": "~/Programs/CLIVideo/TV Shows",
    "mpvDefaults": "mpv.default.settings",
    "whitelist": ["mkv", "mp4"]
}
This defines the media base path, default MPV config file, and which file extensions to list.

Cross-Platform & Dependency-Free
Built in modern C++17 using only the standard library (<filesystem>, <iostream>, <vector>).
No external dependencies beyond mpv itself.

⚙️ Typical Workflow

Launch the program from the terminal.

Browse into a show or season folder.

Select a video file by number.

CLIVideo launches mpv with the appropriate default + local configuration files.
