#include "manage-notes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void edit_note(void) {
  char note_name[MAX_IN] = "notes/";
  printf("Enter the note name: ");
  fgets(note_name + 6, MAX_IN - 6, stdin);
  note_name[strcspn(note_name, "\n")] = '\0';

  FILE *file = fopen(note_name, "rb+");
  if (!file) {
    fprintf(stderr, "No note.\n");
    return;
  }

  unsigned char c;
  printf("This is the previus content: \n");
  printf("----------------------------------\n");
  while (fread(&c, sizeof c, 1, file) == 1)
    putchar(c);
  printf("----------------------------------\n");

  printf("\nIf you want to edit it or rewrite it press Enter.");
  if (getchar() != '\n')
    return;

  remove(note_name);
  file = fopen(note_name, "wb");
  if (!file) {
    perror("fopen");
    return;
  }
  unsigned max_len = 128, count = 0;
  int ch;
  char *buff = calloc(max_len, sizeof(*buff));
  printf("Press CTRL+D to end.\n");
  printf("Enter your note: ");

  while ((ch = getchar()) != EOF) {
    if (count >= max_len)
      buff = realloc(buff, max_len += 64);
    if (buff == NULL) {
      fprintf(stderr, "Error allocating space.\n");
      return;
    }
    buff[count++] = ch;
  }
  unsigned flag = fwrite(buff, 1, count, file);
  if (flag)
    printf("Successfully Edited.\n");
  clearerr(stdin);

  fflush(file);
  fclose(file);
}
