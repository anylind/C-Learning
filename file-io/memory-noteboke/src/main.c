#include "logic.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
  if (mkdir("notes", 0755) == -1) {
    perror("mkdir");
  }
  while (logic() != 7)
    ;
  return 0;
}
