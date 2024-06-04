#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bfs_paths.h"
#include "graph.h"
#include "../../data_structures/stack/stack.h"
#include "../../data_structures/queue/queue.h"

void bfs(bfs_paths_t *b, int v);

typedef struct bfs_paths {
  graph_t *g;
  bool *marked;
  int *edge_to;
  double *dist_to;
  my_stack_t **stacks;
  int s;
} bfs_paths_t;

bfs_paths_t *bfs_paths_init(graph_t *g, int s) {
  if (!g) {
    return NULL;
  }
  if (s < 0 || s >= graph_V(g)) {
    return NULL;
  }

  bfs_paths_t *b = malloc(sizeof(bfs_paths_t));
  if (!b) {
    perror("Failed to malloc bfs paths\n");
    exit(EXIT_FAILURE);
  }

  b->g = g;
  b->s = s;

  b->marked = malloc(sizeof(bool) * graph_V(g));
  if (!b->marked) {
    free(b);
    perror("Failed to malloc marked array\n");
    exit(EXIT_FAILURE);
  }
  b->edge_to = malloc(sizeof(int) * graph_V(g));
  if (!b->edge_to) {
    free(b);
    perror("Failed to malloc edge_to array\n");
    exit(EXIT_FAILURE);
  }
  b->dist_to = malloc(sizeof(double) * graph_V(g));
  if (!b->dist_to) {
    free(b);
    perror("Failed to malloc dist_to array\n");
    exit(EXIT_FAILURE);
  }
  b->stacks = malloc(sizeof(my_stack_t *) * graph_V(g));
  if (!b->stacks) {
    perror("Failed to malloc stacks\n");
    exit(EXIT_FAILURE);
  }

  // Initialize arrays
  for (int i = 0; i < graph_V(g); i++) {
    b->marked[i] = false;
    b->dist_to[i] = INFINITY;
    b->edge_to[i] = -1;
    b->stacks[i] = NULL;
  }

  bfs(b, s);

  return b;
}

void bfs(bfs_paths_t *b, int s) {
  b->dist_to[s] = 0;
  b->marked[s] = true;

  queue_t *q = queue_init(sizeof(int));
  queue_enqueue(q, &s);
  while (!queue_is_empty(q)) {
    int v;
    queue_dequeue(q, &v);
    graph_adj_iter_init(b->g, v);
    while (graph_adj_iter_has_next(b->g, v)) {
      int w;
      graph_adj_iter_next(b->g, v, &w);
      if (!b->marked[w]) {
        b->marked[w] = true;
        b->edge_to[w] = v;
        b->dist_to[w] = b->dist_to[v] + 1;
        queue_enqueue(q, &w);
      }
    }
  }

  free(q);
}

bool has_bfs_path_to(bfs_paths_t *b, int v) {
  if (v < 0 || v >= graph_V(b->g)) {
    return false;
  }
  return b->marked[v];
}

bool bfs_path_iter_init(bfs_paths_t *b, int v) {
  if (v < 0 || v >= graph_V(b->g)) {
    return false;
  }

  if (b->stacks[v]) {
    free(b->stacks[v]);
  }
  b->stacks[v] = stack_init(sizeof(int));
  int w;
  for (w = v; w != b->s; w = b->edge_to[w]) {
    stack_push(b->stacks[v], &w);
  }
  stack_push(b->stacks[v], &w);

  stack_iter_init(b->stacks[v]);
  return true;
}

bool bfs_path_iter_has_next(bfs_paths_t *b, int v) {
  if (v < 0 || v >= graph_V(b->g)) {
    return false;
  }
  return stack_iter_has_next(b->stacks[v]);
}

bool bfs_path_iter_next(bfs_paths_t *b, int v, int *w) {
  if (v < 0 || v >= graph_V(b->g)) {
    return false;
  }
  stack_iter_next(b->stacks[v], w);
  return true;
}

double bfs_dist_to(bfs_paths_t *b, int v) {
  if (v < 0 || v >= graph_V(b->g)) {
    return -1;
  }
  return b->dist_to[v];
}

void bfs_paths_free(bfs_paths_t *b) {
  for (int i = 0; i < graph_V(b->g); i++) {
    if (b->stacks[i]) {
      free(b->stacks[i]);
    }
  }
  free(b->stacks);
  free(b->marked);
  free(b->edge_to);
  free(b->dist_to);
  free(b);
}
