#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node {
  void *item;
  struct node *next;
} node_t;

typedef struct queue {
  size_t item_size;  // item占用多少个字节
  unsigned int n;    // item的数量
  node_t *first;     // 指向第一个node的指针
  node_t *last;      // 指向最后一个node的指针
  node_t *curr_iter; // 迭代器指针
} queue_t;

queue_t *queue_init(size_t item_size) {
  queue_t *q = malloc(sizeof(queue_t));
  if (!q) {
    perror("Failed to malloc queue\n");
    exit(EXIT_FAILURE);
  }

  q->item_size = item_size;
  q->n = 0;
  q->first = NULL;
  q->last = NULL;
  q->curr_iter = NULL;

  return q;
}

void queue_enqueue(queue_t *q, void *item) {
  node_t *new_node = malloc(sizeof(node_t));
  if (!new_node) {
    perror("Failed to malloc node\n");
    exit(EXIT_FAILURE);
  }

  // 如果不设置为空，可能有脏数据，导致misaligned address
  new_node->next = NULL;
  new_node->item = malloc(q->item_size);
  if (!new_node->item) {
    perror("Failed to malloc new item\n");
    exit(EXIT_FAILURE);
  }
  memcpy(new_node->item, item, q->item_size);

  if (q->n == 0) {
    q->first = new_node;
    q->last = new_node;
  } else {
    q->last->next = new_node;
    q->last = new_node;
  }

  q->n++;
}

bool queue_dequeue(queue_t *q, void *item) {
  if (queue_is_empty(q)) {
    return false;
  }
  memcpy(item, q->first->item, q->item_size);

  node_t *old_first = q->first;

  q->first = q->first->next;
  if (!q->first) {
    q->last = NULL;
  }

  free(old_first->item);
  free(old_first);

  q->n--;

  return true;
}

bool queue_is_empty(queue_t *q) { 
  return (q->n == 0); 
}

unsigned int queue_size(queue_t *q) { 
  return q->n; 
}

void queue_free(queue_t *q) {
  node_t *n = q->first;
  node_t *old_n;

  while (n) {
    old_n = n;
    n = n->next;

    free(old_n->item);
    free(old_n);
  }

  free(q);
}

void queue_iter_init(queue_t *q) {
  if (queue_is_empty(q)) {
    return;
  }
  q->curr_iter = q->first;
}

bool queue_iter_has_next(queue_t *q) {
  if (queue_is_empty(q)) {
    return false;
  }
  return q->curr_iter != NULL;
}

void queue_iter_next(queue_t *q, void *item) {
  memcpy(item, q->curr_iter->item, q->item_size);
  q->curr_iter = q->curr_iter->next;
}
