#pragma once

#include "../../lib/lib.h"
#include <stdbool.h>

typedef struct graph graph_t;

graph_t *graph_init(int num_v);

graph_t *graph_init_file(char *filename);

int graph_V(graph_t *g);

int graph_E(graph_t *g);

bool graph_add_edge(graph_t *g, int v, int w);

bool graph_adj_iter_init(graph_t *g, int v);

bool graph_adj_iter_next(graph_t *g, int v, int *w);

void graph_print(graph_t *g);

void graph_free(graph_t *g);
