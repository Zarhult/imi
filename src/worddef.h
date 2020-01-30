#ifndef WORDDEF_H
#define WORDDEF_H

typedef struct wordDef {
    int startRow;
    int endRow;
    const char *word;
    const char *reading;
    const char *definition;
} WordDef;

WordDef WordDef_NEW(const char *, const char *, const char *);

#endif // WORDDEF_H
