#include "graph.h"
#include "dijkstra.h"
#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

static int passed = 0, failed = 0;

#define TEST(cond, name) \
    do { if (cond) { printf("  [PASS] %s\n", name); passed++; } \
         else      { printf("  [FAIL] %s\n", name); failed++; } } while(0)

void test_graph_creation() {
    printf("\n--- Graph Data Structure Tests ---\n");
    Graph *g = graph_create(5, 0);
    TEST(g != NULL,    "graph_create returns non-null");
    TEST(g->n == 5,    "graph has correct node count");
    TEST(!g->directed, "graph is undirected");
    graph_free(g);
}

void test_graph_edges() {
    Graph *g = graph_create(4, 0);
    graph_add_edge(g, 0, 1, 2.5);
    graph_add_edge(g, 1, 2, 1.0);
    graph_add_edge(g, 2, 3, 4.0);

    int found_01 = 0, found_10 = 0;
    for (Edge *e = g->adj[0]; e; e = e->next)
        if (e->dest == 1 && fabs(e->weight - 2.5) < 1e-9) found_01 = 1;
    for (Edge *e = g->adj[1]; e; e = e->next)
        if (e->dest == 0 && fabs(e->weight - 2.5) < 1e-9) found_10 = 1;

    TEST(found_01, "edge 0->1 exists");
    TEST(found_10, "reverse edge 1->0 exists (undirected)");
    graph_free(g);
}

void test_dijkstra() {
    printf("\n--- Dijkstra Algorithm Tests ---\n");

    Graph *g = graph_create(3, 0);
    graph_add_edge(g, 0, 1, 1.0);
    graph_add_edge(g, 1, 2, 2.0);
    graph_add_edge(g, 0, 2, 10.0);

    int *prev = malloc(3 * sizeof(int));
    double *dist = dijkstra(g, 0, prev);

    TEST(fabs(dist[0] - 0.0) < 1e-9, "Dijkstra: dist to source = 0");
    TEST(fabs(dist[1] - 1.0) < 1e-9, "Dijkstra: dist to node 1 = 1.0");
    TEST(fabs(dist[2] - 3.0) < 1e-9, "Dijkstra: dist to node 2 = 3.0 (via 1)");
    TEST(prev[2] == 1, "Dijkstra: path to 2 goes via 1");

    free(dist); free(prev);
    graph_free(g);

    Graph *g2 = graph_create(3, 0);
    graph_add_edge(g2, 0, 1, 5.0);
    int *prev2 = malloc(3 * sizeof(int));
    double *dist2 = dijkstra(g2, 0, prev2);
    TEST(dist2[2] == DBL_MAX, "Dijkstra: unreachable node = INF");
    free(dist2); free(prev2);
    graph_free(g2);
}

void test_bfs() {
    printf("\n--- BFS Tests ---\n");

    Graph *g = graph_create(4, 0);
    graph_add_edge(g, 0, 1, 1.0);
    graph_add_edge(g, 0, 2, 1.0);
    graph_add_edge(g, 2, 3, 1.0);

    int *prev = malloc(4 * sizeof(int));
    int *dist = bfs(g, 0, prev);

    TEST(dist[0] == 0, "BFS: dist to source = 0");
    TEST(dist[1] == 1, "BFS: dist to node 1 = 1 hop");
    TEST(dist[2] == 1, "BFS: dist to node 2 = 1 hop");
    TEST(dist[3] == 2, "BFS: dist to node 3 = 2 hops");

    free(dist); free(prev);
    graph_free(g);
}

void test_evacuation() {
    printf("\n--- Evacuation Problem Tests ---\n");

    Graph *g = graph_create(5, 0);
    graph_add_edge(g, 0, 1, 1.0);
    graph_add_edge(g, 1, 4, 5.0);
    graph_add_edge(g, 0, 2, 2.0);
    graph_add_edge(g, 2, 3, 1.0);
    graph_add_edge(g, 3, 4, 1.0);

    int *prev = malloc(5 * sizeof(int));
    double *dist = dijkstra(g, 0, prev);

    TEST(fabs(dist[4] - 4.0) < 1e-9,
         "Evacuation: shortest route cost = 4.0");
    TEST(prev[4] == 3 && prev[3] == 2 && prev[2] == 0,
         "Evacuation: path is 0->2->3->4");

    printf("  Evacuation path: ");
    print_path(prev, 0, 4);
    printf(" (cost: %.1f)\n", dist[4]);

    free(dist); free(prev);
    graph_free(g);
}

void run_all_tests() {
    printf("========== UNIT TESTS ==========\n");
    test_graph_creation();
    test_graph_edges();
    test_dijkstra();
    test_bfs();
    test_evacuation();
    printf("\n================================\n");
    printf("Results: %d passed, %d failed\n", passed, failed);
    printf("================================\n");
}