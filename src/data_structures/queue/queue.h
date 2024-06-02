#pragma once

#include "../../lib/lib.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct queue queue_t;

queue_t *queue_init(size_t item_size);

void queue_enqueue(queue_t *q, void *item);

bool queue_dequeue(queue_t *q, void *item);

bool queue_is_empty(queue_t *q);

unsigned int queue_size(queue_t *q);

void queue_free(queue_t *q);

void queue_iter_init(queue_t *q);

bool queue_iter_has_next(queue_t *q);

void queue_iter_next(queue_t *q, void *item);
