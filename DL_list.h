#ifndef DL_LIST_H
#define DL_LIST_H

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _DL_node {
  struct _DL_list* next;
  struct _DL_list* prev;
  void* data;
} DL_node;

typedef struct {
  DL_node* head;
  DL_node* tail;
  size_t length;
} DL_list;

DL_node* DL_node_new(void* data) {
  DL_node* n = malloc(sizeof(DL_node));
  assert(n != NULL)
  n->next = NULL;
  n->prev = NULL;
  n->data = data;

  return n;
}

DL_list* DL_list_new(void* data, size_t size_type) {
  DL_list* l = // TODO;
  DL_node* n = DL_node_new(data);
  assert(l != NULL); // TODO good error handling.
  assert(n != NULL);

  l->length = 1;
  l->head = n;
  l->tail = n;

  return n;
}




#endif DL_LIST
