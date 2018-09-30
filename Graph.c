//-----------------------------------------------------------------------------
// Graph.c by Dylan Welch ID: dtwelch
// Implementation file for an integer based adjacency list representation of
// directed or undirected graphs with BFS capability.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
    int size;
    int order;
    int lastBFS;
    List* adj;
    int* color;
    int* parent;
    int* distance;
} GraphObj;

typedef GraphObj* Graph;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object.
Graph newGraph(int n){
    Graph Q;
    Q = malloc(sizeof(GraphObj));
    //Q = malloc((n * (sizeof(List))) + (n * 3 * sizeof(int)));
    Q->adj = malloc((n+1)*sizeof(List));
    Q->color = malloc((n+1)*sizeof(int));
    Q->parent = malloc((n+1)*sizeof(int));
    Q->distance = malloc((n+1)*sizeof(int));
    for (int i=0; i <= n; i++) {
        //Q += malloc(sizeof(ListObj));
        Q->adj[i] = newList();
        //Q += malloc(sizeof(int));
        Q->color[i] = white;
        //Q += malloc(sizeof(int));
        Q->parent[i] = NIL;
        //Q += malloc(sizeof(int));
        Q->distance[i] = INF;
    }
    Q->size = 0;
    Q->order = n;
    Q->lastBFS = NIL;
    return(Q);
}


// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.S
void freeGraph(Graph* pG){
    if(pG!=NULL && (*pG)!=NULL) {

        for (int i = 0; i <= getOrder(*pG); i++) {
            /*while( !isEmpty(*pG->adj[i]) ) {
                deleteFront(*pG->adj[i]);
            }*/
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}


// Access functions -----------------------------------------------------------

// getOrder(Graph G)
// returns the order of Graph G
int getOrder(Graph G) {
    return G->order;
}

// getSize(Graph G)
// returns the size of Graph G
int getSize(Graph G) {
    return G->size;
}

// getSource(Graph G)
// returns most recently used BFS source
int getSource(Graph G) {
    if (G->lastBFS != -1) {
        return G->lastBFS;
    }
    else {
        return NIL;
    }
}

// getParent(Graph G, int u)
// returns the parent of vertex u
// precondition 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if ( 1 > u || getOrder(G) < u) {
        printf("ERROR: input vertex out of acceptable value range");
        return(0);
    }
    return G->parent[u];
}

// void getPath(List L, Graph G, int u);
// fills list L with the shortest path from
// getSource(G) to u
// precondition 1 <= u <= getOrder(G)
// precondition getSource(G)!=NIL
void getPath(List L, Graph G, int u) {
    if ( 1 > u || getOrder(G) < u) {
        printf("ERROR: input vertex out of acceptable value range");
        return;
    }
    if (getSource(G) != NIL) {
        if (u == G->lastBFS) {
            append(L, u);
        } else if (G->parent[u] == NIL) {
            append(L, NIL);
        } else {
            getPath(L, G, G->parent[u]);
            append(L, u);
        }
    }
    else {
        printf("ERROR: getPath called on a null source");
    }
}

//int getDist(Graph G, int u);
//int getDist(List L, Graph G, int u);
// precondition 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if ( 1 > u || getOrder(G) < u) {
        printf("ERROR: input vertex out of acceptable value range");
        return(0);
    }
    return G->distance[u];
}

/*** Manipulation procedures ***/
// void makeNull(Graph G);
// makeNull sets the graph G back to the 0 state
void makeNull(Graph G) {
    for (int i = 0; i <= G->order; i++) {
        clear(G->adj[i]);
        G->color[i] = white;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->lastBFS = NIL;
    G->size = 0;
}


// void addEdge(Graph G, int u, int v);
// adds an edge joining u to v, u is in v's adj list and to u's;
void addEdge(Graph G, int u, int v) {
    int actionu = 0;
    int actionv = 0;
    moveFront(G->adj[v]);
    //TODO update this to match the while condition in adarc
    while (index(G->adj[v]) != -1 && actionu == 0) {
        if (get(G->adj[v]) != u) {
            if (get(G->adj[v]) > u) {
                prepend(G->adj[v], u);
                actionu = 1;
                //G->size++;
            }
        }
        else if (get(G->adj[v]) == u) {
            actionu = 2;
        }
        moveNext(G->adj[v]);
    }
    if (actionu == 0) {
        append(G->adj[v], u);
        actionu = 1;
    }

    moveFront(G->adj[u]);
    while (index(G->adj[u]) != -1 && actionv == 0) {
        if (get(G->adj[u]) != v) {
            if (get(G->adj[u]) > v) {
                prepend(G->adj[u], v);
                actionv = 1;
                //G->size++;
            }
        }
        else if (get(G->adj[u]) == v) {
            actionv = 2;
        }
        moveNext(G->adj[u]);
    }
    if (actionv == 0) {
        append(G->adj[u], v);
        actionv = 1;
    }

    if (actionv == 1 || actionu == 1) {
        G->size++;
    }

}



//void addArc(Graph G, int u, int v);
// v is added to u's adjacency list
void addArc(Graph G, int u, int v) {
    int actionv = 0;
    moveFront(G->adj[u]);
    while (index(G->adj[u]) != -1 && actionv != 1) {
        if (get(G->adj[u]) != v) {
            if (get(G->adj[u]) > v) {
                prepend(G->adj[u], v);
                actionv = 1;
                G->size++;
            }
        }
        else if (get(G->adj[u]) == v) {
            actionv = 1;
        }
        moveNext(G->adj[u]);
    }
    if (actionv == 0) {
        append(G->adj[u], v);
        actionv = 0;
        G->size++;
    }
}

// void BFS(Graph G, int s);
// Performs BFS on Graph G altering its color, distance, and parent
// fields to reflect the BFS tree
void BFS(Graph G, int s) {
    G->lastBFS = s;
    for (int i = 0; i <= G->order; i++ ) {
        if (i != s) {
            G->color[i] = white;
            G->distance[i] = INF;
            G->parent[i] = NIL;
        }
    }
    G->color[s] = gray;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    while (!isEmpty(Q)) {
        int x = front(Q);
        deleteFront(Q);
        moveFront(G->adj[x]);
        while (index(G->adj[x]) != -1) {
            if (G->color[get(G->adj[x])] == white) {
                G->color[get(G->adj[x])] = gray;
                G->distance[get(G->adj[x])] = G->distance[x] + 1;
                G->parent[get(G->adj[x])] = x;
                append(Q, get(G->adj[x]));
            }
            moveNext(G->adj[x]);
        }
        G->color[x] = black;
    }
    freeList(&Q);
}

/*** Other operations ***/

// void printGraph(FILE* out, Graph G);
// Prints an adjacency list representation of the graph G
void printGraph(FILE* out, Graph G) {
    for (int i = 0; i <= getOrder(G); i++) {
        printListLine(G->adj[i]);
        printf("\n");
    }
}