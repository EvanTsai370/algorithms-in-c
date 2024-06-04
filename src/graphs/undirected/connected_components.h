#pragma once

#include <stdbool.h>

#include "graph.h"

typedef struct cc cc_t;

cc_t *cc_init(graph_t *g);

int cc_count(cc_t *cc);

int cc_id(cc_t *cc, int v);

int cc_size(cc_t *cc, int v);

bool cc_connected(cc_t *cc, int n, int w);

void cc_free(cc_t *cc);
