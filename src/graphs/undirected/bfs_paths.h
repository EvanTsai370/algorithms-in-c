#pragma once

#include <stdbool.h>
#include "graph.h"

typedef struct bfs_paths bfs_paths_t;

bfs_paths_t *bfs_paths_init(graph_t *g, int s);

bool has_bfs_path_to(bfs_paths_t *b, int v);

bool bfs_path_iter_init(bfs_paths_t *b, int v);

bool bfs_path_iter_has_next(bfs_paths_t *b, int v);

bool bfs_path_iter_next(bfs_paths_t *b, int v, int *w);

double bfs_dist_to(bfs_paths_t *b, int v);

void bfs_paths_free(bfs_paths_t *b);
