#ifndef MENUARRAY_H
#define MENUARRAY_H

#include <stddef.h>

#include "menu.h"

typedef struct menuArray {
    MenuItem *array;
    size_t used;
    size_t size;
} MenuArray;

MenuArray MenuArray_new(size_t initialSize);

void MenuArray_insert(MenuArray *, MenuItem *);
void MenuArray_delete(MenuArray *, int);
void MenuArray_free(MenuArray *);

#endif // MENUARRAY_H
