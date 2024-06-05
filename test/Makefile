CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror -g -DUNITY_INCLUDE_DOUBLE -fsanitize=address -fsanitize=undefined
ALGORITHMS_PATH := ../src
UNITY_PATH := unity

objects := bag_test queue_test stack_test graph_test dfs_test \
					 dfs_paths_test bfs_paths_test cc_test cycle_test bipartite_test \
					 bipartite_x_test

all: $(objects)
	@echo Executing tests
	$(foreach obj, $(objects), ./$(obj);)

bipartite_x_test: bipartite_x_test.o bipartite_x.o graph.o unity.o bag.o stack.o queue.o
	@echo Compiling bipartite_x_test
	$(CC) $(CFLAGS) $^ -o $@

bipartite_x.o: ${ALGORITHMS_PATH}/graphs/undirected/bipartite_x.c
	$(CC) -c $(CFLAGS) $^ -o $@

bipartite_test: bipartite_test.o bipartite.o graph.o unity.o bag.o stack.o
	@echo Compiling bipartite_test
	$(CC) $(CFLAGS) $^ -o $@

bipartite.o: ${ALGORITHMS_PATH}/graphs/undirected/bipartite.c
	$(CC) -c $(CFLAGS) $^ -o $@

cycle_test: cycle.o graph.o unity.o bag.o cycle_test.o stack.o
	@echo Compiling cycle_test
	$(CC) $(CFLAGS) $^ -o $@

cycle.o: ${ALGORITHMS_PATH}/graphs/undirected/cycle.c
	$(CC) -c $(CFLAGS) $^ -o $@

cc_test: connected_components.o graph.o unity.o bag.o cc_test.o
	@echo Compiling cc_test
	$(CC) $(CFLAGS) $^ -o $@

connected_components.o: ${ALGORITHMS_PATH}/graphs/undirected/connected_components.c
	$(CC) -c $(CFLAGS) $^ -o $@

bfs_paths_test: lib.o bfs_paths_test.o graph.o unity.o bag.o stack.o queue.o bfs_paths.o
	@echo Compiling bfs_paths_test
	$(CC) $(CFLAGS) $^ -o $@

bfs_paths.o: ${ALGORITHMS_PATH}/graphs/undirected/bfs_paths.c
	$(CC) -c $(CFLAGS) $^ -o $@

dfs_paths_test: lib.o dfs_paths_test.o graph.o unity.o bag.o stack.o dfs_paths.o
	@echo Compiling dfs_paths_test
	$(CC) $(CFLAGS) $^ -o $@

dfs_paths.o: ${ALGORITHMS_PATH}/graphs/undirected/dfs_paths.c
	$(CC) -c $(CFLAGS) $^ -o $@

dfs_test: lib.o dfs_test.o graph.o unity.o bag.o dfs.o
	@echo Compiling dfs_test
	$(CC) $(CFLAGS) $^ -o $@

dfs.o: ${ALGORITHMS_PATH}/graphs/undirected/dfs.c
	$(CC) -c $(CFLAGS) $^ -o $@

graph_test: lib.o graph_test.o graph.o unity.o bag.o
	@echo Compiling graph_test
	$(CC) $(CFLAGS) $^ -o $@

graph.o: $(ALGORITHMS_PATH)/graphs/undirected/graph.c
	$(CC) -c $(CFLAGS) $^ -o $@

stack_test: lib.o stack_test.o stack.o unity.o
	@echo Compiling stack_test
	$(CC) $(CFLAGS) $^ -o $@

stack.o: ${ALGORITHMS_PATH}/data_structures/stack/stack.c
	$(CC) -c $(CFLAGS) $^ -o $@

queue_test: lib.o queue_test.o queue.o unity.o
	@echo Compiling queue_test
	$(CC) $(CFLAGS) $^ -o $@

queue.o: ${ALGORITHMS_PATH}/data_structures/queue/queue.c
	$(CC) -c $(CFLAGS) $^ -o $@

# Bag
bag_test: lib.o bag_test.o bag.o unity.o
	@echo Compiling bag_test
	$(CC) $(CFLAGS) $^ -o $@

bag.o: $(ALGORITHMS_PATH)/data_structures/bag/bag.c
	$(CC) -c $(CFLAGS) $^ -o $@

# Unity test framework
unity.o: $(UNITY_PATH)/unity.c
	@$(CC) -c $(CFLAGS) $^ -o $@

# Common library
lib.o: $(ALGORITHMS_PATH)/lib/lib.c
	@$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f $(objects) *.o
