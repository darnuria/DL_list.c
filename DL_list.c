#include <assert.h>
#include <stdio.h>

#include"DL_list.h"

//! Allocate a new node.
static
DL_node* DL_node_new(void* data);

//! Delete use a given Dtor to delete a node.
static
void DL_node_drop(DL_node** self, size_t size, void(*dtor)(void**, size_t));

//! Connect two nodes.
static
void DL_node_connect(DL_node* a, DL_node* b) {
  a->next = b;
  b->prev = a;
}

//! Unconnect two nodes.
static
void DL_node_unconnect(DL_node* a, DL_node* b) {
  a->next = NULL;
  b->prev = NULL;
}

//! Dangerous pointer swap.
// static
// void DL_node_swap(DL_node *a, DL_node* b) {
//   void* tmp = a->data;
//   a->data = b->data;
//   b->data = tmp;
// }

// TODO
static
void DL_node_drop (DL_node** self, size_t size, void(*dtor)(void**, size_t)) {
  assert(self != NULL);
  DL_node* s = *self;
  assert(s != NULL);
  s->prev = NULL;
  s->next = NULL;
  dtor(&(s->data), size);
  free(*self);
  *self = NULL;
}

static
DL_node* DL_node_new(void* data) {
  DL_node* n = malloc(sizeof(DL_node));
  assert(n != NULL);

  n->next = NULL;
  n->prev = NULL;
  n->data = data;
  return n;
}

DL_list* DL_new(size_t size,
    void(*dtor)(void**, size_t size),
    void*(*clone)(void*, size_t)) {
  DL_list* l = malloc(sizeof(DL_list));

  if (l == NULL) {
    perror ("DL_new:");
    return NULL;
  }

  l->length = 0;
  l->head = NULL;
  l->tail = NULL;
  l->type_size = size;
  l->dtor = dtor;
  l->clone = clone;
  return l;
}

static
DL_node* DL_link_with_prev(DL_node* next, DL_node* prev) {
  next->prev = prev;
  return next;
}

static
void DL_push_front_node(DL_list* self, DL_node* new_head) {
  if (self->head == NULL) {
    self->tail = new_head;
    self->head = DL_link_with_prev(new_head, NULL);
  } else {
    DL_node* old_head = self->head;
    self->head = new_head;
    self->head->next = DL_link_with_prev(old_head, new_head);
    assert(self->head->next != NULL);
    assert(self->tail->prev != NULL);
    assert(self->head->prev == NULL);
    assert(self->tail->next == NULL);
  }
  self->length += 1;
}

static
void DL_push_back_node(DL_list* self, DL_node* new_tail) {
  if (self->tail == NULL) {
    DL_push_front_node(self, new_tail);
  } else {
    DL_node* tail = self->tail;
    self->tail = new_tail;
    tail->next = DL_link_with_prev(new_tail, tail);
    self->length += 1;
  }
}

size_t DL_length(const DL_list* self) { return self->length; }

void* DL_front(const DL_list* self) { return self->head->data; }

void* DL_back(const DL_list*self) { return self->tail->data; }

bool DL_is_empty(const DL_list* self) { return self->length == 0; }

void DL_clear(DL_list* self) {
  DL_node* iter = self->head;
  assert(iter != NULL);
  while (iter->next != NULL) {
    DL_node* tmp = iter->next;
    assert(tmp != NULL);
    assert(iter != NULL);
    DL_node_drop(&iter, self->type_size, self->dtor);
    iter = tmp;
  }
  self->length = 0;
  self->head = NULL;
  self->tail = NULL;
}

void DL_push_back(DL_list* self, void* data) {
  DL_node* n = DL_node_new(data);

  if (n == NULL) {
    perror ("DL_push_back:\n");
  }
  DL_push_back_node(self, n);
}

void DL_push_front(DL_list* self, void* data) {
  DL_node* n = DL_node_new(data);

  if(n == NULL) {
    perror ("Allocation Error ! \n");
  }
  DL_push_front_node(self, n);
}

void DL_concat(DL_list* self, DL_list* b) {
  DL_node_connect(self->tail, b->head);
}

void DL_insert(DL_list* self, size_t index, void* data) {
  const size_t len = self->length;

  if (index > len) {
    perror("DL_list_insert: index out of bound.");
    assert(false);
  } else if (index == 0) {
    DL_push_front(self, data);
  } else if (index == len) {
    DL_push_back(self, data);
  } else {
    DL_node* n = DL_node_new(data); // Alloc a new node for the data to be inserted.
    DL_node* iter = NULL;
    if (index > (len / 2)) {
      iter = self->tail;
      for (size_t i = 0; i < index; i += 1) {
        iter = iter->prev; // iteration from last to index.
      }
    } else {
      iter = self->head;
      for (size_t i = 0; i < index; i += 1) {
        iter = iter->next; // iteration from begin to index.
      }
    }
    DL_node* prev = iter->prev;
    DL_node_connect(prev, n);
    DL_node_connect(iter, n);
    self->length += 1;
  }
}

DL_list* DL_copy(const DL_list* self, void*(f_cpy)(void*, size_t)) {
  DL_list* cpy = DL_new(self->type_size, self->dtor, self->clone);

  for (DL_node* iter = self->head; iter != NULL; iter = iter->next) {
    DL_push_front(cpy, f_cpy(iter->data, self->type_size));
  }
  return cpy;
}


DL_list* DL_reverse(const DL_list* self) {
  DL_list* cpy = DL_new(self->type_size, self->dtor, self->clone);

  for (DL_node* iter = self->tail; iter != NULL; iter = iter->prev) {
    DL_push_front(cpy, iter->data);
  }
  return cpy;
}

//! TODO
void DL_reverse_mut(DL_list* self) {
  (void) self;
}

// TODO:
DL_list* DL_sort(const DL_list* self) {
  (void) self;
  return NULL;
}


DL_list* DL_filter(const DL_list* self, DL_list*(*p)(void*)) {
  DL_list* result = DL_new(self->type_size, self->dtor, self->clone);
  const size_t size_type = self->type_size;

  for (DL_node* iter = self->head; iter != NULL; iter = iter->next) {
    if (p(iter->data)) {
      DL_push_front(result, self->clone(iter->data, size_type));
    }
  }
  return result;
}

// TODO:
void DL_sort_mut(DL_list* self) {
  (void) self;
}

void* DL_pop(DL_list* self) {
  DL_node* tail = self->tail;
  DL_node* new_tail = tail->prev;

  DL_node_unconnect(new_tail, tail);
  void* data = tail->data;
  DL_node_drop(&tail, self->type_size, self->dtor);
  self->length -= 1;
  return data;
}

// TODO: implement.
void DL_drop(DL_list** self) {
  assert(self != NULL);
  DL_clear(*self);

  assert((*self)->head == NULL);
  assert((*self)->tail == NULL);

  free(*self);
  *self = NULL;
}
