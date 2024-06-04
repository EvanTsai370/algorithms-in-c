#include <stdio.h>
#include "connected_components.h"
#include "graph.h"

void dfs(cc_t *cc, int v);

typedef struct cc {
  graph_t *g;
  bool *marked;
  int *id; // 连通分量id
  int *size; // 连通分量的顶点个数
  int count; // 连通分量个数
} cc_t;

cc_t *cc_init(graph_t *g) {
  cc_t *cc = malloc(sizeof(cc_t));
  if (!cc) {
    perror("Failed to malloc cc\n");
    exit(EXIT_FAILURE);
  }

  cc->g = g;
  cc->marked = malloc(sizeof(bool) * graph_V(g));
  if (!cc->marked) {
    perror("Failed to malloc marked array\n");
    exit(EXIT_FAILURE);
  }
  cc->id = malloc(sizeof(int) * graph_V(g));
  if (!cc->id) {
    perror("Failed to malloc id array\n");
    exit(EXIT_FAILURE);
  }
  cc->size = malloc(sizeof(int) * graph_V(g));
  if (!cc->size) {
    perror("Failed to malloc size array\n");
    exit(EXIT_FAILURE);
  }

  // Initialize array
  for (int i = 0; i < graph_V(g); i++) {
    cc->marked[i] = false;
    cc->size[i] = 0;
  }
  cc->count = 0;

  for (int v = 0; v < graph_V(g); v++) {
    if (!cc->marked[v]) {
      dfs(cc, v);
      cc->count++;
    }
  }

  return cc;
}

void dfs(cc_t *cc, int v) {
  cc->marked[v] = true;
  cc->id[v] = cc->count;
  cc->size[cc->count]++;

  graph_adj_iter_init(cc->g, v);
  while (graph_adj_iter_has_next(cc->g, v)) {
    int w;
    graph_adj_iter_next(cc->g, v, &w);
    if (!cc->marked[w]) {
      dfs(cc, w);
    }
  }
}

int cc_count(cc_t *cc) {
  return cc->count;
}

int cc_id(cc_t *cc, int v) {
  if (v < 0 || v >= graph_V(cc->g)) {
    return -1;
  }
  return cc->id[v];
}

int cc_size(cc_t *cc, int v) {
  if (v < 0 || v >= graph_V(cc->g)) {
    return -1;
  }
  return cc->size[cc->id[v]];
}

bool cc_connected(cc_t *cc, int v, int w) {
  if (v < 0 || v >= graph_V(cc->g)) {
    return -1;
  }
  if (w < 0 || w >= graph_V(cc->g)) {
    return -1;
  }
  return cc->id[v] == cc->id[w];
}

void cc_free(cc_t *cc) {
  free(cc->marked);
  free(cc->id);
  free(cc->size);
  free(cc);
}
