#include <stdio.h>
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

/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
input: size (int) - number of chars to read
       str (char*) - string to read into
output: none
*/
void myFgets(int size, char *str)
{
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}

int main(int argc, char *argv)
{
    char A = 0;
    ;
    char *str;
    int choise = 0, index = 0, wordCount;
    StrList *list = StrList_alloc();

    do
    {
        scanf("%d", &choise);

        switch (choise)
        {
        case 1:
            fscanf("%c", A);
            fscanf("%d", wordCount);
            scanf("%s", str);
            
            StrList_insertLast(list, str);
            break;
        case ENTER_AT_INDEX:
            scanf("%d", index);
            fscanf("%s", str);
            StrList_insertAt(list, str, index);
            break;
        case PRINT:
            StrList_print(list);
            break;
        case LENGTH:
            printf("%d", StrList_printLen(list));
        case PRINT_AT_INDEX:
            StrList_printAt(list, index);
        case AMOUNT_OF_CHARS:
            StrList_printLen(list);
            break;
        case PRINT_ALL_TIMES:
            fscanf("%s", str);
            StrList_count(list, str);
            break;
        case DELETE_ALL_TIMES:
            fscanf("%s", str);
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

    return 0;
}
