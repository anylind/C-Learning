#include "manage-notes.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void delete_all(void) {
  printf("This action will remove all notes if you agree press Enter.\n if you "
         "don`t press any other keys.");
  if (getchar() != '\n')
    return;
  DIR *dir = opendir("notes");
  if (!dir) {
    perror("opendir");
    return;
  }

  int state = 0;
  char path[MAX_IN] = "notes/";
  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;
    for (int i = 6; i < (MAX_IN - 6); ++i)
      path[i] = '\0';
    strcpy(path + 6, entry->d_name);
    state = 1;
    if (remove(path)) {
      perror("remove");
      return;
    }
  }
  if (state)
    printf("\nSuccessfully deleted.\n");
  else
    printf("\nThere are no note.\n");
}
