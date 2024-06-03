#include <stdio.h>
#include <string.h>
#include "dfs.h"
#include "graph.h"


void dfs(depth_first_search_t *d, int v);

typedef struct depth_first_search {
  graph_t *g;
  bool *marked;
  int count;
} depth_first_search_t;

depth_first_search_t *depth_first_search_init(graph_t *g, int s) {
  if (!g) {
    return NULL;
  }
  if (s < 0 || s >= graph_V(g)) {
    return NULL;
  }

  depth_first_search_t *d = malloc(sizeof(depth_first_search_t));
  if (!d) {
    perror("Failed to malloc dfs\n");
    exit(EXIT_FAILURE);
  }

  d->g = g;
  d->count = 0;

  d->marked = malloc(sizeof(bool) * graph_V(g));
  if (!d->marked) {
    free(d);
    perror("Failed to malloc marked array\n");
    exit(EXIT_FAILURE);
  }

  memset(d->marked, false, sizeof(bool) * graph_V(g));

  dfs(d, s);

  return d;
}

void dfs(depth_first_search_t *d, int v) {
  if (v < 0 || v >= graph_V(d->g)) {
    return;
  }

  d->marked[v] = true;
  d->count++;
  printf("%d ", v);

  if (!graph_adj_iter_init(d->g, v)) {
    return;
  }
  int w;
  while (graph_adj_iter_has_next(d->g, v)) {
    graph_adj_iter_next(d->g, v, &w);
    if (!d->marked[w]) {
      dfs(d, w);
    }
  }
}

bool depth_first_search_marked(depth_first_search_t *d, int v) { 
  if (v < 0 || v >= graph_V(d->g)) {
    return false;
  }
  return d->marked[v]; 
}

int depth_first_search_count(depth_first_search_t *d) { 
  return d->count; 
}

void depth_first_search_free(depth_first_search_t *d) {
  free(d->marked);
  free(d);
}
