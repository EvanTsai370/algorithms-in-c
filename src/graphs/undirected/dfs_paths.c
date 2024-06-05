#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "dfs_paths.h"
#include "../../data_structures/stack/stack.h"

static void dfs(dfs_paths_t *d, int v);

typedef struct dfs_paths {
  graph_t *g;
  int s;
  bool *marked;
  int *edge_to;
  my_stack_t **stacks;
} dfs_paths_t;

dfs_paths_t *dfs_paths_init(graph_t *g, int s) {
  if (!g) {
    return NULL;
  }
  if (s < 0 || s >= graph_V(g)) {
    return NULL;
  }

  dfs_paths_t *d = malloc(sizeof(dfs_paths_t));
  if (!d) {
    perror("Failed to malloc dfs paths\n");
    exit(EXIT_FAILURE);
  }

  d->g = g;
  d->s = s;

  d->marked = malloc(sizeof(bool) * graph_V(g));
  if (!d->marked) {
    perror("Failed to malloc marked array\n");
    exit(EXIT_FAILURE);
  }
  d->edge_to = malloc(sizeof(int) * graph_V(g));
  if (!d->edge_to) {
    perror("Failed to malloc edge_to array\n");
    exit(EXIT_FAILURE);
  }
  d->stacks = malloc(sizeof(my_stack_t *) * graph_V(g));
  if (!d->stacks) {
    perror("Failed to malloc stacks\n");
    exit(EXIT_FAILURE);
  }

  // Initialize arrays
  for (int i = 0; i < graph_V(d->g); i++) {
    d->marked[i] = false;
    d->edge_to[i] = -1;
    d->stacks[i] = NULL;
  }

  dfs(d, s);

  return d;
}

static void dfs(dfs_paths_t *d, int v) {
  if (v < 0 || v >= graph_V(d->g)) {
    return;
  }

  d->marked[v] = true;

  if (!graph_adj_iter_init(d->g, v)) {
    return;
  }
  int w;
  while (graph_adj_iter_has_next(d->g, v)) {
    graph_adj_iter_next(d->g, v, &w);
    if (!d->marked[w]) {
      d->edge_to[w] = v;
      dfs(d, w);
    }
  }
}

bool has_dfs_path_to(dfs_paths_t *d, int v) {
  if (v < 0 || v >= graph_V(d->g)) {
    return false;
  }
  return d->marked[v];
}

bool dfs_path_iter_init(dfs_paths_t *d, int v) {
  if (v < 0 || v >= graph_V(d->g)) {
    return false;
  }
  if (!d->marked[v]) {
    return false;
  }

  // Create a stack for the path to this vertex
  if (d->stacks[v]) {
    free(d->stacks[v]);
  }
  d->stacks[v] = stack_init(sizeof(int));

  // Trace the path back to the source, pushing each vertex onto the stack
  for (int w = v; w != d->s; w = d->edge_to[w]) {
    stack_push(d->stacks[v], &w);
  }
  stack_push(d->stacks[v], &d->s);

  // Initialize an iterator for the stack
  stack_iter_init(d->stacks[v]);

  return true;
}

bool dfs_path_iter_has_next(dfs_paths_t *d, int v) {
  if (v < 0 || v >= graph_V(d->g)) {
    return false;
  }
  return stack_iter_has_next(d->stacks[v]);
}

bool dfs_path_iter_next(dfs_paths_t *d, int v, int *w) {
  if (v < 0 || v >= graph_V(d->g)) {
    return false;
  }
  stack_iter_next(d->stacks[v], w);
  return true;
}

void dfs_paths_free(dfs_paths_t *d) {
  for (int i = 0; i < graph_V(d->g); i++) {
    if (d->stacks[i]) {
      free(d->stacks[i]);
    }
  }
  free(d->stacks);
  free(d->edge_to);
  free(d->marked);
  free(d);
}
