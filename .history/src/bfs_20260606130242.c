#include "bfs.h"
#include <stdlib.h>
#include <stdio.h>

int *bfs(Graph *g, int src, int *prev) {
    int *dist  = malloc(g->n * sizeof(int));
    int *queue = malloc(g->n * sizeof(int));

    for (int i = 0; i < g->n; i++) {
        dist[i] = -1;
        if (prev) prev[i] = -1;
    }
    dist[src] = 0;

    int head = 0, tail = 0;
    queue[tail++] = src;

    while (head < tail) {
        int u = queue[head++];
        for (Edge *e = g->adj[u]; e; e = e->next) {
            int v = e->dest;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                if (prev) prev[v] = u;
                queue[tail++] = v;
            }
        }
    }

    free(queue);
    return dist;
}