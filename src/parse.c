#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <ncurses.h>
#include "worddef.h"
#include "parse.h"

WordDef searchDict(const char *word, const char *dirName) {
    char path[strlen(dirName)];
    char file[] = "term_bank_1.json";
    strlcpy(path, dirName, strlen(path)); // are these strlcpy size arguments ok?
    strlcat(path, file, strlen(path));
    FILE *dict = fopen(path, "r");

    const char *reading = "";
    const char *definition = "";
    char c;
    while( (c = fgetc(dict)) != EOF ) {
	addch(c);
    }

    WordDef searchResult = WordDef_NEW(word, reading, definition); 
    return searchResult;
}
