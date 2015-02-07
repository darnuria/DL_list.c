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

DL_node* DL_node_new (void* data);

DL_list* DL_new (void* data, size_t size_type);

static
void node_connect (DL_node* a, DL_node* b)

// tail
void DL_list_append (DL_list* self, void* data);

// head
void DL_list_prepend (DL_list* self, void* data);

void DL_list_concatenate (DL_list* a, DL_list* b);

void DL_list_insert (DL_list* self, int index, void* data);

DL_list* DL_list_copy (DL_list* self);

DL_node* DL_node_copy (DL_node* self);

DL_list* DL_list_reverse (DL_list* self);

void DL_node_delete (DL_node* self);

void DL_list_del_prepend (DL_list* self);

void DL_list_del_append (DL_list* self);

void DL_list_delete (DL_list* self);

#endif // DL_LIST
