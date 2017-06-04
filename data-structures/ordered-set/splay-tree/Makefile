include ../../../flags.mk
SRC = splay_tree.h splay_tree_test.cc splay_tree_benchmark.cc

test: splay_tree.h splay_tree_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) splay_tree_test.cc $(TEST_FLAGS) -o splay_tree_test
	./splay_tree_test

benchmark: splay_tree.h splay_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) splay_tree_benchmark.cc $(BENCHMARK_FLAGS) -o splay_tree_benchmark
	./splay_tree_benchmark

perf: splay_tree.h splay_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) splay_tree_benchmark.cc $(PERF_FLAGS) -o splay_tree_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm splay_tree_test splay_tree_benchmark splay_tree_perf perf.data*
