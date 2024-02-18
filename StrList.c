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

typedef struct _node {
    char* _data;
    struct _node * _next;
} Node;

//------------------------------------------------
// Node implementation
//------------------------------------------------

Node* Node_alloc(char* data,
				 Node* next) {
	Node* p= (Node*)malloc(sizeof(Node));
    strcpy(p->_data, data);
	p->_next= next;
	return p;
}

void Node_free(Node* node) {
    free(node->_data)
	free(node->_next);
}
//------------------------------------------------

/*
 * StrList represents a StrList data structure.
 */

struct _StrList{
    Node* head;
    size_t _size;
};
typedef struct _StrList StrList;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc()
{
    List* p= (List*)malloc(sizeof(List));
	p->_head= NULL;
	p->_size= 0;
	return p;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList)
{
    if (list==NULL) return;
	Node* p1= list->_head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->_next;
		Node_free(p2);
	}
	free(list);
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList)
{
    return list->_size;
}
/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList, const char* data, int index)
{
    int i = 0;
    Node* p1 = list->_head;

    while (i < )
}
/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList, const char* data)
{
    StrList_insertAt(StrList, data,Strlist._size-1)
}
/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList)
{
    return list->_head->_data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList);

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index);

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist);

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data);

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data);

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index);

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2);

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* StrList);

/*
 * Reverces the given StrList. 
 */
void StrList_reverse( StrList* StrList);

/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort( StrList* StrList);

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList);

