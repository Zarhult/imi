#ifndef MENU_H
#define MENU_H

typedef struct menuItem {
    int row, col;
    const char* text;
} MenuItem;

MenuItem MenuItem_new(int, int, const char *);

void drawItem(MenuItem *);
void selectItem(MenuItem *, MenuItem *);

#endif // MENU_H
