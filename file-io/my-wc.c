#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: my-wc 'filename'\n");
    return 1;
  }

  FILE *file = fopen(argv[1], "rb");
  unsigned char c;
  unsigned int lines, words, bytes;
  lines = words= bytes = 0;

  while (fread(&c, sizeof c, 1, file) == 1) {
    if (c == '\n')
      ++lines;
    if (c == ' ' || c == '\0' || c == '\n')
      ++words;
    ++bytes;
  }

  printf("Lines: %u\n", lines);
  printf("Words: %u\n", words);
  printf("Bytes: %u\n", bytes);

  fclose(file);
  return 0;
}
