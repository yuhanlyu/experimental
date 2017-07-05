include ../../../flags.mk
SRC = red_black_tree.h red_black_tree_test.cc red_black_tree_benchmark.cc

test: red_black_tree.h red_black_tree_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) red_black_tree_test.cc $(TEST_FLAGS) -o red_black_tree_test
	./red_black_tree_test

benchmark: red_black_tree.h red_black_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) red_black_tree_benchmark.cc $(BENCHMARK_FLAGS) -o red_black_tree_benchmark
	./red_black_tree_benchmark

perf: red_black_tree.h red_black_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) red_black_tree_benchmark.cc $(PERF_FLAGS) -o red_black_tree_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm red_black_tree_test red_black_tree_benchmark red_black_tree_perf perf.data*
