#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_IN 41

void add_note(void) {
  char note_name[MAX_IN] = "notes/";
  printf("Enter an Special name for this note: (%d characters) ", MAX_IN - 6);

  if (fgets(note_name + 6, MAX_IN - 6, stdin) == NULL) {
    fprintf(stderr, "Input error!\n");
    return;
  }
  note_name[strcspn(note_name, "\n")] = '\0';
  unsigned long max_len = 128, count = 0;
  char *buff = calloc(max_len, sizeof(*buff));

  FILE *file = fopen(note_name, "rb");
  if (!file)
    file = fopen(note_name, "wb");
  else {
    printf("This note exists!\n");
    fclose(file);
    return;
  }
  if (file) {
    int c;
    printf("Press CTRL+D to end. \n");
    printf("Enter your note: ");
    while ((c = getchar()) != EOF) {
      if (count >= max_len)
        buff = realloc(buff, max_len += 64);
      if (!buff) {
        fprintf(stderr, "Error allocating buffer!\n");
        exit(1);
      }
      buff[count++] = c;
    }
  } else {
    perror("fopen");
    exit(1);
  }

  unsigned flag = fwrite(buff, 1, count, file);
  if (flag)
    printf("Successfully Added! \n");
  clearerr(stdin);
  free(buff);
  fclose(file);
}
