#include <stdio.h>

void char_representation(unsigned char *, int);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: hes-viewer 'filename'.\n");
    return 1;
  }

  FILE *file = fopen(argv[1], "rb");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  unsigned char c, chars[16];

  fseek(file, 0L, SEEK_END);
  unsigned long len = ftell(file), i = 0, last_line;
  fseek(file, 0L, SEEK_SET);

  last_line = len / 16 * 16;
  int last_len = len - last_line;

  printf("%#08lx  ", ftell(file));
  while (fread(&c, sizeof c, 1, file) == 1) {
    len = ftell(file);
    printf("%02x ", c);
    chars[i] = c;
    ++i;

    if (len % 16 == 0) {
      i = 0;
      printf("|");
      char_representation(chars, 0);
      printf("|");

      printf("\n%#08lx  ", len);
    }
  }
  if (i) {
    for (int i = 0; i < (16 - last_len); ++i)
      printf("   ");
    printf("|");
    char_representation(chars, last_len);
    printf("|");

    printf("\n%#08lx\n", ftell(file));
  }
  printf("\n");
  fclose(file);
  return 0;
}

void char_representation(unsigned char *chars, int last_len) {
  unsigned char c;
  int len;
  if (last_len)
    len = last_len;
  else
    len = 16;

  for (int i = 0; i < len; ++i) {
    if (chars[i] >= 32 && chars[i] <= 126)
      c = chars[i];
    else
      c = '.';
    printf("%lc", c);
  }
}
