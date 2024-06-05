#pragma once

#include <stdbool.h>
#include "graph.h"

typedef struct bipartite bipartite_t;

bipartite_t *bipartite_init(graph_t *g);

bool is_bipartite(bipartite_t *b);

bool bipartite_color(bipartite_t *b, int v);

bool b_odd_cycle_iter_init(bipartite_t *b);

bool b_odd_cycle_iter_has_next(bipartite_t *b);

bool b_odd_cycle_iter_next(bipartite_t *b, int *v);

void bipartite_free(bipartite_t *b);
