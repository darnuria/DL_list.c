#include <assert.h>
#include <stdio.h>

#include"DL_list.h"

static
DL_node* DL_node_new(void* data) {
  DL_node* n = malloc(sizeof(DL_node));
  assert(n != NULL);

  n->next = NULL;
  n->prev = NULL;
  n->data = data;

  return n;
}

DL_list* DL_new(void* data, size_t size_type) {
  DL_list* l = malloc(sizeof(int));
  DL_node* n = DL_node_new(data);

  if ((l == NULL) || (n == NULL)) {
    perror ("DL_new:");
    assert(l == NULL);
    assert(n == NULL);
    return NULL;
  }

  l->length = 1;
  l->head = n;
  l->tail = n;

  return l;
}

static
void node_connect(DL_node* a, DL_node* b) {
  a->next = b;
  b->prev = a;
}

void DL_append(DL_list* self, void* data) {
  DL_node* n = DL_node_new(data);

  if (n == NULL) {
    perror ("Allocation Error ! \n");
  }
  DL_node* tmp = self->tail;
  self->tail = n;

  node_connect(tmp, n);
  self->length += 1;
}

void DL_List_prepend(DL_list* self, void* data) {
  DL_node* n = DL_node_new(data);

  if(n == NULL) {
    perror ("Allocation Error ! \n");
  }
  DL_node* tmp = self->head;
  self->head = n;

  node_connect(tmp, n);
  self->length += 1;
}


