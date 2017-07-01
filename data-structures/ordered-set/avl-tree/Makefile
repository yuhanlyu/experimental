include ../../../flags.mk
SRC = avl_tree.h avl_tree_test.cc avl_tree_benchmark.cc

test: avl_tree.h avl_tree_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) avl_tree_test.cc $(TEST_FLAGS) -o avl_tree_test
	./avl_tree_test

benchmark: avl_tree.h avl_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) avl_tree_benchmark.cc $(BENCHMARK_FLAGS) -o avl_tree_benchmark
	./avl_tree_benchmark

perf: avl_tree.h avl_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) avl_tree_benchmark.cc $(PERF_FLAGS) -o avl_tree_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm avl_tree_test avl_tree_benchmark avl_tree_perf perf.data*
