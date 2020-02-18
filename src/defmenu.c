#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include "worddef.h"
#include "defmenu.h"

DefMenu DefMenu_NEW(size_t initialSize) {
    assert(initialSize > 0);

    struct defMenu arr;
    arr.array = (WordDef *)malloc(initialSize * sizeof(WordDef));
    arr.used = 0;
    arr.size = initialSize;
    arr.currIndex = -1; // set by first MenuArray_select call
    return arr;
}

void DefMenu_INSERT(DefMenu *arr, WordDef *item) {
    assert(item != NULL);

    if ((size_t)arr->used == arr->size) {
	arr->size *= 2;
	arr->array = (WordDef *)realloc(arr->array, arr->size * sizeof(WordDef));
    }
    arr->array[arr->used] = *item;
    ++arr->used;
}


void DefMenu_FREE(DefMenu *arr) {
    free(arr->array);
    arr->array = NULL;
    arr->size = 0;
    arr->used = 0;
    arr->currIndex = -1;
}

void DefMenu_DELETE(DefMenu *arr, int index) {
    assert(index < arr->used);

    // TODO: delete item and rearrange as necessary
    // maybe also go through array and update start/stop rows & redraw screen if item is currently drawn (if will need this functionality)
}

void DefMenu_DRAW(DefMenu *arr, int index) {
    assert(index < arr->used);

    WordDef *drawingItem = &arr->array[index];

    // must set startRow if this is the first time drawing this item
    if (drawingItem->startRow == -1 && drawingItem->endRow == -1) {
	if (arr->used == 0) {
	    drawingItem->startRow = 1; // start just below title if nothing drawn yet
	}
	else {
	    int lowestRow = 0;
	    for (int i = 0; i < arr->used; ++i) {
	       if (arr->array[i].endRow > lowestRow) {
		   lowestRow = arr->array[i].endRow;
	       }
	    }
	    drawingItem->startRow = lowestRow + 2; // + 2 to add spacing between entries 
	}
    }
    
    // now draw word, reading, and definition
    mvprintw(drawingItem->startRow, 0, drawingItem->word);
    printw(" - ");
    printw(drawingItem->reading);
    int row, __attribute__((unused)) col; // col must be fed to getyx even though don't use it
    getyx(stdscr, row, col);
    mvprintw(row + 1, 0, drawingItem->definition);
    // set endRow to last row of definition
    getyx(stdscr, row, col);
    drawingItem->endRow = row;

    assert(drawingItem->startRow != -1);
    assert(drawingItem->endRow != -1);
}

void DefMenu_SELECT(DefMenu *arr, int index) {
    // must be a drawn item
    assert(index < arr->used);
    assert(arr->array[index].startRow != -1);
    assert(arr->array[index].endRow != -1);
    assert(arr->array[index].endRow >= arr->array[index].startRow);

    // unselect previous selection if it exists
    if (arr->currIndex != -1) {
	WordDef *prevSelectedItem = &arr->array[arr->currIndex];
	for (int i = prevSelectedItem->startRow; i <= prevSelectedItem->endRow + 1; ++i) { // + 1 to highlight empty newline between elements
	    mvchgat(i, 0, -1, A_NORMAL, 1, NULL);
	}
    }

    // select new item
    WordDef *selectingItem = &arr->array[index];
    for (int i = selectingItem->startRow; i <= selectingItem->endRow + 1; ++i) { // + 1 to highlight empty newline between elements
	mvchgat(i, 0, -1, A_STANDOUT, 1, NULL);
    }

    arr->currIndex = index;
}
