#include "graph.h"
#include "../../data_structures/bag/bag.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
  int V;       // 顶点数量
  int E;       // 边数量
  bag_t **adj; // 领接表
} graph_t;

graph_t *graph_init(int num_v) {
  if (num_v <= 0) {
    return NULL;
  }

  graph_t *g = malloc(sizeof(graph_t));
  if (!g) {
    perror("Failed to malloc graph\n");
    exit(EXIT_FAILURE);
  }
  g->V = num_v;
  g->E = 0;
  g->adj = malloc(sizeof(bag_t *) * num_v);
  if (!g->adj) {
    perror("Failed to malloc adj\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < num_v; i++) {
    g->adj[i] = bag_init(sizeof(int));
  }

  return g;
}

// Creates a graph given an input file with the following format:
// num_vertices
// num_edges
// v1 w1
// v2 w2
// v3 w3
// ...
graph_t *graph_init_file(char *filename) {
  FILE *fp = fopen(filename, "r");

  // Read the size of the graph from the file
  return NULL;
}
