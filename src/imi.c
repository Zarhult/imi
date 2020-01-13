#include <signal.h>
#include <locale.h>

#include <ncurses.h>

#include "menu.h"
#include "menuarray.h"

// ??!

void resizeHandler(int);

int main(int argc, char *argv[]) {
    // setup
    setlocale(LC_ALL, "ja_JP.UTF-8");

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int row, col;
    getmaxyx(stdscr, row, col);

    MenuItem dummyItem = MenuItem_new(-1, -1, "");

    attron(A_UNDERLINE);
    printw("imi - A Japanese dictionary tool for nerds");
    attroff(A_UNDERLINE);

    // prepare menu
    MenuArray entries = MenuArray_new(1);
    MenuItem test1 = MenuItem_new(1, 0, "テキスト");
    MenuItem test2 = MenuItem_new(2, 0, "日本語って難しいだね");
    MenuArray_insert(&entries, &test1);
    MenuArray_insert(&entries, &test2);
    // draw menu and select first item
    int i;
    for (i = 0; (size_t)i < entries.used; ++i) {
        drawItem(&entries.array[i]);
    }
    MenuItem *curr = &entries.array[0];
    selectItem(curr, &dummyItem); //selectItem requires a previously selected item, so we use a dummy for the first selection
    // main loop
    int ch;
    while((ch = getch())) {
        if (ch == 'j' && curr != &entries.array[entries.used - 1]) {
            selectItem(curr + 1, curr);
            ++curr;
        }
        else if (ch == 'k' && curr != &entries.array[0]) {
            selectItem(curr - 1, curr);
            --curr;
        }

        refresh();
    }

    // catch resize event
    signal(SIGWINCH, resizeHandler);

    // end
    MenuArray_free(&entries);
    endwin();

    return 0;
}

void resizeHandler(int sig) {
    int row, col;
    getmaxyx(stdscr, row, col);
    // handle here
}
