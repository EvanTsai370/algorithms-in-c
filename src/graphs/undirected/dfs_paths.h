#pragma once

#include <stdbool.h>
#include "graph.h"

typedef struct dfs_paths dfs_paths_t;

dfs_paths_t *dfs_paths_init(graph_t *g, int s);

bool has_dfs_path_to(dfs_paths_t *d, int v);

bool dfs_path_iter_init(dfs_paths_t *d, int v);

bool dfs_path_iter_has_next(dfs_paths_t *d, int v);

bool dfs_path_iter_next(dfs_paths_t *d, int v, int *w);

void dfs_paths_free(dfs_paths_t *d);
