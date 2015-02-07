#include <assert.h>
#include <stdio.h>

#include"DL_list.h"

static
DL_node* DL_node_new (void* data) {
  DL_node* n = malloc(sizeof(DL_node));
  assert(n != NULL);

  n->next = NULL;
  n->prev = NULL;
  n->data = data;

  return n;
}

DL_list* DL_new (void* data, size_t size_type) {
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
void node_connect (DL_node* a, DL_node* b) {
  a->next = b;
  b->prev = a;
}

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
void DL_list_concatenate (DL_list* a, DL_list* b) {
  node_connect(a->head, b->tail);
}

/*ça serais pas plutot ça
  DL_list* DL_List_concatenate (DL_list* a, DL_list* b) {
  node_connect(a->head, b->tail);
//une copie de liste de a et b non?
DL_list* tmp = a;
tmp->tail = b->tail;
return tmp;
*/

void DL_list_insert (DL_list* self, int index, void* data) {
  if (index > self->length) {
    perror ("Index not in the list \n");
  }
  DL_node* tmp = self->head;
  int i = 0;
  while (i =! index)  {
    if (i == index) {
      tmp->data = data;
    }
    tmp = tmp->next;
    i += 1;
  }
}

DL_list* DL_list_copy (DL_list* self) {
  DL_list* cpy = DL_new (self->head->data, self->length); // probleme avec le length je pense
  DL_node* tmp = self->head;
  int i = 0;
  while (i != self->length) {
    DL_list_append (cpy, tmp->data);
    tmp = tmp->next;
    i += 1;
  }
  return cpy;
}

//sert a rien je pense
DL_node* DL_node_copy (DL_node* self) {
  DL_node* cpy = DL_node_new (self->data);
  return cpy;
}

DL_list* DL_list_reverse (DL_list* self) {
  DL_list* cpy = DL_new (self->head->data, self->length); // probleme avec le length je pense
  DL_node* tmp = self->head;
  int i = 0;
  while (i != self->length) {
    DL_list_prepend (cpy, tmp->data);
    tmp = tmp->next;
    i += 1;
  }
  return cpy;
}

void DL_node_delete (DL_node* self) {
  self->prev = NULL;
  self->next = NULL;
  free (self);
}

void DL_list_del_prepend (DL_list* self) {
  DL_node* tmp = self->head;
  self->head = self->head->next;
  self->head->prev = NULL;
  tmp->next = NULL;
  free (tmp);
  tmp = NULL;
  self->length -= 1;
}

void DL_list_del_append (DL_list* self) {
  DL_node* tmp = self->tail;
  self->tail = self->tail->prev;
  self->tail->next = NULL;
  tmp->prev = NULL;
  free (tmp);
  tmp = NULL;
  self->length -= 1;
}

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

// En construction
void main() {
  int input;
  bool exit = false;
  printf ("Bonjour, que souhaiter vous faire ?\n");
  while (exit =! true) {
    printf ("1. Crée une liste\n");
    printf ("2. Ajouter un élément en début de liste\n");
    printf ("3. Ajouter un élément en fin de liste\n");
    printf ("4. Assembler deux listes\n");
    printf ("5. Inserer dans une liste\n");
    printf ("6. Copier une liste\n");
    scanf ("%d", &input);
    switch (input) {
      case 1 :
        printf ("Donner un élément pour initialiser la liste : ");
        scanf ("%d", &input);

        break;
      default :
        exit = true;
        break;
    }
  }
}
