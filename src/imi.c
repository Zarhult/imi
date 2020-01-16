#include <stddef.h>
#include <signal.h>
#include <locale.h>

#include <ncurses.h>

#include "word.h"
#include "wordmenu.h"

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

    // TODO: put this in an if(has_colors() == TRUE) block
    //start_color();
    //init_pair(1, COLOR_WHITE, COLOR_BLACK);
    //attron(COLOR_PAIR(1));

    int row, col;
    getmaxyx(stdscr, row, col);

    attron(A_UNDERLINE);
    printw("imi - A Japanese dictionary tool for nerds");
    attroff(A_UNDERLINE);

    // prepare menu
    WordMenu entries = WordMenu_new(1);
    Word test1 = Word_new("テキスト", "てきすと", "text");
    Word test2 = Word_new("日本語", "にほんご", "japanese");
    Word test3 = Word_new("魔女", "まじょ", "witch");
    Word test4 = Word_new("長い", "ながい", "long");
    WordMenu_insert(&entries, &test1);
    WordMenu_insert(&entries, &test2);
    WordMenu_insert(&entries, &test3);
    WordMenu_insert(&entries, &test4);

    // draw menu and select first item
    int i;
    for (i = 0; i < entries.used; ++i) {
	WordMenu_draw(&entries, i);
    }
    WordMenu_select(&entries, 0);

    // main loop
    int ch;
    while( (ch = getch()) != 'q' ) {
        if (ch == 'j' && entries.currIndex < entries.used - 1) {
            WordMenu_select(&entries, entries.currIndex + 1);
        }
        else if (ch == 'k' && entries.currIndex > 0) {
            WordMenu_select(&entries, entries.currIndex - 1);
        }

        refresh();
    }

    // catch resize event
    signal(SIGWINCH, resizeHandler);

    // end
    WordMenu_free(&entries);
    endwin();

    return 0;
}

void resizeHandler(int sig) {
    int row, col;
    getmaxyx(stdscr, row, col);

    // TODO: handle here
}
