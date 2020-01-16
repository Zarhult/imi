#ifndef WORD_H
#define WORD_H

typedef struct word {
    int startRow;
    int endRow;
    const char *word;
    const char *reading;
    const char *definition;
} Word;

Word Word_new(const char *, const char *, const char *);

#endif // WORD_H
