#pragma once

#include "../../lib/lib.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct stack my_stack_t;

my_stack_t *stack_init(size_t item_size);

void stack_push(my_stack_t *s, void *item);

bool stack_pop(my_stack_t *s, void *item);

bool stack_is_empty(my_stack_t *s);

unsigned int stack_size(my_stack_t *s);

void stack_free(my_stack_t *s);

void stack_iter_init(my_stack_t *s);

bool stack_iter_has_next(my_stack_t *s);

void stack_iter_next(my_stack_t *s, void *item);
