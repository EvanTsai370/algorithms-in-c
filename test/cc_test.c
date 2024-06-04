#include <stdbool.h>

#include "unity/unity.h"
#include "../src/graphs/undirected/connected_components.h"

#define NUM_E 13

static const int num_v = 13;
static const int num_e = NUM_E;
static const int connections[NUM_E][2] = {{0, 5}, {4, 3}, {0, 1}, {9, 12}, \
                                              {6, 4}, {5, 4}, {0, 2}, {11, 12},\
                                              {9, 10}, {0, 6}, {7, 8}, {9, 11},\
                                              {5, 3}};

cc_t *cc;
graph_t *g;

// Helper function
void fill_graph(graph_t *g) {
  for (int i = 0; i < num_e; i++) {
    graph_add_edge(g, connections[i][0], connections[i][1]);
  }
}

void setUp() {
  g = graph_init(num_v);
  fill_graph(g);
  cc = cc_init(g);
}

void tearDown() {
  if (cc) {
    cc_free(cc);
  }
  if (g) {
    graph_free(g);
  }
}

// Tests

void test_cc_count() {
  TEST_ASSERT_EQUAL(3, cc_count(cc));
}

void test_cc_id() {
  int expected[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2};
  for (int i = 0; i < graph_V(g); i++) {
    TEST_ASSERT_EQUAL(expected[i], cc_id(cc, i));
  }
}

void test_cc_size() {
  int expected[] = {7, 7, 7, 7, 7, 7, 7, 2, 2, 4, 4, 4, 4};
  for (int i = 0; i < graph_V(g); i++) {
    TEST_ASSERT_EQUAL(expected[i], cc_size(cc, i));
  }
}

void test_cc_connected() {
  TEST_ASSERT_TRUE(cc_connected(cc, 0, 1));
  TEST_ASSERT_TRUE(cc_connected(cc, 7, 8));
  TEST_ASSERT_TRUE(cc_connected(cc, 9, 10));
  TEST_ASSERT_FALSE(cc_connected(cc, 8, 9));
}

// Main
int main() {
  UNITY_BEGIN();
  
  RUN_TEST(test_cc_count);
  RUN_TEST(test_cc_id);
  RUN_TEST(test_cc_size);
  RUN_TEST(test_cc_connected);

  return UNITY_END();
}
