#pragma once

#include <stdbool.h>
#include "graph.h"

typedef struct bipartite_x bipartite_x_t;

bipartite_x_t *bipartite_x_init(graph_t *g);

bool is_bipartite_x(bipartite_x_t *b);

bool bipartite_x_color(bipartite_x_t *b, int v);

bool bx_odd_cycle_iter_init(bipartite_x_t *b);

bool bx_odd_cycle_iter_has_next(bipartite_x_t *b);

bool bx_odd_cycle_iter_next(bipartite_x_t *b, int *v);

void bipartite_x_free(bipartite_x_t *b);
