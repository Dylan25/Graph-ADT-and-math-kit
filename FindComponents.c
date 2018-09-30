//-----------------------------------------------------------------------------
// FindComponents.c by Dylan Welch. ID: dtwelch@ucsc.edu
// FindComponents.c utilizes an integer que adt called List.c and an adjacency list Graph ADT called Graph.c
// to read a graph from a file in the first argument and identify it's strongly connected components printing the graph and its
// strongly connected components to a file in the second argument;
//-----------------------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 160


int main(int argc, char * argv[]){

    int Gorder;
    int Gedge1, Gedge2;
    int lineCount = 0;
    int count = 1;
    int compcount = 0;
    List sortOrder = newList();
    FILE *in, *out;


    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }


    // counts lines in the input file;
    while(!feof(in)) {
        char currentChar = fgetc(in);
        if (currentChar == '\n') {
            lineCount++;
        }
    }

    rewind(in);

    // gets order of graph and first vertex
    fscanf(in, "%d", &Gorder);
    Graph G = newGraph(Gorder);
    fscanf(in, "%d %d", &Gedge1, &Gedge2);
    addArc(G, Gedge1, Gedge2);

    // gets rest of vertices
    for (int i = 0; i < lineCount; i++){
        fscanf(in, "%d %d", &Gedge1, &Gedge2);
        addArc(G, Gedge1, Gedge2);
    }

    // prints the graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // creates sortOrder used as S
    for (int i = 1; i <= getOrder(G); i++) {
        append(sortOrder, i);
    }

    // run DFS on G and transpose G
    DFS(G, sortOrder);
    Graph GT = transpose(G);
    DFS(GT, sortOrder);

    // count the components
    for (int i = 1; i <= getOrder(GT); i++)
    {
        if (getParent(GT, i) == NIL) {
            compcount++;
        }
    }

    // print number of components
    fprintf(out, "\n");
    fprintf(out, "%s %d %s", "G contains", compcount, "strongly connected components:\n");

    //create an array of Lists
    List* components;
    components = malloc((compcount + 1)*sizeof(List));
    for (int i=0; i <= compcount; i++) {
        components[i] = newList();
    }

    // Fill the array of lists with the vertices of each component
    moveBack(sortOrder);
    while (index(sortOrder) != -1) {
        if (getParent(GT, (get(sortOrder))) == NIL) {
            prepend(components[count], get(sortOrder));
            count++;
            movePrev(sortOrder);
        }
        else {
            prepend(components[count], get(sortOrder));
            movePrev(sortOrder);
        }
    }

    // print the array of lists
    for (int i=1; i <= compcount; i++) {
        fprintf(out, "%s %d", "Component", i);
        fprintf(out, ": ");
        printList(out, components[i]);
        fprintf(out, "\n");
    }


    // close files and free memory;
    fclose(in);
    fclose(out);

    freeList(&sortOrder);
    freeGraph(&G);
    freeGraph(&GT);

    for (int i = 0; i <= compcount; i++) {
        freeList(&(components[i]));
    }
    free(components);
}