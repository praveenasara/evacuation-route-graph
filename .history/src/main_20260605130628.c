/**
 * main.c - Entry point for the evacuation routing project.
 * 
 * This program demonstrates:
 *   - Unit tests for graph data structure, Dijkstra's algorithm,
 *     BFS, and the evacuation-specific problem.
 *   - An example evacuation route calculation on a small test graph.
 *   - Optional loading of a larger graph from a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "graph.h"
#include "dijkstra.h"
#include "bfs.h"
#include "tests.h"

/**
 * Demonstrate the evacuation problem on a small predefined graph.
 * Computes shortest paths from a source (e.g., an incident location)
 * to all other nodes (e.g., evacuation exits).
 */
void demo_evacuation_small() {
    printf("\n========== EVACUATION DEMO (Small Graph) ==========\n");
    
    // Create a small undirected graph representing a building layout.
    // Nodes: 0 = entry/incident, 4 = exit, others = intermediate rooms.
    Graph *g = graph_create(5, 0);  // undirected
    graph_add_edge(g, 0, 1, 1.0);
    graph_add_edge(g, 1, 4, 5.0);   // long corridor
    graph_add_edge(g, 0, 2, 2.0);
    graph_add_edge(g, 2, 3, 1.0);
    graph_add_edge(g, 3, 4, 1.0);   // shortcut
    
    graph_print(g);
    
    int source = 0;
    int target = 4;
    int *prev = malloc(g->n * sizeof(int));
    double *dist = dijkstra(g, source, prev);
    
    printf("\nEvacuation from node %d to node %d:\n", source, target);
    printf("  Shortest distance = %.2f\n", dist[target]);
    printf("  Path: ");
    print_path(prev, source, target);
    printf("\n");
    
    // Show distances to all nodes (useful for planning).
    printf("\nShortest distances from source %d:\n", source);
    for (int i = 0; i < g->n; i++) {
        printf("  Node %d: ", i);
        if (dist[i] == DBL_MAX)
            printf("unreachable\n");
        else
            printf("%.2f\n", dist[i]);
    }
    
    free(dist);
    free(prev);
    graph_free(g);
}

/**
 * Demonstration using a graph loaded from a file.
 * The file format is:
 *   first line: number_of_nodes
 *   then lines: src dest weight
 * (undirected graph assumed)
 *
 * If the file does not exist, this function prints a message and skips.
 */
void demo_evacuation_from_file(const char *filename) {
    printf("\n========== EVACUATION DEMO (From File: %s) ==========\n", filename);
    
    Graph *g = graph_from_file(filename);
    if (!g) {
        printf("Could not load graph from '%s'. Skipping file demo.\n", filename);
        return;
    }
    
    graph_print(g);
    
    // Example: find shortest paths from node 0 (the incident location)
    int source = 0;
    int *prev = malloc(g->n * sizeof(int));
    double *dist = dijkstra(g, source, prev);
    
    printf("\nEvacuation distances from source node %d:\n", source);
    for (int i = 0; i < g->n; i++) {
        if (dist[i] == DBL_MAX)
            printf("  Node %d: unreachable\n", i);
        else {
            printf("  Node %d: %.2f  (path: ", i, dist[i]);
            print_path(prev, source, i);
            printf(")\n");
        }
    }
    
    free(dist);
    free(prev);
    graph_free(g);
}

int main(int argc, char *argv[]) {
    // Part 1 & 2: Run all unit tests (graph, Dijkstra, BFS, evacuation logic)
    run_all_tests();
    
    // Demonstrate the specific problem (evacuation) on a small, built‑in graph.
    demo_evacuation_small();
    
    // Optionally, if a graph file is provided as a command‑line argument, load and evaluate it.
    if (argc > 1) {
        demo_evacuation_from_file(argv[1]);
    } else {
        printf("\n(No graph file provided. To test a custom graph, pass the filename as an argument.)\n");
    }
    
    printf("\n========== PROGRAM FINISHED ==========\n");
    return 0;
}