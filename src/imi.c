#include <stddef.h>
#include <signal.h>
#include <locale.h>
#include <ncurses.h>
#include "worddef.h"
#include "defmenu.h"
#include "parse.h"

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

    // not yet necessary
    //int row, col;
    //getmaxyx(stdscr, row, col);

    attron(A_UNDERLINE);
    printw("imi - A Japanese dictionary tool for nerds");
    attroff(A_UNDERLINE);

    // prepare menu
    DefMenu entries = DefMenu_NEW(1);
    WordDef test1 = WordDef_NEW("かしこ", "かしこ", "TEST");
    WordDef test2 = WordDef_NEW("日本語", "にほんご", "japanese");
    WordDef test3 = WordDef_NEW("魔女", "まじょ", "witch");
    WordDef test4 = WordDef_NEW("長い", "ながい", "long");
    DefMenu_INSERT(&entries, &test1);
    DefMenu_INSERT(&entries, &test2);
    DefMenu_INSERT(&entries, &test3);
    DefMenu_INSERT(&entries, &test4);

    // draw menu and select first item
    int i;
    for (i = 0; i < entries.used; ++i) {
	DefMenu_DRAW(&entries, i);
    }
    DefMenu_SELECT(&entries, 0);

    // main loop
    if (argc == 2) {
	char* __attribute__((unused)) search = argv[1]; // unused until implemented
	// TODO: handle parameter word search
    }
    else {
	char ch;
	while( (ch = getch()) != 'q' ) {
	    if (ch == 'j' && entries.currIndex < entries.used - 1) {
		DefMenu_SELECT(&entries, entries.currIndex + 1);
	    }
	    else if (ch == 'k' && entries.currIndex > 0) {
		DefMenu_SELECT(&entries, entries.currIndex - 1);
	    }
	    else if (ch == 'l') {
		WordDef result = searchDict(entries.array[entries.currIndex].word, "jmdict_english");
		DefMenu_INSERT(&entries, &result);
		DefMenu_DRAW(&entries, entries.used - 1);
		DefMenu_SELECT(&entries, entries.used - 1);
	    }

	    refresh();
	}
    }

    // catch resize event
    signal(SIGWINCH, resizeHandler);

    // end
    DefMenu_FREE(&entries);
    endwin();

    return 0;
}

void resizeHandler(int __attribute__ ((unused)) sig) { // sig unused until implemented
    //int row, col;
    //getmaxyx(stdscr, row, col);

    // TODO: handle here
}
