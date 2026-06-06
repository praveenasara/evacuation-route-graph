#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

double *dijkstra(Graph *g, int src, int *prev);
void    print_path(int *prev, int src, int dest);

#endif