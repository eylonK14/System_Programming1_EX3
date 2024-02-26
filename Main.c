#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

#define ENTER_AT_INDEX 2
#define PRINT 3
#define LENGTH 4
#define PRINT_AT_INDEX 5
#define AMOUNT_OF_CHARS 6
#define PRINT_ALL_TIMES 7
#define DELETE_ALL_TIMES 8
#define DELETE_AT_INDEX 9
#define REVERSE 10
#define CLEAR 11
#define SORT 12
#define CHECK_SORTED 13

char* getWord()
{
    char* str = NULL;
    size_t len = 0;
    getline(&str, &len, stdin);
    str[strcspn(str, "\r\n")] = 0;
    return str;
}

int main(int argc, char **argv)
{
    char *str = NULL;

    int choise = 0, index = 0, wordCount = 0;

    StrList *list = StrList_alloc();

    do
    {
        scanf("%d", &choise);
        getchar();

        switch (choise)
        {
        case 1:
            StrList_free(list);
            list = StrList_alloc();
            scanf("%d", &wordCount);
            getchar();

            str = getWord();

            char *word = strtok(str, " ");
            while (word != NULL)
            {
                StrList_insertLast(list, word);
                word = strtok(NULL, " ");
                wordCount--;
            }
            if (wordCount != 0)
                return 1;
            break;
        case ENTER_AT_INDEX:
            scanf("%d", &index);
            getchar();
            str = getWord();
            StrList_insertAt(list, str, index);
            break;
        case PRINT:
            StrList_print(list);
            break;
        case LENGTH:
            printf("%zu\n", StrList_size(list));
            break;
        case PRINT_AT_INDEX:
            scanf("%d", &index);
            getchar();
            StrList_printAt(list, index);
            break;
        case AMOUNT_OF_CHARS:
            printf("%d\n", StrList_printLen(list));
            break;
        case PRINT_ALL_TIMES:
            str = getWord();
            printf("%d\n", StrList_count(list, str));
            break;
        case DELETE_ALL_TIMES:
            str = getWord();
            StrList_remove(list, str);
            break;
        case DELETE_AT_INDEX:
            scanf("%d", &index);
            getchar();
            StrList_removeAt(list, index);
            break;
        case REVERSE:
            StrList_reverse(list);
            break;
        case CLEAR:
            StrList_free(list);
            break;
        case SORT:
            StrList_sort(list);
            break;
        case CHECK_SORTED:
            printf("%s\n", StrList_isSorted(list) ? "true" : "false");
            break;
        default:
            break;
        }
    } while (choise);

    StrList_free(list);
    free(list);
    free(str);

    return 0;
}
