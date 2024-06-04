#include <stdio.h>
#include "cycle.h"
#include "../../data_structures/stack/stack.h"
#include "graph.h"

void dfs(cycle_t *c, int from, int v);

typedef struct cycle {
  graph_t *g;
  int *edge_to;
  bool *marked;
  my_stack_t *stack;
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
  c->stack = NULL;

  for (int v = 0; v < graph_V(g); v++) {
    if (!c->marked[v]) {
      dfs(c, -1, v);
    }
  }

  return c;
}

void dfs(cycle_t *c, int from, int v) {
  c->marked[v] = true;

  graph_adj_iter_init(c->g, v);
  while (graph_adj_iter_has_next(c->g, v)) {
    // if we've already found a cycle
    if (c->stack) {
      return;
    }

    int w;
    graph_adj_iter_next(c->g, v, &w);
    if (!c->marked[w]) {
      c->edge_to[w] = v;
      dfs(c, v, w);
    } else if (from != w) {
      c->stack = stack_init(sizeof(int));
      int x;
      for (x = v; x != w; x = c->edge_to[x]) {
        stack_push(c->stack, &x);
      }
      stack_push(c->stack, &w);
      stack_push(c->stack, &v);
    }
  }
}

bool has_cycle(cycle_t *c) {
  return (c->stack != NULL);
}

bool cycle_iter_init(cycle_t *c) {
  if (!c->stack) {
    return false;
  }
  stack_iter_init(c->stack);
  return true;
}

bool cycle_iter_has_next(cycle_t *c) {
  return stack_iter_has_next(c->stack);
}

bool cycle_iter_next(cycle_t *c, int *v) {
  stack_iter_next(c->stack, v);
  return true;
}

void cycle_free(cycle_t *c) {
  free(c->marked);
  free(c->edge_to);
  if (c->stack) {
    stack_free(c->stack);
  }
  free(c);
}
