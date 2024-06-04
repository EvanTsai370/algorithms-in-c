#include <stdbool.h>
#include "unity/unity.h"
#include "../src/graphs/undirected/bfs_paths.h"
#include "unity/unity_internals.h"

#define NUM_E 8

static const int num_v = 6;
static const int num_e = NUM_E;
static const int connections[NUM_E][2] = {{0, 5}, {2, 4}, {2, 3}, {1, 2}, \
                                          {0, 1}, {3, 4}, {3, 5}, {0, 2}};
graph_t *g;
bfs_paths_t *b;

void setUp() {
  g = graph_init(num_v);
  for (int i = 0; i < num_e; i++) {
    TEST_ASSERT_TRUE(graph_add_edge(g, connections[i][0], connections[i][1]));
  }
}

void tearDown() {
  if (b) {
    bfs_paths_free(b);
  }
  graph_free(g);
}

// Tests
// Tests creation of a paths struct with out-of-bounds vertices
void test_out_of_bounds_vertex() {
  b = bfs_paths_init(g, -1);
  TEST_ASSERT_NULL(b);
  b = bfs_paths_init(g, num_v);
  TEST_ASSERT_NULL(b);
}

// Checks that the has_path_to responses are accurate
void test_has_path_to() {
  for (int s = 0; s < num_v; s++) {
    if (b) {
      bfs_paths_free(b);
    }
    b = bfs_paths_init(g, s);
    for (int v = 0; v < num_v; v++) {
      TEST_ASSERT_TRUE(has_bfs_path_to(b, v));
    }
    TEST_ASSERT_FALSE(has_bfs_path_to(b, -1));
    TEST_ASSERT_FALSE(has_bfs_path_to(b, num_v));
  }
}

// Test the path_to iterator (assumes iterator is implemented as a stack)
void test_paths_iter() {
  b = bfs_paths_init(g, 0);
  int path_bfs[] = {0, 5};
  int v = 5;
  int w;
  TEST_ASSERT_TRUE(bfs_path_iter_init(b, v));
  int i = 0;
  while (bfs_path_iter_has_next(b, v)) {
    TEST_ASSERT_TRUE(bfs_path_iter_next(b, v, &w));
    TEST_ASSERT_EQUAL(path_bfs[i], w);
    i++;
  }
}

// Test path_to iterator with repeated call on same vertex.
void test_paths_iter_repeat() {
  b = bfs_paths_init(g, 0);
  int path_bfs[] = {0, 5};
  int v = 5;
  int w;
  TEST_ASSERT_TRUE(bfs_path_iter_init(b, v));
  int i = 0;
  while (bfs_path_iter_has_next(b, v)) {
    TEST_ASSERT_TRUE(bfs_path_iter_next(b, v, &w));
    TEST_ASSERT_EQUAL(path_bfs[i], w);
    i++;
  }

  TEST_ASSERT_TRUE(bfs_path_iter_init(b, v));
  i = 0;
  while (bfs_path_iter_has_next(b, v)) {
    TEST_ASSERT_TRUE(bfs_path_iter_next(b, v, &w));
    TEST_ASSERT_EQUAL(path_bfs[i], w);
    i++;
  }
}

// Tests the path_to iterator with out of bounds values.
void test_paths_iter_out_of_bounds() {
  b = bfs_paths_init(g, 0);
  TEST_ASSERT_FALSE(bfs_path_iter_init(b, -1));
  TEST_ASSERT_FALSE(bfs_path_iter_init(b, num_v));
  TEST_ASSERT_TRUE(bfs_path_iter_init(b, 5));
  TEST_ASSERT_FALSE(bfs_path_iter_has_next(b, -1));
  TEST_ASSERT_FALSE(bfs_path_iter_has_next(b, num_v));
  
  int w;
  TEST_ASSERT_FALSE(bfs_path_iter_next(b, -1, &w));
  TEST_ASSERT_FALSE(bfs_path_iter_next(b, num_v, &w));
}

void test_paths_dist_to() {
  b = bfs_paths_init(g, 0);
  TEST_ASSERT_EQUAL(-1, bfs_dist_to(b, -1));
  TEST_ASSERT_EQUAL(1, bfs_dist_to(b, 2));
  TEST_ASSERT_EQUAL(2, bfs_dist_to(b, 4));
}

// Main
int main() {
  UNITY_BEGIN();
  
  RUN_TEST(test_out_of_bounds_vertex);
  RUN_TEST(test_has_path_to);
  RUN_TEST(test_paths_iter);
  RUN_TEST(test_paths_iter_repeat);
  RUN_TEST(test_paths_iter_out_of_bounds);
  RUN_TEST(test_paths_dist_to);

  return UNITY_END();
}
