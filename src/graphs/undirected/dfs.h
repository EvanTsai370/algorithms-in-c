#pragma once

#include <stdbool.h>
#include "graph.h"

typedef struct depth_first_search depth_first_search_t;

depth_first_search_t *depth_first_search_init(graph_t *g, int s);

bool depth_first_search_marked(depth_first_search_t *d, int v);

int depth_first_search_count(depth_first_search_t *d);

void depth_first_search_free(depth_first_search_t *d);
