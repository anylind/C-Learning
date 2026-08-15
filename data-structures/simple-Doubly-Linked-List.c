#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
  struct node *prev;
};

struct list {
  struct node *head;
  struct node *tail;
  size_t size;
};

struct list *list_create(void);
struct node *create_node(int);
void list_destroy(struct list **);
int list_push_back(struct list *, int);
int list_push_front(struct list *, int);
int list_pop_front(struct list *, int *);
int list_pop_back(struct list *, int *);
int list_erase(struct list *, size_t);
struct node *list_find(struct list *, int);
void list_reverse(struct list *);

int main(void) { return 0; }

struct list *list_create(void) {
  struct list *p = malloc(sizeof(*p));
  if (!p)
    return NULL;
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;
  return p;
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

void list_destroy(struct list **l) {
  if (!l)
    return;

  struct node *mtf;
  while ((*l)->tail != NULL) {
    mtf = (*l)->tail;
    (*l)->tail = (*l)->tail->prev;
    free(mtf);
  }
  (*l)->head = NULL;
  (*l)->tail = NULL;
  free(*l);
  *l = NULL;
}

int list_push_back(struct list *l, int value) {
  if (!l)
    return 0;
  struct node *new = create_node(value);
  if (!new)
    return 0;
  if (l->size == 0) {
    l->head = new;
    l->tail = new;
    l->size++;
    return 1;
  }
  new->prev = l->tail;
  l->tail->next = new;
  l->tail = new;
  l->size++;
  return 1;
}

int list_push_front(struct list *l, int value) {
  if (!l)
    return 0;

  struct node *new = create_node(value);
  if (!new)
    return 0;
  if (l->size == 0) {
    l->tail = new;
    l->head = new;
  } else {
    new->next = l->head;
    l->head->prev = new;
    l->head = new;
  }
  l->size++;
  return 1;
}

int list_pop_front(struct list *l, int *v) {
  if (!l || !v || !l->head)
    return 0;

  *v = l->head->data;
  struct node *old_head = l->head;
  l->head = l->head->next;
  if (!l->head)
    l->tail = NULL;
  else
    l->head->prev = NULL;
  free(old_head);
  l->size--;
  return 1;
}

int list_pop_back(struct list *l, int *v) {
  if (!l || !v || !l->tail)
    return 0;

  *v = l->tail->data;
  struct node *old_tail = l->tail;
  if (l->size > 1) {
    l->tail = l->tail->prev;
    l->tail->next = NULL;
  } else {
    l->head = NULL;
    l->tail = NULL;
  }
  free(old_tail);
  l->size--;
  return 1;
}

int list_insert(struct list *l, size_t index, int value) {
  if (!l || index > l->size)
    return 0;

  if (index == l->size) {
    int stat = list_push_back(l, value);
    if (stat)
      return 1;
    return 0;
  }

  if (index == 0) {
    int stat = list_push_front(l, value);
    if (stat)
      return 1;
    return 0;
  }
  struct node *new = create_node(value);
  if (!new)
    return 0;

  struct node *cur = l->head;
  for (size_t i = 0; i < index; ++i)
    cur = cur->next;
  new->prev = cur->prev;
  cur->prev->next = new;
  cur->prev = new;
  new->next = cur;
  l->size++;
  return 1;
}

int list_erase(struct list *l, size_t index) {
  int tmp;
  if (!l || !l->size || index >= l->size)
    return 0;
  if (l->size == 1 || index == l->size - 1) {
    int stat = list_pop_back(l, &tmp);
    if (stat)
      return 1;
    return 0;
  }
  if (index == 0) {
    int stat = list_pop_front(l, &tmp);
    if (stat)
      return 1;
    return 0;
  }

  struct node *cur = l->head;
  for (size_t i = 0; i < index; ++i)
    cur = cur->next;
  struct node *to_erase = cur;
  cur->prev->next = cur->next;
  cur->next->prev = cur->prev;
  free(to_erase);
  l->size--;
  return 1;
}

struct node *list_find(struct list *l, int value) {
  if (!l || !l->size)
    return NULL;

  struct node *cur;
  for (cur = l->head; cur != NULL; cur = cur->next)
    if (cur->data == value)
      return cur;
  return NULL;
}

void list_reverse(struct list *l) {
  if (!l || l->size <= 1)
    return;

  struct node *next, *cur, *head;
  for (cur = l->head; cur != NULL; cur = next) {
    next = cur->next;
    cur->next = cur->prev;
    cur->prev = next;
  }
  head = l->head;
  l->head = l->tail;
  l->tail = head;
}
