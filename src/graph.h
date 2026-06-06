#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#define MAX_NODES 10000
#define INF 1e9

typedef struct Edge {
    int dest;
    double weight;
    struct Edge *next;
} Edge;

typedef struct {
    Edge **adj;
    int n;
    int directed;
} Graph;

Graph *graph_create(int n, int directed);
void   graph_add_edge(Graph *g, int src, int dest, double weight);
void   graph_free(Graph *g);
void   graph_print(Graph *g);
Graph *graph_from_file(const char *filename);

#endif
