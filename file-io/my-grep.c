#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *get_line(FILE *, unsigned int);
void check_line(char *, size_t, unsigned char *);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: my-grep 'word' 'filename'\n");
    return 1;
  }
  FILE *file = fopen(argv[2], "rb");
  unsigned char *line_addr = NULL;

  fseek(file, 0, SEEK_END);
  unsigned int len = (unsigned)ftell(file);
  rewind(file);

  while ((line_addr = get_line(file, len)) != NULL) {
    check_line(argv[1], strlen(argv[1]), line_addr);

    free(line_addr);
  }

  fclose(file);
  return 0;
}

unsigned char *get_line(FILE *file, unsigned int len) {

  static unsigned int count_static = 0;

  if (count_static >= len)
    return NULL;

  unsigned int count = 0, maxcline = 64;
  unsigned char ch;
  unsigned char *line_buff = calloc(maxcline, sizeof(*line_buff));

  while (fread(&ch, sizeof ch, 1, file) == 1) {
    if (count == maxcline)
      line_buff = realloc(line_buff, maxcline += 64);
    if (line_buff == NULL) {
      fprintf(stderr, "Error allocating space! Try again.\n");
      exit(1);
    }
    line_buff[count] = ch;
    ++count;
    ++count_static;
    if (ch == '\n')
      break;
  }
  return line_buff;
}

void check_line(char *word, size_t word_len, unsigned char *line) {

  unsigned int count = 0, i;

  while (line[count] != '\n' && line[count] != '\0') {

      if (strncmp(line + count, word, word_len) == 0){
          printf("%s", line);

      break;}

    ++count;
  }
}
