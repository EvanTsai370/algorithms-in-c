#include "unity/unity.h"
#include "../src/graphs/undirected/dfs.h"
#include "unity/unity_internals.h"

#define NUM_V 6
#define NUM_E 8

static const int connections[NUM_E][2] = {{0, 5}, {2, 4}, {2, 3}, {1, 2}, \
                                          {0, 1}, {3, 4}, {3, 5}, {0, 2}};

graph_t *g;
depth_first_search_t *d;

void setUp() {
  g = graph_init(NUM_V);
  for (int i = 0; i < NUM_E; i++) {
    TEST_ASSERT_TRUE(graph_add_edge(g, connections[i][0], connections[i][1]));
  }
  d = depth_first_search_init(g, 0);
}

void tearDown() {
  graph_free(g);
  depth_first_search_free(d);
}

void test_depth_first_search_out_of_bound() {
  TEST_ASSERT_NULL(depth_first_search_init(g, -1));
  TEST_ASSERT_NULL(depth_first_search_init(g, NUM_V));
}

void test_depth_first_search_marked() {
  for (int i = 0; i < NUM_V; i++) {
    TEST_ASSERT_TRUE(depth_first_search_marked(d, i));
  }
  TEST_ASSERT_FALSE(depth_first_search_marked(d, -1));
  TEST_ASSERT_FALSE(depth_first_search_marked(d, NUM_V));
}

void test_depth_first_search_count() {
  TEST_ASSERT_EQUAL(NUM_V, depth_first_search_count(d));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_depth_first_search_out_of_bound);
  RUN_TEST(test_depth_first_search_marked);
  RUN_TEST(test_depth_first_search_count);
  return UNITY_END();
}
