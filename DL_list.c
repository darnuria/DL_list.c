#include <assert.h>
#include <stdio.h>

#include"DL_list.h"

//Fonction créeant un node
static
DL_node* DL_node_new (void* data) {
  DL_node* n = malloc(sizeof(DL_node));
  assert(n != NULL);

  n->next = NULL;
  n->prev = NULL;
  n->data = data;

  return n;
}

//Fonction créeant une liste avec un node
DL_list* DL_new (void* data) {
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

//Fonction connectant deux node
static
void node_connect (DL_node* a, DL_node* b) {
  a->next = b;
  b->prev = a;
}

//Ajout d'un élément en fin de liste
void DL_list_append (DL_list* self, void* data) {
  DL_node* n = DL_node_new(data);

  if (n == NULL) {
    perror ("Allocation Error ! \n");
  }
  DL_node* tmp = self->tail;
  self->tail = n;

  node_connect(tmp, n);
  self->length += 1;
}

//Ajout d'un élément en début de liste
void DL_list_prepend (DL_list* self, void* data) {
  DL_node* n = DL_node_new(data);

  if(n == NULL) {
    perror ("Allocation Error ! \n");
  }
  DL_node* tmp = self->head;
  self->head = n;

  node_connect(tmp, n);
  self->length += 1;
}

//sa me parait trop simple j'ai du oublier quelque chose...
//Fonction concatenant deux liste
void DL_list_concatenate (DL_list* a, DL_list* b) {
  node_connect(a->head, b->tail);
}

/*ça serais pas plutot ça
//Fonction concatenant deux listes en renvoyant un node avec head et tail
DL_list* DL_List_concatenate (DL_list* a, DL_list* b) {
  node_connect(a->head, b->tail);     //une copie de liste de a et b non?
  DL_list* tmp = a;
  tmp->tail = b->tail;
  return tmp;
*/

//Ajout un élément dans la liste
void DL_list_insert (DL_list* self, int index, void* data) {
  if (index < 0 || (size_t)index > self->length) {
    perror("DL_list_insert: index out of bound.");
    assert(false);
  } else if (index == 0) {
     DL_list_prepend(self, data);
  } else if ((size_t)index == self->length) {
    DL_list_append(self, data);
  } else {
    DL_node* n = DL_node_new(data); // Alloc a new node for the data to be inserted.
    DL_node* iter = NULL;
    if ((size_t)index > (self->length / 2)) {
      iter = self->tail;
      for (size_t i = 0; i < (size_t)index; i += 1) {
        iter = iter->prev; // iteration from last to index.
      }
    } else {
      iter = self->head;
      for (size_t i = 0; i < (size_t)index; i += 1) {
        iter = iter->next; // iteration from begin to index.
      }
    }
    DL_node* prev = iter->prev;
    node_connect(prev, n);
    node_connect(iter, n);
  }
}

//Fonction créeant une copie d'une liste
DL_list* DL_list_copy (DL_list* self) {
  DL_list* cpy = DL_new (self->head->data);
  DL_node* tmp = self->head;
  int i = 0;
  while ((size_t)i != self->length) {
    DL_list_append (cpy, tmp->data);
    tmp = tmp->next;
    i += 1;
  }
  return cpy;
}

//sert a rien je pense
//Fonction copiant un node
DL_node* DL_node_copy (DL_node* self) {
  DL_node* cpy = DL_node_new (self->data);
  return cpy;
}

//Fonction créant une liste qui est l'inverse de celle donner
DL_list* DL_list_reverse (DL_list* self) {
  DL_list* cpy = DL_new (self->head->data);
  DL_node* tmp = self->head;
  int i = 0;
  while ((size_t)i != self->length) {
    DL_list_prepend (cpy, tmp->data);
    tmp = tmp->next;
    i += 1;
  }
  return cpy;
}

//Fonction detruisant un node
void DL_node_delete (DL_node* self) {
  self->prev = NULL;
  self->next = NULL;
  free (self);
}

//Fonction suprimant le premiere élément de la liste
void DL_list_del_prepend (DL_list* self) {
  DL_node* tmp = self->head;
  self->head = self->head->next;
  self->head->prev = NULL;
  tmp->next = NULL;
  free (tmp);
  tmp = NULL;
  self->length -= 1;
}

//Fonction suprimant le dernière élément de la liste
void DL_list_del_append (DL_list* self) {
  DL_node* tmp = self->tail;
  self->tail = self->tail->prev;
  self->tail->next = NULL;
  tmp->prev = NULL;
  free (tmp);
  tmp = NULL;
  self->length -= 1;
}

//Fonction suprimant la liste
void DL_list_delete (DL_list* self) {
  DL_node* tmp = self->head;
  while (self->length != 1) {
    DL_list_del_prepend (self);
  }
  self->head = NULL;
  self->tail = NULL;
  self->length -= 1;
  free (self);
  DL_node_delete (tmp);
}
