//-----------------------------------------------------------------------------
// Graph.c by Dylan Welch ID: dtwelch
// Implementation file for an integer based adjacency list representation of
// directed or undirected graphs with BFS and DFS capability.
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
    int* Discover;
    int* Finish;
    int* component;
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
    Q->Discover = malloc((n+1)*sizeof(int));
    Q->Finish = malloc((n+1)*sizeof(int));
    Q->component = malloc((n+1)*sizeof(int));
    for (int i=0; i <= n; i++) {
        //Q += malloc(sizeof(ListObj));
        Q->adj[i] = newList();
        //Q += malloc(sizeof(int));
        Q->color[i] = white;
        //Q += malloc(sizeof(int));
        Q->parent[i] = NIL;
        Q->Discover[i] = UNDEF;
        Q->Finish[i] = UNDEF;
        Q->component[i] = UNDEF;
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
        free((*pG)->Discover);
        free((*pG)->Finish);
        free((*pG)->component);
        free(*pG);
        *pG = NULL;
    }
}


// Access functions -----------------------------------------------------------

// getDiscover(Graph )
// returns the discover time of u
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u) {
    if ( 1 > u || getOrder(G) < u) {
        printf("ERROR: input vertex out of acceptable value range");
        return(0);
    }
    return (G->Discover[u]);
}

// getFinish(Graph G, int u);
// returns the finish time of u
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u) {
    if ( 1 > u || getOrder(G) < u) {
        printf("ERROR: input vertex out of acceptable value range");
        return(0);
    }
    return (G->Finish[u]);
}

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
// returns the distance to vertex u;
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

// Void visit(Graph G, int x);
// a helper function to DFS
void visit(Graph G, int x, int* time, int k, List S) {
    G->color[x] = gray;
    G->Discover[x] = ++*time;
    G->component[x] = k;
    //moveFront(G->adj[x]);
    moveFront(G->adj[x]);
    while (index(G->adj[x]) != -1) {
        if (G->color[get(G->adj[x])] == white) {
            G->parent[get(G->adj[x])] = x;
            visit(G, (get(G->adj[x])), time, k, S);
        }
        moveNext(G->adj[x]);
    }
    G->color[x] = black;
    G->Finish[x] = ++*time;
    //deleteFront(S);
    prepend(S, x);
}


// void DFS(Graph G, List S);
// performs DFS on Graph G altering its color, Discover, and Finish
// fields.
// /* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S) {
    if (length(S) != getOrder(G)) {
        printf("ERROR: list length not equal to graph order");
        return;
    }

    for (int i = 0; i <= G->order; i++ ) {
        G->color[i] = white;
        G->parent[i] = NIL;
        G->Finish[i] = UNDEF;
        G->Discover[i] = UNDEF;
    }

    //moveFront(G->adj);
    int time = 0;
    //k is connected component number
    int k = 0;

    moveFront(S);
    while (index(S) != -1) {
        if (G->color[get(S)] == white) {
            //moveFront(G->adj[get(S)]);
            k = k+1;
            visit(G, get(S), &time, k, S);
        }
        moveNext(S);
    }
    for (int i = 0; i < getOrder(G); i++) {
        deleteBack(S);
    }

}

/*** Other operations ***/

// void printGraph(FILE* out, Graph G);
// Prints an adjacency list representation of the graph G
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d", i);
        fprintf(out, ": ");
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}

// Graph transpose(Graph G);
// returns graph Q where all edges
// are the reverse of all edge directions in graph G.
Graph transpose(Graph G) {
    //use a nested for loop for arcs

    Graph Q = newGraph(getOrder(G));

    for (int i=0; i <= G->order; i++) {
        moveFront(G->adj[i]);
        while (index(G->adj[i]) != -1) {
            addArc(Q, get(G->adj[i]), i);
            moveNext(G->adj[i]);
        }
    }

    for (int i=0; i <= G->order; i++) {
        //Q += malloc(sizeof(ListObj));
        //Q += malloc(sizeof(int));
        Q->color[i] = G->color[i];
        //Q += malloc(sizeof(int));
        Q->parent[i] = G->parent[i];
        Q->Discover[i] = G->Discover[i];
        Q->Finish[i] = G->Finish[i];
        Q->component[i] = G->component[i];
        //Q += malloc(sizeof(int));
        Q->distance[i] = G->distance[i];
    }
    Q->size = G->size;
    Q->lastBFS = G->lastBFS;
    return(Q);
}

// Graph copyGraph(Graph G);
// returns a copy of graph G.
Graph copyGraph(Graph G) {
    //use a nested for loop for arcs

    Graph Q = newGraph(getOrder(G));

    for (int i=0; i <= G->order; i++) {
        //Q += malloc(sizeof(ListObj));
        Q->adj[i] = copyList(G->adj[i]);
        //Q += malloc(sizeof(int));
        Q->color[i] = G->color[i];
        //Q += malloc(sizeof(int));
        Q->parent[i] = G->parent[i];
        Q->Discover[i] = G->Discover[i];
        Q->Finish[i] = G->Finish[i];
        Q->component[i] = G->component[i];
        //Q += malloc(sizeof(int));
        Q->distance[i] = G->distance[i];
    }
    Q->size = G->size;
    Q->lastBFS = G->lastBFS;
    return(Q);
}
