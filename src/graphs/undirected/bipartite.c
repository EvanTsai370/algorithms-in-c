 // 判断无向图是否为二分图，如果不是，则无向图有一个长度为奇数的环，
 // 这里使用递归的dfs判断，bipartite_x使用非递归的bfs判断

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bipartite.h"
#include "../../data_structures/stack/stack.h"
#include "graph.h"

static void dfs(bipartite_t *b, int v);
static bool check(bipartite_t *b);

typedef struct bipartite {
  graph_t *g;
  bool *marked;
  int *edge_to;
  bool *color;
  bool is_bipartite;
  my_stack_t *cycle;
} bipartite_t;

bipartite_t *bipartite_init(graph_t *g) {
  bipartite_t *b = malloc(sizeof(bipartite_t));
  if (!b) {
    perror("Failed to malloc bipartite\n");
    exit(EXIT_FAILURE);
  }

  b->g = g;
  b->is_bipartite = true;
  b->cycle = NULL;
  b->marked = malloc(sizeof(bool) * graph_V(g));
  if (!b->marked) {
    perror("Failed to malloc marked array\n");
    exit(EXIT_FAILURE);
  }
  b->edge_to = malloc(sizeof(int) * graph_V(g));
  if (!b->edge_to) {
    perror("Failed to malloc edge_to array\n");
    exit(EXIT_FAILURE);
  }
  b->color = malloc(sizeof(bool) * graph_V(g));
  if (!b->color) {
    perror("Failed to malloc color array\n");
    exit(EXIT_FAILURE);
  }

  // Initialize array
  for (int i = 0; i < graph_V(g); i++) {
    b->marked[i] = false;
    b->edge_to[i] = -1;
    b->color[i] = false;
  }

  for (int i = 0; i < graph_V(g); i++) {
    if (!b->marked[i]) {
      dfs(b, i);
    }
  }

  assert(check(b));

  return b;
}

static void dfs(bipartite_t *b, int v) {
  b->marked[v] = true;

  graph_adj_iter_init(b->g, v);
  while (graph_adj_iter_has_next(b->g, v)) {
    // if an odd cycle is found
    if (b->cycle) {
      return;
    }

    int w; 
    graph_adj_iter_next(b->g, v, &w);
    if (!b->marked[w]) {
      b->edge_to[w] = v;
      b->color[w] = !b->color[v];
      dfs(b, w);
    } else if (b->color[w] == b->color[v]) {
      b->is_bipartite = false;
      b->cycle = stack_init(sizeof(int));
      stack_push(b->cycle, &w);
      for (int x = v; x != w; x = b->edge_to[x]) {
        stack_push(b->cycle, &x);
      }
      stack_push(b->cycle, &w);
    }
  }
}

static bool check(bipartite_t *b) {
  if (b->is_bipartite) {
    for (int v = 0; v < graph_V(b->g); v++) {
      graph_adj_iter_init(b->g, v);
      while (graph_adj_iter_has_next(b->g, v)) {
        int w;
        graph_adj_iter_next(b->g, v, &w);
        if (b->color[v] == b->color[w]) {
          printf("edge %d-%d with %d and %d in same side of bipartition\n", v, w, v, w);
          return false;
        } 
      }
    }
  } else {
    // 检查环
    int first = -1, last = -1;
    b_odd_cycle_iter_init(b);
    while (b_odd_cycle_iter_has_next(b)) {
      int v;
      b_odd_cycle_iter_next(b, &v);
      if (first == -1) {
        first = v;
      }
      last = v;
    }
    if (first != last) {
      printf("cycle begins with %d and ends with %d\n", first, last);
      return false;
    }
  }
  return true;
}

bool is_bipartite(bipartite_t *b) {
  return b->is_bipartite;
}

bool bipartite_color(bipartite_t *b, int v) {
  return b->color[v];
}

bool b_odd_cycle_iter_init(bipartite_t *b) {
  if (b->is_bipartite) {
    return false;
  }
  stack_iter_init(b->cycle);
  return true;
}

bool b_odd_cycle_iter_has_next(bipartite_t *b) {
  return stack_iter_has_next(b->cycle);
}

bool b_odd_cycle_iter_next(bipartite_t *b, int *v) {
  stack_iter_next(b->cycle, v);
  return true;
}

void bipartite_free(bipartite_t *b) {
  free(b->marked);
  free(b->edge_to);
  free(b->color);
  if (b->cycle) {
    stack_free(b->cycle);
  }
}
