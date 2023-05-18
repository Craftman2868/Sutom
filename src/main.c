#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sutom.h"

#include <termios.h>
#include <unistd.h>

#define MAX_TRY 6

#define CSI "\033["

enum letterType
{
    CORRECT,
    MISPLACED,
    INCORRECT,
} typedef letterType;

int wordLength;

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void printWord(const char *word)
{
    for (int i = 0; i < wordLength; i++)
    {
        char l = word[i];

        if (l == 0)
            l = '_';

        printf("%c ", l);
    }

    printf("\n");
}

void printLetter(char letter, letterType type)
{
    char *color;
    if (type == CORRECT)
    {
        color = CSI "41m";
    }
    else if (type == INCORRECT)
    {
        color = CSI "2m";
    }
    else if (type == MISPLACED)
    {
        color = CSI "43m";
    }
    printf("%s%c" CSI "0m ", color, letter);
}

void printTry(char *try, char *word)
{
    for (int i = 0; i < wordLength; i++)
    {
        char tryLetter = try[i];
        char letter = word[i];

        if (letter == tryLetter)
        {
            printLetter(tryLetter, CORRECT);
        }
        else if (strchr(word, tryLetter) != NULL)
        {
            printLetter(tryLetter, MISPLACED);
        }
        else
        {
            printLetter(tryLetter, INCORRECT);
        }
    }

    printf("\n");
}

void placeCursor(__int8_t cur)
{
    printf(CSI "F");
    if (cur >= wordLength)
        cur = wordLength-1;
    int m = cur * 2;
    if (m > 0)
        printf(CSI "%dC", m);
}

int main(int argc, char *argv[], char *envp[])
{
    printf("%s\n\n", "Welcome to Sutom!");

    char word[MAX_WORD_SIZE];

    if (chooseWord(word) < 0)
        return -1;

    wordLength = strlen(word);

    char knownLetters[wordLength];

    for (int i = 0; i < wordLength + 1; i++)
    {
        knownLetters[i] = 0;
    }

    knownLetters[0] = word[0];

    int tryN = 0;

    while (tryN < MAX_TRY)
    {
        __int8_t cur = 1;
        char try[wordLength];

        strncpy(try, knownLetters, wordLength + 1);

        printf(CSI "G");
        printWord(try);
        placeCursor(cur);

        char c;
        while ((c = getch()))
        {
            if (cur < wordLength && isalpha(c))
            {
                try[cur] = toupper(c);
                cur++;
            }
            else if (cur > 0 && (c == 127 || c == '\b'))
            {
                cur--;
                try[cur] = 0;
            }
            else if (c == '\n' && cur == wordLength)
            {
                break;
            }
            else
            {
                continue;
            }

            printf(CSI "G");
            printWord(try);
            placeCursor(cur);
        }

        printf(CSI "G");
        printTry(try, word);

        if (strcmp(try, word) == 0)
        {
            tryN = -1;
            break;
        }

        tryN++;
    }

    if (tryN > 0) {
        printf("\nThe word was %s\n", word);
    }

    return 0;
}
