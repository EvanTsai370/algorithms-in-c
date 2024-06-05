// 使用非递归的bfs判断无向图是否为二分图

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bipartite_x.h"
#include "../../data_structures/stack/stack.h"
#include "../../data_structures/queue/queue.h"
#include "graph.h"

static const bool white = true;

static void bfs(bipartite_x_t *b, int s);
static bool check(bipartite_x_t *b);

typedef struct bipartite_x {
  graph_t *g;
  bool *marked;
  int *edge_to;
  bool *color;
  bool is_bipartite;
  queue_t *cycle;
} bipartite_x_t;

bipartite_x_t *bipartite_x_init(graph_t *g) {
  bipartite_x_t *b = malloc(sizeof(bipartite_x_t));
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
      bfs(b, i);
    }
  }

  assert(check(b));

  return b;
}

static void bfs(bipartite_x_t *b, int s) {
  queue_t *q = queue_init(sizeof(int));
  if (!q) {
    perror("Failed to malloc queue\n");
    exit(EXIT_FAILURE);
  }
  b->color[s] = white;
  b->marked[s] = true;
  queue_enqueue(q, &s);

  while (!queue_is_empty(q)) {
    int v;
    queue_dequeue(q, &v);
    
    graph_adj_iter_init(b->g, v);
    while (graph_adj_iter_has_next(b->g, v)) {
      int w;
      graph_adj_iter_next(b->g, v, &w);
      if (!b->marked[w]) {
        b->marked[w] = true;;
        b->color[w] = !b->color[v];
        b->edge_to[w] = v;
        queue_enqueue(q, &w);
      } else if (b->color[v] == b->color[w]) {
        b->is_bipartite = false;

        // w已被标记，v与w相邻，则w与v位于同一层或者w位于v上层
        // 由于v与w同色，则v与w位于同一层，distTo[v] == distTo[w]
        // 设x为v与w最近的公共祖先，Path(x-v).length == Path(x-w).length
        // cycle = Path(x-v) + Path(x-w) + Edge(v-w)，长度为奇数
        b->cycle = queue_init(sizeof(int));
        my_stack_t *stack = stack_init(sizeof(int));
        int x = v, y = w;
        while (x != y) {
          // stack记录v-x
          stack_push(stack, &x);
          // cycle记录w-x
          queue_enqueue(b->cycle, &y);
          x = b->edge_to[x];
          y = b->edge_to[y];
        }
        stack_push(stack, &x);

        while (!stack_is_empty(stack)) {
          int s;
          stack_pop(stack, &s);
          queue_enqueue(b->cycle, &s);
        }
        queue_enqueue(b->cycle, &w);
        return;
      }
    }
  }
}

static bool check(bipartite_x_t *b) {
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
    bx_odd_cycle_iter_init(b);
    while (bx_odd_cycle_iter_has_next(b)) {
      int v;
      bx_odd_cycle_iter_next(b, &v);
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

bool is_bipartite_x(bipartite_x_t *b) {
  return b->is_bipartite;
}

bool bipartite_x_color(bipartite_x_t *b, int v) {
  return b->color[v];
}

bool bx_odd_cycle_iter_init(bipartite_x_t *b) {
  if (b->is_bipartite) {
    return false;
  }
  queue_iter_init(b->cycle);
  return true;
}

bool bx_odd_cycle_iter_has_next(bipartite_x_t *b) {
  return queue_iter_has_next(b->cycle);
}

bool bx_odd_cycle_iter_next(bipartite_x_t *b, int *v) {
  queue_iter_next(b->cycle, v);
  return true;
}

void bipartite_x_free(bipartite_x_t *b) {
  free(b->marked);
  free(b->edge_to);
  free(b->color);
  if (b->cycle) {
    queue_free(b->cycle);
  }
}
