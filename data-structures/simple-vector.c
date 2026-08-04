#include <stdio.h>
#include <stdlib.h>

struct vector {
  int *data;
  size_t size;
  size_t capacity;
};

struct vector *vector_create(size_t);
void vector_destroy(struct vector **);
int vector_push_back(struct vector *, int);
int vector_pop_back(struct vector *, int *);
int vector_get(struct vector *, size_t, int *);
int vector_set(struct vector *, size_t, int);
void print_vs(struct vector *);
int vector_insert(struct vector *, size_t, int);
int vector_erase(struct vector *, size_t);

int main(void) {
  struct vector *vtr = vector_create(8);
  vector_push_back(vtr, 10);
  int x;
  vector_push_back(vtr, 20);
  vector_get(vtr, 1, &x);
  vector_set(vtr, 0, 100);
  vector_get(vtr, 1, &x);

  print_vs(vtr);
  vector_insert(vtr, 1, 60);
  print_vs(vtr);
  vector_erase(vtr, 2);
  print_vs(vtr);
  return 0;
}

struct vector *vector_create(size_t initial_capacity) {
  if (initial_capacity == 0)
    initial_capacity = 1;
  struct vector *p = malloc(sizeof(*p));
  if (!p)
    return NULL;
  p->data = malloc(sizeof(*(p->data)) * initial_capacity);
  if (!p->data) {
    free(p);
    return NULL;
  }
  p->capacity = initial_capacity;
  p->size = 0;
  return p;
}

void vector_destroy(struct vector **v) {
  if (v == NULL || *v == NULL)
    return;
  free((*v)->data);
  free(*v);
  *v = NULL;
}

int vector_push_back(struct vector *v, int value) {
  if (v == NULL)
    return 0;

  if (v->size >= v->capacity) {
    int *tmp = realloc(v->data, (v->capacity * 2) * sizeof(*(v->data)));
    if (!tmp)
      return 0;
    v->data = tmp;
    v->capacity *= 2;
  }
  v->data[v->size] = value;
  v->size++;
  return 1;
}

int vector_pop_back(struct vector *v, int *out) {
  if (!v || !out)
    return 0;
  if (v->size == 0)
    return 0;

  *out = v->data[--v->size];
  return 1;
}

int vector_get(struct vector *vtr, size_t idx, int *ptr) {
  if (!vtr || !ptr)
    return 0;
  if (idx > vtr->size)
    return 0;

  *ptr = vtr->data[idx];
  return 1;
}

int vector_set(struct vector *vtr, size_t idx, int value) {
  if (!vtr)
    return 0;
  if (idx > vtr->size)
    return 0;

  vtr->data[idx] = value;
  return 1;
}

void print_vs(struct vector *vtr) {
  if (!vtr)
    return;

  for (size_t i = 0; i < vtr->size; ++i)
    printf("%d ", vtr->data[i]);
  printf("\n");
}

int vector_insert(struct vector *vtr, size_t idx, int value) {
  if (!vtr)
    return 0;

  if (vtr->size >= vtr->capacity) {
    int *tmp = realloc(vtr->data, (vtr->capacity * 2) * sizeof(*vtr->data));
    if (!tmp)
      return 0;
    vtr->data = tmp;
    vtr->capacity *= 2;
  }

  for (size_t i = vtr->size; i > idx; --i)
    vtr->data[i] = vtr->data[i - 1];

  vtr->data[idx] = value;
  vtr->size++;
  return 1;
}

int vector_erase(struct vector *vtr, size_t idx) {
  if (!vtr)
    return 0;
  if (idx >= vtr->size)
    return 0;

  for (size_t i = idx; i < vtr->size - 1; ++i)
    vtr->data[i] = vtr->data[i + 1];

  vtr->size--;
  return 1;
}
