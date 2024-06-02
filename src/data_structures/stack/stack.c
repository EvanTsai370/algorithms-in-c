#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct node {
  void *item;
  struct node *next;
} node_t;

typedef struct stack {
  size_t item_size;  // item占用的字节数
  unsigned int n;    // item的数量
  node_t *first;     // 指向第一个node的指针
  node_t *curr_iter; // 迭代器指针
} my_stack_t;

my_stack_t *stack_init(size_t item_size) {
  my_stack_t *s = malloc(sizeof(my_stack_t));

  s->item_size = item_size;
  s->n = 0;
  s->first = NULL;
  s->curr_iter = NULL;

  return s;
}

void stack_push(my_stack_t *s, void *item) {
  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) {
    perror("Failed to malloc node\n");
    exit(EXIT_FAILURE);
  }
  new_node->item = malloc(s->item_size);
  if (!new_node->item) {
    printf("Failed to malloc new item\n");
    exit(EXIT_FAILURE);
  }
  memcpy(new_node->item, item, s->item_size);

  // 添加到链表的首部
  new_node->next = s->first;
  s->first = new_node;
  s->n++;
}

bool stack_pop(my_stack_t *s, void *item) {
  if (stack_is_empty(s)) {
    return false;
  }
  memcpy(item, s->first->item, s->item_size);

  node_t *old_first = s->first;

  s->first = s->first->next;

  free(old_first->item);
  free(old_first);

  s->n--;
  return true;
}

bool stack_is_empty(my_stack_t *s) { return (s->n == 0); }

unsigned int stack_size(my_stack_t *s) { return s->n; }

void stack_free(my_stack_t *s) {
  node_t *n = s->first;
  node_t *old_n;

  while (n) {
    old_n = n;
    n = n->next;

    free(old_n->item);
    free(old_n);
  }

  free(s);
}

void stack_iter_init(my_stack_t *s) {
  if (stack_is_empty(s)) {
    return;
  }
  s->curr_iter = s->first;
}

bool stack_iter_has_next(my_stack_t *s) {
  if (stack_is_empty(s)) {
    return false;
  }
  return s->curr_iter != NULL;
}

void stack_iter_next(my_stack_t *s, void *item) {
  memcpy(item, s->curr_iter->item, s->item_size);
  s->curr_iter = s->curr_iter->next;
}
