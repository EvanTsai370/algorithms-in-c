#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bag.h"

typedef struct node {
  void *item;
  struct node *next;
} node_t;

typedef struct bag {
  size_t item_size;  // item占用几个字节
  unsigned int n;    // 有多少个item
  node_t *first;     // 指向第一个节点的指针
  node_t *curr_iter; // 指向当前节点的指针
} bag_t;

bag_t *bag_init(size_t item_size) {
  bag_t *b = malloc(sizeof(bag_t));
  if (!b) {
    perror("Failed to malloc bag\n");
    exit(EXIT_FAILURE);
  }

  b->first = NULL;
  b->curr_iter = NULL;
  b->n = 0;
  b->item_size = item_size;

  return b;
}

void bag_add(bag_t *b, void *item) {
  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) {
    perror("Failed to malloc node\n");
    exit(EXIT_FAILURE);
  }
  new_node->item = malloc(b->item_size);
  if (!new_node->item) {
    perror("Failed to malloc new item");
    exit(EXIT_FAILURE);
  }
  memcpy(new_node->item, item, b->item_size);

  // 添加到链表的首部
  new_node->next = b->first;
  b->first = new_node;
  b->n++;
}

bool bag_is_empty(bag_t *b) { return (b->n == 0); }

unsigned int bag_size(bag_t *b) { return b->n; }

bool bag_iter_init(bag_t *b) {
  if (bag_is_empty(b)) {
    return false;
  }
  b->curr_iter = b->first;
  return true;
}

bool bag_iter_has_next(bag_t *b) {
  if (bag_is_empty(b)) {
    return false;
  }
  return b->curr_iter != NULL;
}

void bag_iter_next(bag_t *b, void *item) {
  memcpy(item, b->curr_iter->item, b->item_size);
  b->curr_iter = b->curr_iter->next;
}

// 私有方法，用于测试
bool bag_remove(bag_t *b, void *item) {
  if (bag_is_empty(b)) {
    return false;
  }
  memcpy(item, b->first->item, b->item_size);

  node_t *old_first = b->first;
  b->first = b->first->next;

  free(old_first->item);
  free(old_first);

  b->n--;
  return true;
}

void bag_free(bag_t *b) {
  node_t *n = b->first;
  node_t *old_n;

  while (n) {
    old_n = n;
    n = n->next;
    free(old_n->item);
    free(old_n);
  }
  free(b);
}
