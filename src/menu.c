#include <ncurses.h>

struct menuItem {
    int row, col;
    const char *text;
};

struct menuItem MenuItem_new(int row, int col, const char *text) {
    struct menuItem item;
    item.row = row;
    item.col = col;
    item.text = text;
    return item;
}

void drawItem(struct menuItem *item) {
    mvprintw((*item).row, (*item).col, (*item).text);
}

void selectItem(struct menuItem *selectingItem, struct menuItem *prevItem) {
    drawItem(prevItem);
    attron(A_STANDOUT);
    drawItem(selectingItem);
    attroff(A_STANDOUT);
}
