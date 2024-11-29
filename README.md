## Description:
randhyprpaper is a simple c++ script that randomizes your wallpaper based off of environment variables it will plant into your hyprland.conf. Includes a bash install script for easy setup.

## Requirements:
1. hyprland (duhh)
2. hyprpaper (also duhh)
3. ninja
4. cmake
5. git

## Installation:
Copy the following commands into your terminal
```bash
sudo pacman -S cmake ninja git
git clone https://github.com/CORVUS047/randhyprpaper.git
cd randhyprpaper
bash install.sh
```
randhyprpaper requires a restart of hyprland in order to function properly!!!

## Configuration
Configuration options are automatically set in your hyprland.conf file via environment variables.
Any time you edit these variables hyprland must be reset for them to take effect.
