#include <dirent.h>
#include <stdio.h>
#include <string.h>

void show_notes(void) {
  DIR *dir = opendir("notes/");
  int state = 0;
  struct dirent *entry;

  printf("-----------------\n");
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;
    printf(" - %s\n", entry->d_name);
    state = 1;
  }
  if (!state)
    printf("There are no notes.\n");
  printf("-----------------\n");
}
