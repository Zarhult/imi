#ifndef MENU_H
#define MENU_H

typedef struct menuItem {
    int startRow;
    int endRow;
    const char *word;
    const char *reading;
    const char *definition;
} MenuItem;

MenuItem MenuItem_new(const char *, const char *, const char *);

#endif // MENU_H
