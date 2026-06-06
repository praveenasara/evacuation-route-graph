#include "dijkstra.h"
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double *dijkstra(Graph *g, int src, int *prev) {
    double *dist = malloc(g->n * sizeof(double));
    int *visited = calloc(g->n, sizeof(int));

    for (int i = 0; i < g->n; i++) {
        dist[i] = DBL_MAX;
        if (prev) prev[i] = -1;
    }
    dist[src] = 0.0;

    PriorityQueue *pq = pq_create(g->n);
    pq_push(pq, src, 0.0);

    while (!pq_empty(pq)) {
        PQNode cur = pq_pop(pq);
        int u = cur.node;
        if (visited[u]) continue;
        visited[u] = 1;

        for (Edge *e = g->adj[u]; e; e = e->next) {
            int v = e->dest;
            double nd = dist[u] + e->weight;
            if (nd < dist[v]) {
                dist[v] = nd;
                if (prev) prev[v] = u;
                pq_push(pq, v, nd);
            }
        }
    }

    pq_free(pq);
    free(visited);
    return dist;
}

void print_path(int *prev, int src, int dest) {
    if (dest == src) { printf("%d", src); return; }
    if (prev[dest] == -1) { printf("No path"); return; }
    print_path(prev, src, prev[dest]);
    printf(" -> %d", dest);
}