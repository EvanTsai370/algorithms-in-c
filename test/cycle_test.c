#include <stdbool.h>
#include <stdio.h>
#include "unity/unity.h"
#include "../src/graphs/undirected/cycle.h"

void setUp() {
}

void tearDown() {
}

// Tests

void test_undirected_cycle_true() {
  graph_t *g = graph_init(4);
  graph_add_edge(g, 0, 1);
  graph_add_edge(g, 1, 2);
  graph_add_edge(g, 2, 3);
  graph_add_edge(g, 0, 3);

  cycle_t *c = cycle_init(g);
  TEST_ASSERT_TRUE(has_cycle(c));

  // print cycle
  cycle_iter_init(c);
  while (cycle_iter_has_next(c)) {
    int v;
    cycle_iter_next(c, &v);
    printf("%d ", v);
  }
  printf("\n");

  cycle_free(c);
}

void test_undirected_cycle_false() {
  graph_t *g = graph_init(4);
  graph_add_edge(g, 0, 1);
  graph_add_edge(g, 1, 2);
  graph_add_edge(g, 2, 3);

  cycle_t *c = cycle_init(g);
  TEST_ASSERT_FALSE(has_cycle(c));
  cycle_free(c);
}

// Main
int main() {
  UNITY_BEGIN();
  RUN_TEST(test_undirected_cycle_true);
  RUN_TEST(test_undirected_cycle_false);
  return UNITY_END();
}
