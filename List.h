#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UNTITLED_List_H
#define UNTITLED_List_H

#endif //UNTITLED_List_H
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
// Credit to P. Tantalo for providing Queue.h, the basis of this program
// Implementation file for an integer que adt called List
//-----------------------------------------------------------------------------

#ifndef _List_H_INCLUDE_
#define _List_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pQ);


// Access functions -----------------------------------------------------------

// index()
// Returns current index.
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

// back()
// Returns back element.
// Pre: length()>0
int back(List L);

// length()
// Returns the length of Q.
int length(List Q);

// int index()
// Returns index of cursor element.
int index();

// int get()
// returns the data of the current element.
int get(List L);



// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List Q);


// Manipulation procedures ----------------------------------------------------

// void clear(List L)
// Resets this List to its original empty state.
void clear(List L);

// void moveFront()
// If List is non-empty. places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L);

// void moveBack()
// If List is non-empty, places the cursor under the front element,
void moveBack(List L);

// void moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L);

// void movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L);

// void append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data);

// void prepend(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
// Pre: !isEmpty(L)
void prepend(List L, int data);

// insertBefore()
// Insert new element before the cursor.
// Pre: length ()>0, index()>=0
void insertBefore(List L, int data);

// void insertAfter (List L, int data)
// Insert new element After cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data);

// deleteFront(List L)
// Deletes front element from this List.
// Pre: !this.isEmpty()
void deleteFront(List L);

// void deleteBack(List L)
// Deletes the bak element.
// Pre: length()>0
void deleteBack(List L);

// void deleteThis()... this is delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in Q on a single line to stdout.
void printListLine(List Q);

// printList()
// prints data elements in L to file out.
void printList(FILE* out, List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L);

#endif