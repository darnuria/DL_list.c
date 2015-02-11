#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "DL_list.h"

typedef struct {
  int id;
} FatPtr;

FatPtr* FatPtr_new(int data) {
  FatPtr* n = malloc(sizeof(FatPtr));
  assert(n != NULL);
  n->id = data;
  return n;
}

void FatPtr_dtor(FatPtr** a, size_t size) {
  (void) size;
  assert(a != NULL && *a != NULL);
  free(*a);
  *a = NULL;
}

FatPtr* FatPtr_clone(FatPtr* a, size_t s) {
  (void) s;
  assert(a != NULL);
  FatPtr* b = FatPtr_new(a->id);
  assert(b != NULL);
  return b;
}

#define FatPtr_cast(p) ((FatPtr*)(p))

int main(void) {
  DL_list* a = DL_new(sizeof(FatPtr),
      DL_cast_dtor(FatPtr_dtor),
      DL_cast_clone(FatPtr_clone));

  assert(a != NULL && DL_length(a) == 0);

  DL_push_front(a, FatPtr_new(4));
  assert(DL_length(a) == 1 && FatPtr_cast(DL_front(a))->id == 4);
  DL_push_front(a, FatPtr_new(3));
  assert(DL_length(a) == 2 && FatPtr_cast(DL_front(a))->id == 3);
  DL_push_front(a, FatPtr_new(2));
  assert(DL_length(a) == 3 && FatPtr_cast(DL_front(a))->id == 2);
  DL_push_front(a, FatPtr_new(1));
  assert(DL_length(a) == 4 && FatPtr_cast(DL_front(a))->id == 1);

  DL_push_back(a, FatPtr_new(4));
  assert(DL_length(a) == 1 && FatPtr_cast(DL_back(a))->id == 4);
  DL_push_back(a, FatPtr_new(3));
  assert(DL_length(a) == 2 && FatPtr_cast(DL_back(a))->id == 3);
  DL_push_back(a, FatPtr_new(2));
  assert(DL_length(a) == 3 && FatPtr_cast(DL_back(a))->id == 2);
  DL_push_back(a, FatPtr_new(1));
  assert(DL_length(a) == 4 && FatPtr_cast(DL_back(a))->id == 1);

  DL_drop(&a);
  assert(a == NULL);

  return EXIT_SUCCESS;
}
