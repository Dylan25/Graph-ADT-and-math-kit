//-----------------------------------------------------------------------------
//
// GraphClient.c
// By Dylan Welch ID: dtwelch created on 11/18/17
// A baisic test file for Graph.c
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    int n=40;

    Graph Gundi = newGraph(n);
    Graph Gdi = newGraph(n);

    addEdge(Gundi, 9, 31);
    addEdge(Gundi, 11, 3);
    addEdge(Gundi, 1, 23);
    addEdge(Gundi, 12, 32);
    addEdge(Gundi, 19, 5);
    addEdge(Gundi, 16, 13);
    addEdge(Gundi, 3, 2);
    addEdge(Gundi, 18, 6);
    addEdge(Gundi, 15, 8);

    addArc(Gdi, 9, 31);
    addArc(Gdi, 11, 3);
    addArc(Gdi, 1, 23);
    addArc(Gdi, 12, 32);
    addArc(Gdi, 19, 5);
    addArc(Gdi, 16, 13);
    addArc(Gdi, 3, 2);
    addArc(Gdi, 18, 6);
    addArc(Gdi, 15, 8);

    printGraph(stdout, Gundi);
    printGraph(stdout, di);

    BFS(Gundi);
    BFS(Gdi);

    printGraph(stdout, Gundi);
    printGraph(stdout, di);

    printf(getOrder(Gundi));
    printf(getSize(Gundi));
    printf(getSource(Gundi));
    printf(getParent(Gundi));
    printf(getDist(Gundi));
    printf(getPath(Gundi));

    printf(getOrder(Gundi));
    printf(getSize(Gundi));
    printf(getSource(Gundi));
    printf(getParent(Gundi));
    printf(getDist(Gundi));
    printf(getPath(Gundi));

    makeNull(Gundi);
    makeNull(Gdi);

    printGraph(stdout, Gundi);
    printGraph(stdout, di);

    return(0);
}