#ifndef DEFMENU_H
#define DEFMENU_H

#include <stddef.h>
#include "worddef.h"

typedef struct defMenu {
    WordDef *array;
    size_t size;
    int used;
    int currIndex;
} DefMenu;

DefMenu DefMenu_NEW(size_t initialSize);

void DefMenu_INSERT(DefMenu *, WordDef *);
void DefMenu_DELETE(DefMenu *, int);
void DefMenu_FREE(DefMenu *);

void DefMenu_DRAW(DefMenu *, int);
void DefMenu_SELECT(DefMenu *, int);

#endif // DEFMENU_H
