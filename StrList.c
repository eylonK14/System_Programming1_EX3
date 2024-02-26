#include <stdio.h>
#include <string.h>
#include "StrList.h"

int cmpstr(void const *a, void const *b);

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

Node *Node_alloc(const char *data, Node *next)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (p != NULL)
    {
        p->_data = (char *)malloc((strlen(data) + 1) * sizeof(char));
        if (p->_data != NULL)
        {
            strcpy(p->_data, data);
            p->_next = next;
            return p;
        }
        else
        {
            fprintf(stderr, "Error occurred while allocating the node!");
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "Error occurred while allocating the node!");
        exit(1);
    }
}

void Node_free(Node *node)
{
    if (node != NULL)
    {
        free(node->_data);
        free(node);
    }
}

//------------------------------------------------

/*
 * StrList represents a StrList data structure.
 */

typedef struct _StrList
{
    Node *_head;
    size_t _size;
} StrList, *Strlstptr;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_alloc()
{
    StrList *p = (StrList *)malloc(sizeof(StrList));
    if (p == NULL)
    {
        fprintf(stderr, "Error occurred while allocating the list!");
        exit(1);
    }
    p->_head = NULL;
    p->_size = 0;
    return p;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
/*

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
}*/
void StrList_free(StrList *StrList)
{
    if (StrList == NULL)
    {
        return;
    }
    Node *p1 = StrList->_head;
    while (p1)
    {
        Node *p2 = p1;
        p1 = p1->_next;

        // Free the data string within the Node
        // free(p2->_data);

        // Then free the Node itself
        Node_free(p2);
    }

    StrList->_size = 0;
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
    if (StrList->_head == NULL)
    {
        StrList->_head = Node_alloc(data, NULL);
        ++(StrList->_size);
    }
    else
    {
        Node *curr = StrList->_head;
        Node *new = Node_alloc(data, NULL);
        if (new != NULL)
        {
            while (curr->_next != NULL)
            {
                curr = curr->_next;
            }
            curr->_next = new;
            ++(StrList->_size);
        }
    }
}
/*
 * Inserts an element at given index
 */
void StrList_insertAt(StrList *StrList, const char *data, int index)
{

    Node *curr = StrList->_head;
    Node *new = Node_alloc((char *)data, NULL);
    if (index < 0 || index > StrList->_size || new == NULL)
    {
        return;
    }
    if (index == 0)
    {
        new->_next = StrList->_head;
        StrList->_head = new;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            curr = curr->_next;
        }
        new->_next = curr->_next;
        curr->_next = new;
    }
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
    if (StrList->_size < 0 || StrList == NULL || StrList->_head == NULL)
    {
        printf("\n");
        return;
    }
    while (p)
    {
        printf("%s ", p->_data);
        p = p->_next;
    }
    printf("\n");
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList *Strlist, int index)
{
    int i = 0;
    Node *p1 = Strlist->_head;
    if (index < 0 || index > Strlist->_size || Strlist == NULL || Strlist->_head == NULL)
    {
        printf("\n");
        return;
    }
    while (i < index && p1 != NULL)
    {
        p1 = p1->_next;
        i++;
    }
    printf("%s\n", p1->_data);
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

        if (p1->_data == NULL)
            len += 0;
        else
            len += strlen(p1->_data);
        p1 = p1->_next;
    }

    return len;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList *StrList, const char *data)
{
    if (StrList == NULL || StrList->_head == NULL || StrList->_size < 1 || data == NULL)
        return 0;

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
void StrList_remove(StrList *list, const char *data)
{
    if (list == NULL || list->_head == NULL || list->_size < 1 || data == NULL)
        return;

    Node *curr = list->_head;
    Node *prev = NULL;
    Node *del = NULL;

    if (!(strcmp(list->_head->_data, data)))
    {
        del = list->_head;
        list->_head = list->_head->_next;
        --(list->_size);
        Node_free(del);
    }

    else
    {
        while (curr != NULL)
        {
            if (!(strcmp(curr->_data, data)))
            {
                prev->_next = curr->_next;
                --(list->_size);
                Node_free(curr);
            }
            else
            {
                prev = curr;
                curr = curr->_next;
            }
        }
    }
}

/*
    Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList *list, int index)
{
    if (list == NULL || list->_head == NULL || list->_size < 1 || index < 0 || index > list->_size)
        return;

    int i = 0;
    Node *curr = list->_head;
    Node *del = NULL;

    if (index == 0)
    {
        del = list->_head;
        list->_head = list->_head->_next;
        --(list->_size);
        Node_free(del);
    }

    else
    {
        while (curr && i < index - 1)
        {
            curr = curr->_next;
            i++;
        }
        del = curr->_next;
        curr->_next = curr->_next->_next;
        --(list->_size);
        Node_free(del);
    }
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList *StrList1, const StrList *StrList2)
{
    if (StrList1 == NULL || StrList1->_head == NULL || StrList2 == NULL || StrList2->_head == NULL || StrList1->_size < 1 || StrList2->_size < 1)
        return 0;

    const int neq = 0;
    const int eq = 1;

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
    if (StrList == NULL || StrList->_head == NULL || StrList->_size < 1)
        return NULL;

    Strlstptr ret = StrList_alloc();
    const Node *old = StrList->_head;
    Node **copy = &(ret->_head);
    ret->_size = StrList->_size;
    while (old)
    {
        *copy = Node_alloc(strdup(old->_data), NULL);
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
    if (StrList == NULL || StrList->_head == NULL || StrList->_size < 1)
        return;
    Node *curr = StrList->_head;
    Node *prev = NULL;
    Node *temp = NULL;
    while (curr != NULL)
    {
        temp = curr->_next;
        curr->_next = prev;
        prev = curr;
        curr = temp;
    }
    StrList->_head = prev;
}

/*
 * Sort the given list in lexicographical order
 */
void StrList_sort(StrList *list)
{
    if (list == NULL || list->_head == NULL || list->_size < 1)
        return;

    Node *temp = list->_head;
    char **arr = (char **)malloc(list->_size * sizeof(char *));

    for (int i = 0; i < list->_size; i++)
    {
        arr[i] = temp->_data;
        temp = temp->_next;
    }

    qsort(arr, list->_size, sizeof(char *), cmpstr);

    temp = list->_head;

    for (int i = 0; i < list->_size; i++)
    {
        temp->_data = arr[i];
        temp = temp->_next;
    }

    free(arr);
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList *lst)
{
    if (lst == NULL || lst->_head == NULL || lst->_size < 1)
        return 0;

    int eq = 0;

    StrList *list = StrList_alloc();
    list = StrList_clone(lst);
    StrList_sort(list);

    eq = StrList_isEqual(lst, list);

    StrList_free(list);

    return eq;
}

int cmpstr(void const *a, void const *b)
{
    return strcmp(*(char const **)a, *(char const **)b);
}