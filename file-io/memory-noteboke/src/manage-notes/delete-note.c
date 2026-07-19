#include <stdio.h>
#include <string.h>

#define MAX_IN 41

void delete_note(void) {
  char note_name[MAX_IN] = "notes/";
  printf("Enter the name of the note you want to delete: (%d characters) ",
         MAX_IN - 6);
  if (fgets(note_name + 6, MAX_IN - 6, stdin) == NULL) {
    fprintf(stderr, "Inpute Error!\n");
    return;
  }

  note_name[strcspn(note_name, "\n")] = '\0';
  if (!remove(note_name))
    printf("Deleted successfuly.\n");
  else
    perror("remove");
}
