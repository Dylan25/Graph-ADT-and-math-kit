//-----------------------------------------------------------------------------
// Graph.h by Dylan Welch ID: dtwelch
// header file for an integer based adjacency list representation of
// directed or undirected graphs with BFS capability
// contains the publicly accessible functions.
//-----------------------------------------------------------------------------
#ifndef _Graph_H_INCLUDE_
#define _Graph_H_INCLUDE_
#include "List.h"

#define INF -7
#define NIL -5
#define white 0
#define gray 1
#define black 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;
typedef struct GraphObj* Graph;

//TODO add comments to describe these functions
/*** Constructors-Destructors ***/
// newGraph()
// Returns reference to new empty Graph object.
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.S
void freeGraph(Graph* pG);

/*** Access functions ***/
// getOrder(Graph G)
// returns the order of Graph G
int getOrder(Graph G);

// getSize(Graph G)
// returns the size of Graph G
int getSize(Graph G);

// getSource(Graph G)
// returns most recently used BFS source
int getSource(Graph G);

// getParent(Graph G, int u)
// returns the parent of vertex u
int getParent(Graph G, int u);

//int getDist(Graph G, int u);
//int getDist(List L, Graph G, int u);
int getDist(Graph G, int u);

//int getPath(List L, Graph G, int u);
//void getPath(List L, Graph G, int u);
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
// void makeNull(Graph G);
// makeNull sets the graph G back to the 0 state
void makeNull(Graph G);

// void addEdge(Graph G, int u, int v);
// adds an edge joining u to v, u is in v's adj list and to u's;
void addEdge(Graph G, int u, int v);

//void addArc(Graph G, int u, int v);
// v is added to u's adjacency list
void addArc(Graph G, int u, int v);

// void BFS(Graph G, int s);
// Performs BFS on Graph G altering its color, distance, and parent
// fields to reflect the BFS tree
void BFS(Graph G, int s);

/*** Other operations ***/
// void printGraph(FILE* out, Graph G);
// Prints an adjacency list representation of the graph G
void printGraph(FILE* out, Graph G);

#endif

