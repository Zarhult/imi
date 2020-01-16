#ifndef MENUARRAY_H
#define MENUARRAY_H

#include <stddef.h>

#include "menu.h"

typedef struct menuArray {
    MenuItem *array;
    size_t size;
    int used;
    int currIndex;
} MenuArray;

MenuArray MenuArray_new(size_t initialSize);

void MenuArray_insert(MenuArray *, MenuItem *);
void MenuArray_delete(MenuArray *, int);
void MenuArray_free(MenuArray *);

void MenuArray_draw(MenuArray *, int);
void MenuArray_select(MenuArray *, int);

#endif // MENUARRAY_H
