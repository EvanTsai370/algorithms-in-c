#include "../src/graphs/undirected/bipartite.h"
#include "unity/unity.h"

void setUp() {
}

void tearDown() {
}

void test_bipartite_true() {
  graph_t *g = graph_init(4);
  graph_add_edge(g, 0, 1);
  graph_add_edge(g, 0, 2);
  graph_add_edge(g, 1, 3);
  graph_add_edge(g, 2, 3);
  bipartite_t *b = bipartite_init(g);
  TEST_ASSERT_TRUE(is_bipartite(b));
  bipartite_free(b);
  graph_free(g);
}

void test_bipartite_false() {
  graph_t *g = graph_init(3);
  graph_add_edge(g, 0, 1);
  graph_add_edge(g, 0, 2);
  graph_add_edge(g, 1, 2);
  bipartite_t *b = bipartite_init(g);
  TEST_ASSERT_FALSE(is_bipartite(b));
  bipartite_free(b);
  graph_free(g);
}

void test_bipartite_color() {
  graph_t *g = graph_init(4);
  graph_add_edge(g, 0, 1);
  graph_add_edge(g, 0, 2);
  graph_add_edge(g, 1, 3);
  graph_add_edge(g, 2, 3);
  bipartite_t *b = bipartite_init(g);
  for (int v = 0; v < graph_V(g); v++) {
    graph_adj_iter_init(g, v);
    while (graph_adj_iter_has_next(g, v)) {
      int w;
      graph_adj_iter_next(g, v, &w);
      TEST_ASSERT_TRUE(bipartite_color(b, v) != bipartite_color(b, w));
    }
  }
  bipartite_free(b);
  graph_free(g);
}

void test_bipartite_cycle() {
  graph_t *g = graph_init(4);
  graph_add_edge(g, 0, 1);
  graph_add_edge(g, 0, 2);
  graph_add_edge(g, 1, 2);
  bipartite_t *b = bipartite_init(g);

  int first = -1, last = -1;
  b_odd_cycle_iter_init(b);
  while (b_odd_cycle_iter_has_next(b)) {
    int v;
    b_odd_cycle_iter_next(b, &v);
    if (first == -1) {
      first = v;
    }
    last = v;
    printf("%d ", v);
  }

  TEST_ASSERT_EQUAL(first, last);

  bipartite_free(b);
  graph_free(g);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_bipartite_true);
  RUN_TEST(test_bipartite_false);
  RUN_TEST(test_bipartite_color);
  RUN_TEST(test_bipartite_cycle);
  return UNITY_END();
}
