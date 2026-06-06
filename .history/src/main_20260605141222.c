#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "graph.h"
#include "dijkstra.h"
#include "bfs.h"
#include "tests.h"

void demo_evacuation_small() {
    printf("\n========== EVACUATION DEMO (Small Graph) ==========\n");
    Graph *g = graph_create(5, 0);
    graph_add_edge(g, 0, 1, 1.0);
    graph_add_edge(g, 1, 4, 5.0);
    graph_add_edge(g, 0, 2, 2.0);
    graph_add_edge(g, 2, 3, 1.0);
    graph_add_edge(g, 3, 4, 1.0);
    graph_print(g);

    int source = 0, target = 4;
    int *prev = malloc(g->n * sizeof(int));
    double *dist = dijkstra(g, source, prev);

    printf("\nEvacuation from node %d to node %d:\n", source, target);
    printf("  Shortest distance = %.2f\n", dist[target]);
    printf("  Path: ");
    print_path(prev, source, target);
    printf("\n");

    printf("\nShortest distances from source %d:\n", source);
    for (int i = 0; i < g->n; i++) {
        printf("  Node %d: ", i);
        if (dist[i] == DBL_MAX) printf("unreachable\n");
        else printf("%.2f\n", dist[i]);
    }

    free(dist); free(prev); graph_free(g);
}

void demo_evacuation_from_file(const char *filename) {
    printf("\n========== EVACUATION DEMO (From File: %s) ==========\n", filename);
    Graph *g = graph_from_file(filename);
    if (!g) { printf("Could not load graph.\n"); return; }
    graph_print(g);

    int source = 0;
    int *prev = malloc(g->n * sizeof(int));
    double *dist = dijkstra(g, source, prev);

    printf("\nEvacuation distances from source %d:\n", source);
    for (int i = 0; i < g->n; i++) {
        if (dist[i] == DBL_MAX) printf("  Node %d: unreachable\n", i);
        else {
            printf("  Node %d: %.2f (path: ", i, dist[i]);
            print_path(prev, source, i);
            printf(")\n");
        }
    }

    free(dist); free(prev); graph_free(g);
}

int main(int argc, char *argv[]) {
    run_all_tests();
    demo_evacuation_small();
    if (argc > 1) demo_evacuation_from_file(argv[1]);
    else printf("\n(No graph file provided. Pass filename as argument.)\n");
    printf("\n========== PROGRAM FINISHED ==========\n");
    return 0;
}