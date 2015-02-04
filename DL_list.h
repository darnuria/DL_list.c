#ifndef DL_LIST_H
#define DL_LIST_H

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _DL_node {
  struct _DL_node* next;
  struct _DL_node* prev;
  void* data;
} DL_node;

typedef struct {
  DL_node* head;
  DL_node* tail;
  size_t length;
} DL_list;

DL_list* DL_new(void* data, size_t size_type);

// tail
void DL_append(DL_list* self, void* data);

// head
void DL_List_prepend(DL_list* self, void* data);

#endif // DL_LIST
