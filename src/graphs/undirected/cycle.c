#include <stdio.h>
#include "cycle.h"
#include "../../data_structures/stack/stack.h"
#include "graph.h"

static void dfs(cycle_t *c, int from, int v);

typedef struct cycle {
  graph_t *g;
  int *edge_to;
  bool *marked;
  my_stack_t *cycle;
} cycle_t;

cycle_t *cycle_init(graph_t *g) {
  if (!g) {
    return NULL;
  }
  cycle_t *c = malloc(sizeof(cycle_t));
  if (!c) {
    perror("Failed to malloc cycle\n");
    exit(EXIT_FAILURE);
  }
  c->g = g;

  c->edge_to = malloc(sizeof(int) * graph_V(g));
  if (!c->edge_to) {
    perror("Failed to malloc edge_to array\n");
    exit(EXIT_FAILURE);
  }
  c->marked = malloc(sizeof(bool) * graph_V(g));
  if (!c->marked) {
    perror("Failed to malloc marked array\n");
    exit(EXIT_FAILURE);
  }

  // Initialize array
  for (int i = 0; i < graph_V(g); i++) {
    c->edge_to[i] = -1;
    c->marked[i] = false;
  }
  c->cycle = NULL;

  for (int v = 0; v < graph_V(g); v++) {
    if (!c->marked[v]) {
      dfs(c, -1, v);
    }
  }

  return c;
}

static void dfs(cycle_t *c, int from, int v) {
  c->marked[v] = true;

  graph_adj_iter_init(c->g, v);
  while (graph_adj_iter_has_next(c->g, v)) {
    // if we've already found a cycle
    if (c->cycle) {
      return;
    }

    int w;
    graph_adj_iter_next(c->g, v, &w);
    if (!c->marked[w]) {
      c->edge_to[w] = v;
      dfs(c, v, w);
    } else if (from != w) {
      c->cycle = stack_init(sizeof(int));
      int x;
      for (x = v; x != w; x = c->edge_to[x]) {
        stack_push(c->cycle, &x);
      }
      stack_push(c->cycle, &w);
      stack_push(c->cycle, &v);
    }
  }
}

bool has_cycle(cycle_t *c) {
  return (c->cycle != NULL);
}

bool cycle_iter_init(cycle_t *c) {
  if (!c->cycle) {
    return false;
  }
  stack_iter_init(c->cycle);
  return true;
}

bool cycle_iter_has_next(cycle_t *c) {
  return stack_iter_has_next(c->cycle);
}

bool cycle_iter_next(cycle_t *c, int *v) {
  stack_iter_next(c->cycle, v);
  return true;
}

void cycle_free(cycle_t *c) {
  free(c->marked);
  free(c->edge_to);
  if (c->cycle) {
    stack_free(c->cycle);
  }
  free(c);
}
