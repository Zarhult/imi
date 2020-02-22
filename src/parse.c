#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <bsd/string.h>
#include <ncurses.h>
#include "worddef.h"
#include "parse.h"

WordDef searchDict(const char *word, char *dirName) {
    // TODO: make path variable use $HOME
    // prepare path string
    char path[100] = "/home/calvin/.config/imi/dictionaries/";
    strlcat(path, dirName, sizeof(path));
    strlcat(path, "/", sizeof(path));

    char *filePrefix = "term_bank_";
    char *fileSuffix = ".json";
    strlcat(path, filePrefix, sizeof(path));

    // loop through all valid dictionary files
    FILE *dict = NULL;
    bool resultFound = false;
    char reading[20];
    char definition[200];
    for (int fileNum = 1; (dict || fileNum == 1) && !resultFound; ++fileNum) {
	// finish path string with file number
	char fullPath[100];
	strlcpy(fullPath, path, sizeof(fullPath));
	char fileNumString[10];
	snprintf(fileNumString, sizeof(fileNumString), "%d", fileNum);
	strlcat(fullPath, fileNumString, sizeof(fullPath));
	strlcat(fullPath, fileSuffix, sizeof(fullPath));
	dict = fopen(fullPath, "r");

	if (dict) {
	    char c;
	    while( (c = fgetc(dict)) != EOF ) {
		if (c == '[') {
		    c = fgetc(dict);
		    if (c == '"') {
			// load word into a string and check if it equals search term
			char temp[100] = "";
			while( (c = fgetc(dict)) != '"' ) {
			    char toString[2];
			    toString[0] = c;
			    toString[1] = 0;
			    strlcat(temp, toString, sizeof(temp));
			}

			if (strcmp(temp, word) == 0) {
			    // clear temp
			    memset(temp, 0, sizeof(temp));

			    // skip from ending " to reading in "<WORD>","<READING>"
			    c = fgetc(dict);
			    c = fgetc(dict);
			    c = fgetc(dict);

			    // get reading
			    while( (c = fgetc(dict)) != '"' ) {
				//mvprintw(6, 6, "2");
				char toString[2];
				toString[0] = c;
				toString[1] = 0;
				strlcat(temp, toString, sizeof(temp));
			    }
			    strlcpy(reading, temp, sizeof(reading));

			    // clear temp
			    memset(temp, 0, sizeof(temp));
			    
			    // skip to definition opening brace
			    c = fgetc(dict);
			    while (c != '[') {
				c = fgetc(dict);
			    }

			    // skip to start of definition ["<DEFINITION>"]
			    c = fgetc(dict);
			    c = fgetc(dict);

			    // get definition
			    while( (c = fgetc(dict)) != '"' ) {
				//mvprintw(7, 7, "3");
				char toString[2];
				toString[0] = c;
				toString[1] = 0;
				strlcat(temp, toString, sizeof(temp));
			    }
			    strlcpy(definition, temp, sizeof(definition));

			    // clear temp
			    memset(temp, 0, sizeof(temp));

			    resultFound = true;
			    //reading = "FOUND";
			    //definition = "FOUND";			

			    // break out of while loop once have search results
			    break;
			}
		    }
		}
	    }
	}
    }

    WordDef searchResult = WordDef_NEW(word, reading, definition); 
    return searchResult;
}
