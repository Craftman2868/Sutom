#include "sutom.h"

#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
Load dictionary.

WARNING: Don't forget to call freeDict()
*/
char** loadDict() {
    FILE *file = fopen(DICT_PATH, "r");

    int lines = 1;

    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n')
            lines++;
    }

    char** dict = (char**) malloc(sizeof(char*) * (lines + 1));

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < lines; i++) {
        char* word = (char*) malloc(MAX_WORD_SIZE);

        fgets(word, MAX_WORD_SIZE, file);

        if (word[strlen(word)-1] == '\n')
            word[strlen(word)-1] = 0;

        dict[i] = word;
    }

    fclose(file);

    dict[lines] = NULL;

    return dict;
}

void freeDict(char* dict[]) {
    char* word;

    int i = 0;
    while ((word = dict[i++]) != NULL)
        free(word);
    
    free(dict);
}

int dictSize(char* dict[]) {
    int i = 0;

    while ((dict[i++]) != NULL);

    return i-1;
}

int chooseWord(char* word) {
    if (word == NULL) return -1;

    char** dict = loadDict();

    char* w = randchoice(dict, dictSize(dict));

    strncpy(word, w, MAX_WORD_SIZE);

    freeDict(dict);

    return strlen(word);
}
