#pragma once

#include <stdbool.h>

#include "graph.h"

typedef struct cycle cycle_t;

cycle_t *cycle_init(graph_t *g);

bool has_cycle(cycle_t *c);

bool cycle_iter_init(cycle_t *c);

bool cycle_iter_has_next(cycle_t *c);

bool cycle_iter_next(cycle_t *c, int *v);

void cycle_free(cycle_t *c);
