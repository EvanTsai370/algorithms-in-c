CC = gcc
CFLAGS = -Wall -Werror -g -DUNITY_INCLUDE_DOUBLE
ALGORITHMS_PATH := ../src
UNITY_PATH := unity

objects := bag_test queue_test stack_test

all: $(objects)
	@echo Executing tests
	$(foreach obj, $(objects), ./$(obj);)
	make clean

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
