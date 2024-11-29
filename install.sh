#!/bin/bash
echo "Enter a directory for your wallpapers (absolute path):"
read wallpaperDirectory
echo "Enter the location of your hyprland.conf file (absolute path):"
read hyprlandConfig
echo "Enter the time in minutes that you want between wallpaper changes (0 to disable wallpaper changing):"
read wallpaperDelay
echo "env = WALLPAPER_DIR,$wallpaperDirectory" >>$hyprlandConfig
echo "env = WALLPAPER_DELAY,$wallpaperDelay" >>$hyprlandConfig
echo "exec-once = sleep 1 && randhyprpaper" >>$hyprlandConfig
cmake -GNinja -S . -B build
cd build
ninja
sudo mv randhyprpaper /usr/local/bin
echo "
NOTE: randhyprpaper requires a restart of hyprland or a reboot.
If you want to change your wallpaper directory or wallpaper delay
edit the WALLPAPER_DIR and WALLPAPER_DELAY environment variables 
in your hyprland.conf file."
