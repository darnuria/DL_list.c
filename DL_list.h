#ifndef DL_LIST_H
#define DL_LIST_H

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//! Use this macro for casting your destructors.
#define DL_cast_dtor(f) ((void (*)(void**, size_t))(f))

//! Use this macro for casting your clone function.
#define DL_cast_clone(f) ((void* (*)(void*, size_t))(f))

//! Use this macro for casting your datatype.
#define DL_cast_data(d) ((void*)(d))


//! Private type.
typedef struct _DL_node {
  struct _DL_node* next;
  struct _DL_node* prev;
  void* data; // Data to store we know nothing about it. If were storing an array please make a  vector like.
} DL_node;

// Accept only one type of data Undefined behaviour with mixed datatype.
typedef struct {
  DL_node* head;
  DL_node* tail;
  size_t length; // number of node in the list.
  size_t type_size; // Datatype size equivalent to typeof(T)
  void(*dtor)(void**, size_t); // Destructor for our data.
} DL_list;

// Allocate a new list.
// dtor: destructor of for the givien void* data
DL_list* DL_new(size_t size, void(*dtor)(void**, size_t size));

// Add on tail.
// Complexity: O(1)
void DL_push_back(DL_list* self, void* data);

// Add on head.
// Complexity: O(1)
void DL_push_front(DL_list* self, void* data);

//! Concatenate B to A in O(1) with A self modification.
void DL_concat(DL_list* self, DL_list* b);

//! append B to A O(n) and return a new list.
DL_list* DL_concat_mut(const DL_list* self, const DL_list* b);

//! Insert a data in the lista at an index.
void DL_insert(DL_list* self, size_t index, void* data);

//! Copy a list with a `f_cpy` function.
DL_list* DL_copy(const DL_list* self, void*(f_cpy)(void*, size_t));

//! Return a new list reversed from self.
DL_list* DL_reverse(const DL_list* self);

//! Reverse in place self.
void DL_reverse_mut(DL_list* self);

//! TODO
DL_list* DL_sort(const DL_list* self);

//! TODO
void DL_sort_mut(DL_list* self);

//! Remove last elem and return it.
void* DL_pop(DL_list* self);

//! Delete the list given in parameter and set as null the pointer.
void DL_drop(DL_list** self);

#endif // DL_LIST
