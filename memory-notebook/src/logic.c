#include "manage-notes.h"
#include <stdio.h>
#include <unistd.h>

int logic(void) {

  int option = 0, c;

  printf("1) Add note.\n");
  printf("2) delete note.\n");
  printf("3) delete all notes.\n");
  printf("4) edit note.\n");
  printf("5) show notes.\n");
  printf("6) show note content.\n");
  printf("7) Quite.\n");
  printf("Select an option: ");

  scanf("%d", &option);
  while ((c = getchar()) != '\n')
    ;

  switch (option) {
  case 1:
    add_note();
    break;
  case 2:
    delete_note();
    break;
  case 3:
    delete_all();
    break;
  case 4:
    edit_note();
    break;
  case 5:
    show_notes();
    break;
  case 6:
    show_content();
    break;
  case 7:
    return option;
  default:
    printf("Enter the valid option!\n");
  }

  return option;
}
