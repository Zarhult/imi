#ifndef WORDMENU_H
#define WORDMENU_H

#include <stddef.h>

#include "word.h"

typedef struct wordMenu {
    Word *array;
    size_t size;
    int used;
    int currIndex;
} WordMenu;

WordMenu WordMenu_new(size_t initialSize);

void WordMenu_insert(WordMenu *, Word *);
void WordMenu_delete(WordMenu *, int);
void WordMenu_free(WordMenu *);

void WordMenu_draw(WordMenu *, int);
void WordMenu_select(WordMenu *, int);

#endif // WORDMENU_H
