CC = gcc
CFLAGS = -Wall -Werror -g -DUNITY_INCLUDE_DOUBLE
ALGORITHMS_PATH := ../src
UNITY_PATH := unity

objects := bag_test

all: $(objects)
	@echo Executing tests
	$(foreach obj, $(objects), ./$(obj);)
	make clean

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
