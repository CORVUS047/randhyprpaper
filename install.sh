#!/bin/bash
echo "Enter a directory for your wallpapers (absolute path):"
read wallpaperDirectory
echo "Enter the time in minutes that you want between wallpaper changes:"
read wallpaperDelay
echo "env = WALLPAPER_DIR,$wallpaperDirectory" >>~/.config/hypr/hyprland.conf
echo "env = WALLPAPER_DELAY,$wallpaperDelay" >>~/.config/hypr/hyprland.conf
echo "exec-once = sleep 9 && randpaper" >>~/.config/hypr/hyprland.conf
cmake -GNinja -S . -B build
cd build
ninja
sudo mv randpaper /usr/local/bin
echo "
NOTE: Randpaper requires a restart of hyprland or a reboot.
If you want to change your wallpaper directory or wallpaper delay
edit the WALLPAPER_DIR and WALLPAPER_DELAY environment variables 
in your hyprland.conf file."
