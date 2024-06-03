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
  int num_v, num_e;
  int ret = fscanf(fp, "%d", &num_v);
  if (ret != 1) {
    perror("Failed to read number of vertices from input file!\n");
    exit(EXIT_FAILURE);
  }
  ret = fscanf(fp, "%d", &num_e);
  if (ret != 1) {
    perror("Failed to read number of edges from input file!\n");
    exit(EXIT_FAILURE);
  }

  if (num_v <= 0 || num_e <= 0) {
    return NULL;
  }

  // Initialize the graph
  graph_t *g = graph_init(num_v);

  // Fill the graph
  int v, w;
  for (int i = 0; i < num_e; i++) {
    ret = fscanf(fp, "%d %d", &v, &w);
    if (ret != 2) {
      perror("Failed to read edge from input file!\n");
      exit(EXIT_FAILURE);
    }
    if (!graph_add_edge(g, v, w)) {
      perror("Failed to add edge!\n");
      exit(EXIT_FAILURE);
    }
  }
  return g;
}

int graph_V(graph_t *g) { return g->V; }

int graph_E(graph_t *g) { return g->E; }

bool graph_add_edge(graph_t *g, int v, int w) {
  if (v < 0 || w < 0 || v > g->V - 1 || w > g->V - 1) {
    return false;
  }

  bag_add(g->adj[v], &w);
  bag_add(g->adj[w], &v);

  g->E++;
  return true;
}

bool graph_adj_iter_init(graph_t *g, int v) {
  if (v < 0 || v > g->V - 1) {
    return false;
  }
  return bag_iter_init(g->adj[v]);
}

bool graph_adj_iter_has_next(graph_t *g, int v) {
  if (v < 0 || v > g->V - 1) {
    return false;
  }
  return bag_iter_has_next(g->adj[v]);
}

bool graph_adj_iter_next(graph_t *g, int v, int *w) {
  if (v < 0 || v > g->V - 1) {
    return false;
  }
  bag_iter_next(g->adj[v], w);
  return true;
}

void graph_print(graph_t *g) {
  printf("%d vertices, %d edges\n", g->V, g->E);
  for (int v = 0; v < g->V; v++) {
    printf("%d: ", v);
    graph_adj_iter_init(g, v);
    while (graph_adj_iter_has_next(g, v)) {
      int w;
      graph_adj_iter_next(g, v, &w);
      printf("%d ", w);
    }
    printf("\n");
  }
  return;
}

void graph_free(graph_t *g) {
  for (int i = 0; i < g->V; i++) {
    // Free each bag
    bag_free(g->adj[i]);
  }

  // free the list of bags
  free(g->adj);

  // free the graph
  free(g);

  return;
}
