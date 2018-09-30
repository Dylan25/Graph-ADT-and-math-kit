//
// Created by Dylan on 10/15/2017.
//


//-----------------------------------------------------------------------------
// List.c by Dylan Welch
// Credit to P. Tantalo for providing Queue.c, the basis of this program
// Implementation file for an integer que adt called List
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
} ListObj;

typedef ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
    List Q;
    Q = malloc(sizeof(ListObj));
    Q->front = Q->back = Q->cursor = NULL;
    Q->length = 0;
    Q->index = -1;
    return(Q);
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(List* pQ){
    if(pQ!=NULL && *pQ!=NULL) {
        while( !isEmpty(*pQ) ) {
            deleteFront(*pQ);
        }
        free(*pQ);
        *pQ = NULL;
    }
}


// Access functions -----------------------------------------------------------

// int get()
// returns the data of the current element.
int get(List L) {
    if ( L==NULL ){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    else if (L->index < 0) {
        printf("List Error: calling get() on an undefined cursor\n");
        exit(1);
    }
    else
        return(L->cursor->data);
}

// int index()
// returns the current index.
int index(List L) {
   if (L->cursor != NULL)
       return L->index;
    else
       return -1;
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
    if ( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if ( isEmpty(L) ){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return(L->front->data);
}

// back()
// Returns back element.
// Pre: length()>0
int back(List L){
    if ( L==NULL ){
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    if( L->length <= 0 ){
        printf("List Error: back() called on empty List");
        exit(1);
    }
    return(L->back->data);
}

// length()
// Returns the length of Q.
int length(List Q){
    if ( Q==NULL ){
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return(Q->length);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List Q){
    if ( Q==NULL ){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }
    return(Q->length==0);
}


// Manipulation procedures ----------------------------------------------------

// void clear(List L)
// Resets this List to its original empty state.
void clear(List L) {
    if( L==NULL ){
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    Node N = NULL;
    N = L->front;
    while (N != L->back) {
        N = N->next;
        deleteFront(L);
    }
    freeNode(&N);
    L->index = -1;
    L->length = 0;
}

// void moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if( L==NULL ){
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// void moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if( L==NULL ){
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

// void moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L) {
    if( L==NULL ){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor != NULL) {
        if (L->index != L->length - 1) {
            L->cursor = L->cursor->next;
            L->index++;
        }
        else if (L->index == L->length - 1) {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}

// void movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L) {
    if( L==NULL ){
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor != NULL) {
        if(L->index != 0) {
            L->cursor = L->cursor->prev;
            L->index--;
        }
        else {
            L->cursor = L->cursor->prev;
            L->index = -1;
        }
    }
}

// void append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data)
{
    if( L==NULL ){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(data);
    if( isEmpty(L) ) {
        L->front = L->back = N;
    }else{
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}

// void prepend(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
    if (L==NULL){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(data);
    if (isEmpty(L)) {
        L->front = L->back = N;
    }else{
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    L->length++;
    L->index++;
}

// void insertBefore (int data)
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore (List L, int data) {
    if (L==NULL){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if (L->length <= 0) {
        printf("List Error: calling insertBefore() on an empty List");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: calling insertBefore() on an undefined cursor");
        exit(1);
    }
    Node N = newNode(data);
    if (L->index > 0) {
        L->cursor->prev->next = N;
        N->prev = L->cursor->prev;
        //index++;
        //length++;
        //EnList(L, data);
    }
    else
        L->front = N;
    N->next = L->cursor;
    L->cursor->prev = N;
    L->index++;
    L->length++;
}

// void insertAfter (int data)
// Insert new element After cursor.
// Pre: length()>0, index()>=0
void insertAfter (List L, int data) {
    if (L==NULL){
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if (L->length <= 0) {
        printf("List Error: calling insertAfter() on an empty List");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: calling insertAfter() on an undefined cursor");
        exit(1);
    }
    Node N = newNode(data);
    if (L->index != L->length-1) {
        N->next = L->cursor->next;
        L->cursor->prev = N;
    }
    else
        L->back = N;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length++;
}

// deleteFront()
// Deletes front element from this List.
// Pre: length > 0
void deleteFront(List L) {
    if (L==NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if (L->length <= 0) {
        printf("List Error: calling deleteFront() on an empty List");
        exit(1);
    }
    Node N = NULL;
    N = L->front;
    if (L->length > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    else {
        L->front = L->back = NULL;
    }
    if (L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
    }
    if (L->index > -1) {
        L->index--;
    }
    freeNode(&N);
    L->length--;
}

// void deleteBack()
// Deletes the bak element.
// Pre: length()>0
void deleteBack(List L) {
    if (L==NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if (L->length <= 0) {
        printf("List Error: calling deleteBack() on an empty List");
        exit(1);
    }
    Node N = NULL;
    N = L->back;
    if(L->length > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else {
        L->front = L->back = NULL;
    }
    if(L->index == L->length-1) {
        L->cursor = NULL;
        L->index = -1;
    }
    freeNode(&N);
    L->length--;
}

// void delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L==NULL){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
    if (L->length <= 0) {
        printf("List Error: calling delete() on an empty List");
        exit(1);
    }
    if (L->index < 0) {
        printf("List Error: calling delete() on an undefined cursor");
        exit(1);
    }
    Node N = NULL;
    N = L->cursor;
    if (L->index != 0 && L->index != L->length-1) {
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
    }
    else if (L->index == 0) {
        L->front = L->cursor->next;
        L->cursor->next->prev = NULL;
    }
    else if (L->index == L->length-1) {
        L->back = L->cursor->prev;
        L->cursor->prev->next = NULL;
    }
    freeNode(&N);
    L->cursor = NULL;
    L->index = -1;
    L->length--;
}




// Other Functions ------------------------------------------------------------

// printListLine()
// Prints data elements in Q on a single line to stdout.
void printListLine(List Q){
    if( Q==NULL ){
        printf("List Error: calling printListLine() on NULL List reference\n");
        exit(1);
    }
    Node N = NULL;

    for(N = Q->front; N != NULL; N = N->next){
        printf("%d ", N->data);
    }
    printf("\n");
    freeNode(&N);
}


// printList()
// prints data elements in L to file out.
void printList(FILE* out, List L) {

    if (out == NULL) {
        printf("List Error: target outfile undefined.\n");
        exit(1);
    }
    if( L==NULL ){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }
    Node N = NULL;
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d", N->data);
        fprintf(out, "%s", " ");
    }
    freeNode(&N);
}


// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){

    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }
    int eq = 0;
    eq = ( A->length == B->length );
    Node N = NULL;
    Node M = NULL;
    N = A->front;
    M = B->front;


    while( eq && N!=NULL){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    if(N==NULL) {
        freeNode(&N);
    }
    if(M==NULL) {
        freeNode(&M);
    }
    return eq;
}

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
    if (L == NULL) {
        printf("List Error: Can't copy Null List Object.\n");
        exit(1);
    }

    List newL = newList();
    Node N = NULL;
    N = L->front;

    while (N != NULL) {
        append(newL, N->data);
        N = N->next;
    }
    if(N==NULL){
        freeNode(&N);;
    }
    return newL;
}

