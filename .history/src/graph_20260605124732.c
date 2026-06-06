#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph *graph_create(int n, int directed) {
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->directed = directed;
    g->adj = calloc(n, sizeof(Edge *));
    return g;
}

void graph_add_edge(Graph *g, int src, int dest, double weight) {
    Edge *e = malloc(sizeof(Edge));
    e->dest = dest;
    e->weight = weight;
    e->next = g->adj[src];
    g->adj[src] = e;

    if (!g->directed) {
        Edge *e2 = malloc(sizeof(Edge));
        e2->dest = src;
        e2->weight = weight;
        e2->next = g->adj[dest];
        g->adj[dest] = e2;
    }
}

void graph_free(Graph *g) {
    for (int i = 0; i < g->n; i++) {
        Edge *cur = g->adj[i];
        while (cur) {
            Edge *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
    }
    free(g->adj);
    free(g);
}

void graph_print(Graph *g) {
    printf("Graph (%d nodes, %s):\n", g->n,
           g->directed ? "directed" : "undirected");
    for (int i = 0; i < g->n; i++) {
        printf("  %d:", i);
        for (Edge *e = g->adj[i]; e; e = e->next)
            printf(" ->%d(%.1f)", e->dest, e->weight);
        printf("\n");
    }
}

Graph *graph_from_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { perror("graph_from_file"); return NULL; }

    int n;
    fscanf(f, "%d", &n);
    Graph *g = graph_create(n, 0);

    int src, dest;
    double w;
    while (fscanf(f, "%d %d %lf", &src, &dest, &w) == 3)
        graph_add_edge(g, src, dest, w);

    fclose(f);
    return g;
}
