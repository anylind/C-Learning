#include "manage-notes.h"
#include <stdio.h>
#include <string.h>

void show_content(void) {
  char note_name[MAX_IN] = "notes/";
  printf("Enter the note name: ");
  fgets(note_name + 6, MAX_IN - 6, stdin);
  note_name[strcspn(note_name, "\n")] = '\0';

  FILE *file = fopen(note_name, "rb");
  if (file == NULL) {
    fprintf(stderr, "No note.\n");
    return;
  }

  unsigned char c;
  printf("-------------------------------\n");
  while (fread(&c, sizeof c, 1, file) == 1)
    putchar(c);
  printf("-------------------------------\n");
  printf("Enter any key to continue. ");
  getchar();
}
