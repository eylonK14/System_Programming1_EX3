#include <stdio.h>
#include "StrList.h"
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char **argv)
{

    char *str = "hello";
    char *str2 = "to";
    char *str3 = "you";
    int choise = 0, index = 0, wordCount = 0;
    StrList *list = StrList_alloc();

    StrList_insertLast(list, str);
    StrList_insertLast(list, str2);
    StrList_insertLast(list, str3);

    do
    {
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
            scanf("%d", &wordCount);
            while (wordCount)
            {
                scanf("%[^\n]s", str);
                puts(str);
                StrList_insertLast(list, str);
                wordCount--;
            }
            break;
        case ENTER_AT_INDEX:
            scanf("%d", &index);
            scanf("%[^\n]s", str);
            StrList_insertAt(list, str, index);
            break;
        case PRINT:
            StrList_print(list);
            break;
        case LENGTH:
            printf("%zu", StrList_size(list));
            break;
        case PRINT_AT_INDEX:
            StrList_printAt(list, index);
            break;
        case AMOUNT_OF_CHARS:
            printf("%d", StrList_printLen(list));
            break;
        case PRINT_ALL_TIMES:
            scanf("%s", str);
            StrList_count(list, str);
            break;
        case DELETE_ALL_TIMES:
            scanf("%[^\n]s", str);
            StrList_remove(list, str);
            break;
        case DELETE_AT_INDEX:
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
            StrList_isSorted(list);
            break;
        default:
            break;
        }
    } while (choise);

    StrList_free(list);

    return 0;
}
