#include <stdbool.h>
#include "unity/unity.h"
#include "../src/graphs/undirected/dfs_paths.h"

static const int num_v = 6;
static const int num_e = 8;
static const int connections[num_e][2] = {{0, 5}, {2, 4}, {2, 3}, {1, 2}, \
                                          {0, 1}, {3, 4}, {3, 5}, {0, 2}};

graph_t *g;
dfs_paths_t *d;

void setUp() {
  g = graph_init(num_v);
  for (int i = 0; i < num_e; i++) {
    TEST_ASSERT_TRUE(graph_add_edge(g, connections[i][0], connections[i][1]));
  }
}

void tearDown() {
  graph_free(g);
  if (d) {
    dfs_paths_free(d);
  }
}

// Tests
// Tests creation of a paths struct with out-of-bounds vertices
void test_out_of_bounds_vertex() {
  d = dfs_paths_init(g, -1);
  TEST_ASSERT_NULL(d);
  d = dfs_paths_init(g, num_v);
  TEST_ASSERT_NULL(d);
}

// Checks that the has_path_to responses are accurate
void test_has_path_to() {
  for (int s = 0; s < num_v; s++) {
    if (d) {
      dfs_paths_free(d);
    }
    d = dfs_paths_init(g, s);
    for (int v = 0; v < num_v; v++) {
      TEST_ASSERT_TRUE(has_dfs_path_to(d, v));
    }
    TEST_ASSERT_FALSE(has_dfs_path_to(d, -1));
    TEST_ASSERT_FALSE(has_dfs_path_to(d, num_v));
  }
}

// Test the path_to iterator (assumes iterator is implemented as a stack)
void test_paths_iter() {
  d = dfs_paths_init(g, 0);
  int path_dfs[] = {0, 2, 3, 5};
  int v = 5;
  int w;
  TEST_ASSERT_TRUE(dfs_path_iter_init(d, v));
  int i = 0;
  while (dfs_path_iter_has_next(d, v)) {
    TEST_ASSERT_TRUE(dfs_path_iter_next(d, v, &w));
    TEST_ASSERT_EQUAL(path_dfs[i], w);
    i++;
  }
}

// Test path_to iterator with repeated call on same vertex.
void test_paths_iter_repeat() {
  d = dfs_paths_init(g, 0);
  int path_dfs[] = {0, 2, 3, 5};
  int v = 5;
  int w;
  TEST_ASSERT_TRUE(dfs_path_iter_init(d, v));
  int i = 0;
  while (dfs_path_iter_has_next(d, v)) {
    TEST_ASSERT_TRUE(dfs_path_iter_next(d, v, &w));
    TEST_ASSERT_EQUAL(path_dfs[i], w);
    i++;
  }

  TEST_ASSERT_TRUE(dfs_path_iter_init(d, v));
  i = 0;
  while (dfs_path_iter_has_next(d, v)) {
    TEST_ASSERT_TRUE(dfs_path_iter_next(d, v, &w));
    TEST_ASSERT_EQUAL(path_dfs[i], w);
    i++;
  }
}

// Tests the path_to iterator with out of bounds values.
void test_paths_iter_out_of_bounds() {
  d = dfs_paths_init(g, 0);
  TEST_ASSERT_FALSE(dfs_path_iter_init(d, -1));
  TEST_ASSERT_FALSE(dfs_path_iter_init(d, num_v));
  TEST_ASSERT_TRUE(dfs_path_iter_init(d, 5));
  TEST_ASSERT_FALSE(dfs_path_iter_has_next(d, -1));
  TEST_ASSERT_FALSE(dfs_path_iter_has_next(d, num_v));
  
  int w;
  TEST_ASSERT_FALSE(dfs_path_iter_next(d, -1, &w));
  TEST_ASSERT_FALSE(dfs_path_iter_next(d, num_v, &w));
}

// Main
int main() {
  UNITY_BEGIN();
  
  RUN_TEST(test_out_of_bounds_vertex);
  RUN_TEST(test_has_path_to);
  RUN_TEST(test_paths_iter);
  RUN_TEST(test_paths_iter_repeat);
  RUN_TEST(test_paths_iter_out_of_bounds);

  return UNITY_END();
}
