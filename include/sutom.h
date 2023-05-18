#ifndef SUTOM_H
#define SUTOM_H

#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define DICT_PATH "assets/dict.txt"
#define MAX_WORD_SIZE 32

/*
Load dictionary.

WARNING: Don't forget to call freeDict()
*/
char** loadDict();
void freeDict(char* dict[]);

int dictSize(char* dict[]);

int chooseWord(char* word);

#endif  // SUTOM_H
