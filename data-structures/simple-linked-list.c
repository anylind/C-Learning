#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
  struct node *prev;
};

struct node *create_node(int);
int sum(struct node *);
int length(struct node *);
void append(struct node **, int);
void print_list(struct node *);
void destroy(struct node **);

int main(void) {
  struct node *foo = NULL;
  append(&foo, 10);
  append(&foo, 20);
  append(&foo, 30);
  print_list(foo);
  printf("Sum: %d\n", sum(foo));
  printf("Length: %d\n", length(foo));
  destroy(&foo);
  printf("foo: %p\n", (void *)foo);

  return 0;
}

struct node *create_node(int value) {
  struct node *p = malloc(sizeof(*p));
  if (!p)
    return NULL;
  p->data = value;
  p->next = NULL;
  p->prev = NULL;
  return p;
}

void print_list(struct node *head) {
  struct node *var;
  for (var = head; var != NULL; var = var->next) {
    printf("Value: %d\n", var->data);
  }
}

void append(struct node **head, int value) {
  if (*head == NULL) {
    *head = create_node(value);
    return;
  }

  struct node *var = *head;
  while (var->next != NULL)
    var = var->next;
  struct node *new = create_node(value);
  if (!new)
    return;

  new->prev = var;
  var->next = new;

  printf("append:\n");
  if (var->prev)
    printf("\tprev: %d\n", var->prev->data);
  else
    printf("\tprev: NULL\n");

  printf("\tcur: %d\n", var->data);

  if (var->next)
    printf("\tnext: %d\n", var->next->data);
  else
    printf("\tnext: NULL\n");
}

int sum(struct node *head) {
  struct node *var;
  int result = 0;
  for (var = head; var != NULL; var = var->next) {
    result += var->data;
  }
  return result;
}

int length(struct node *head) {
  struct node *var;
  int result = 0;
  for (var = head; var != NULL; var = var->next) {
    ++result;
  }
  return result;
}

void destroy(struct node **head) {
  if (!head)
    return;

  while (*head != NULL) {
    struct node *next = (*head)->next;
    free(*head);
    *head = next;
  }
}
