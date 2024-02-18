#include <stdio.h>
#include <string.h>
#include "StrList.h"

/********************************************************************************
 *
 * A StrList library.
 *
 * This library provides a StrList of STRINGS data structure.
 *
 * This library will fail in unpredictable ways when the system memory runs
 * out.
 *
 ********************************************************************************/

/*
 * Node represents a node in the StrList data structure.
 */

typedef struct _node
{
    char *_data;
    struct _node *_next;
} Node;

//------------------------------------------------
// Node implementation
//------------------------------------------------

Node *Node_alloc(char *data,
                 Node *next)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->_data, data);
    p->_next = next;
    return p;
}

void Node_free(Node *node)
{
    free(node->_data);
    free(node->_next);
}
//------------------------------------------------

/*
 * StrList represents a StrList data structure.
 */

typedef struct _StrList
{
    Node *_head;
    size_t _size;
} StrList , *Strlstptr;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_alloc()
{
    StrList *p = (StrList *)malloc(sizeof(StrList));
    p->_head = NULL;
    p->_size = 0;
    return p;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList *StrList)
{
    if (StrList == NULL)
        return;
    Node *p1 = StrList->_head;
    Node *p2;
    while (p1)
    {
        p2 = p1;
        p1 = p1->_next;
        Node_free(p2);
    }
    free(StrList);
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList *StrList)
{
    return StrList->_size;
}
/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList *StrList, const char *data)
{
    StrList_insertAt(StrList, data, StrList->_size);
}
/*
 * Inserts an element at given index
 */
void StrList_insertAt(StrList *StrList, const char *data, int index)
{
    int i = 1;
    Node *p1 = StrList->_head;
    Node *p2 = NULL;

    while (i < index - 1 && p1 != NULL)
    {
        p1 = p1->_next;
        i++;
    }
    p2 = p1->_next;
    p1->_next = Node_alloc(data, p1->_next);
    p1->_next->_next = p2;
    ++(StrList->_size);
}
/*
 * Returns the StrList first data.
 */
char *StrList_firstData(const StrList *StrList)
{
    return StrList->_head->_data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList *StrList)
{
    const Node *p = StrList->_head;
    while (p)
    {
        printf("(%s)->", p->_data);
        p = p->_next;
    }
    printf("|| size:%zu\n", StrList->_size);
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList *Strlist, int index)
{
    int i = 1;
    Node *p1 = Strlist->_head;

    while (i < index - 1 && p1 != NULL)
    {
        p1 = p1->_next;
        i++;
    }
    printf("(%s)->", p1->_data);
}
/*
 * Return the amount of chars in the list.
 */
int StrList_printLen(const StrList *Strlist)
{
    int len = 0;
    Node *p1 = Strlist->_head;

    while (p1 != NULL)
    {
        p1 = p1->_next;
        len += strlen(p1->_data);
    }

    return len;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList *StrList, const char *data)
{
    Node *p1 = StrList->_head;
    int count = 0;
    while (p1 != NULL)
    {
        if (!(strcmp(p1->_data, data)))
        {
            count++;
        }
        p1 = p1->_next;
    }
    return count;
}

/*
    Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList *StrList, const char *data)
{
    Node *curr = StrList->_head;
    Node *prev = NULL;
    while (curr != NULL)
    {
        if (!(strcmp(curr->_data, data)))
        {
            prev->_next = prev->_next->_next;
        }
        else
        {
            curr = curr->_next;
            prev = prev->_next;
        }
    }
}

/*
    Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList *StrList, int index)
{
    int i = 1;
    Node *curr = StrList->_head;
    Node *prev = NULL;
    while (curr != NULL && i <= index)
    {
        if (i == index - 1)
        {
            prev->_next = prev->_next->_next;
        }
        else
        {
            curr = curr->_next;
            prev = prev->_next;
        }
    }
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList *StrList1, const StrList *StrList2)
{
    const int eq = 0;
    const int neq = 1;

    const Node *p1 = StrList1->_head;
    const Node *p2 = StrList2->_head;
    while (p1)
    {
        if (p2 == NULL || strcmp(p1->_data, p2->_data))
            return neq;
        p1 = p1->_next;
        p2 = p2->_next;
    }
    if (p2 != NULL)
        return neq;
    return eq;
}

/*
 * Clones the given StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_clone(const StrList *StrList)
{
    Strlstptr ret = StrList_alloc();
    const Node *old = StrList->_head;
    Node **copy = &(ret->_head);
    ret->_size = StrList->_size;
    while (old)
    {
        *copy = Node_alloc(old->_data, NULL);
        old = old->_next;
        copy = &((*copy)->_next);
    }
    return ret;
}

/*
 * Reverces the given StrList.
 */
void StrList_reverse(StrList *StrList)
{
    Node *curr = StrList->_head;
    Node *prev = NULL;
    Node *temp = NULL;
    while (curr->_next != NULL)
    {
        temp = curr->_next;
        curr->_next = prev;
        prev = curr;
        curr = temp;
    }
}

/*
 * Sort the given list in lexicographical order
 */
void StrList_sort(StrList *StrList)
{
    int i = 0;
    Node *temp = StrList->_head;
    char *arr[] = (char **)malloc(StrList->_size * sizeof(char *));

    while (temp != NULL)
    {
        arr[i] = temp->_data;
        temp = temp->_next;
        i++;
    }

    qsort(arr, StrList->_size, sizeof(char *), (void *)strcmp);

    i = 0;
    temp = StrList->_head;

    while (temp != NULL)
    {
        temp->_data = arr[i];
        temp = temp->_next;
        i++;
    }
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList *StrList)
{
    Strlstptr list = StrList_alloc();
    list = StrList_clone(StrList);
    StrList_sort(list);
    return StrList_isEqual(StrList, list);
}