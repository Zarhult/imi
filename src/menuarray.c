#include <stdlib.h>

#include "menu.h"

struct menuArray {
    MenuItem *array;
    size_t used;
    size_t size;
};

struct menuArray MenuArray_new(size_t initialSize) {
    struct menuArray arr;
    arr.array = (MenuItem *)malloc(initialSize * sizeof(MenuItem));
    arr.used = 0;
    arr.size = initialSize;
    return arr;
}

void MenuArray_insert(struct menuArray *arr, MenuItem *item) {
    if (arr->used == arr->size) {
	arr->size *= 2;
	arr->array = (MenuItem *)realloc(arr->array, arr->size * sizeof(MenuItem));
    }
    arr->array[arr->used] = *item;
    ++arr->used;
}

void MenuArray_delete(struct menuArray *arr, int index) {
    //TODO: delete item and rearrange as necessary
}

void MenuArray_free(struct menuArray *arr) {
    free(arr->array);
    arr->array = NULL;
    arr->used = 0;
    arr->size = 0;
}
