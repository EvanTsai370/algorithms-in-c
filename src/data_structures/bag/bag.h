#pragma once

#include "../../lib/lib.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct bag bag_t;

bag_t *bag_init(size_t item_size);

void bag_add(bag_t *b, void *item);

bool bag_is_empty(bag_t *b);

unsigned int bag_size(bag_t *b);

void bag_free(bag_t *b);

bool bag_iter_init(bag_t *b);

bool bag_iter_has_next(bag_t *b);

void bag_iter_next(bag_t *b, void *item);
