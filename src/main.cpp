#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

int main() {

  // getting the environment variables placed in your hyprland.conf by the
  // install.sh script

  const char *wallpaperDelay = getenv("WALLPAPER_DELAY");
  char *wallpaperDelayEnd{};
  int delayMins = std::strtol(wallpaperDelay, &wallpaperDelayEnd, 10);
  printf("%s", "Randomizing wallpaper... \n");

  // grabbing last used wallpaper to avoid reusing it

  FILE *fpipe;
  char getPrevWallpaper[] = "hyprctl --instance 0 hyprpaper listactive";
  char c = 0;

  if (0 == (fpipe = (FILE *)popen(getPrevWallpaper, "r"))) {
    perror("popen() failed");
    return 1;
  }

  char delim[] = "/\n";
  char *prevWallpaper = new char[256];
  int i = 0;
  bool readOrWrite = false;
  while (fread(&c, sizeof c, 1, fpipe)) {
    if (c == *(delim + 1)) {
      break;
    }
    if (c == *(delim + 0)) {
      readOrWrite = true;
    }
    if (readOrWrite == true) {
      *(prevWallpaper + i) = c;
      i++;
    }
  }
  pclose(fpipe);

  printf("Previous wallpaper: %s \n", prevWallpaper);

  int iterationOverflow = 0;
  char getNextWallpaper[] = "ls -1 $WALLPAPER_DIR/{*,*} | shuf -n 1";
  c = 0;

  while (true) {
    FILE *npipe;
    if (0 == (npipe = (FILE *)popen(getNextWallpaper, "r"))) {
      perror("popen() failed");
    }

    char nextWallpaper[256];
    std::memset(nextWallpaper, '\0', sizeof(nextWallpaper));
    i = 0;
    c = 0;

    while (fread(&c, sizeof c, 1, npipe)) {
      if (c == delim[1]) {
        break;
      }
      *(nextWallpaper + i) = c;
      i++;
      if (i == 256) {
        printf("%s", "ERROR: file string size too long!");
        return 1;
      }
    }
    pclose(npipe);

    printf("Next wallpaper: %s\n", nextWallpaper);
    if (strcmp(nextWallpaper, prevWallpaper) == 0) {
      printf("%s\n", "Wallpapers are the same, retrying...");
      iterationOverflow++;
      if (iterationOverflow < 15) {
      } else {
        printf("%s", "Too many attempts...");
        break;
      }
    } else if (nextWallpaper != prevWallpaper) {
      char postWallpaperCommand[1024] =
          "hyprctl -q --instance 0 hyprpaper preload ";
      strcat(postWallpaperCommand, nextWallpaper);
      strcat(postWallpaperCommand,
             "\nhyprctl -q --instance 0 hyprpaper wallpaper \",");
      strcat(postWallpaperCommand, nextWallpaper);
      strcat(postWallpaperCommand,
             "\"\nsleep 0.2\nhyprctl -q --instance 0 hyprpaper unload ");
      strcat(postWallpaperCommand, nextWallpaper);
      system(postWallpaperCommand);
      if (delayMins > 0) {
        sleep(delayMins * 60);
      } else
        break;
    }
  }

  return 0;
};
