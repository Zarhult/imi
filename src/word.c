struct word {
    int startRow;
    int endRow;
    const char *word;
    const char *reading;
    const char *definition;
};

struct word Word_new(const char *word, const char *reading, const char *definition) {
    struct word item;
    item.startRow = -1; // must be set by draw function at runtime
    item.endRow = -1;   // same
    item.word = word;
    item.reading = reading;
    item.definition = definition;
    return item;
}
