include ../../../flags.mk
SRC = weight_balanced_tree.h weight_balanced_tree_test.cc weight_balanced_tree_benchmark.cc

test: weight_balanced_tree.h weight_balanced_tree_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) weight_balanced_tree_test.cc $(TEST_FLAGS) -o weight_balanced_tree_test
	./weight_balanced_tree_test

benchmark: weight_balanced_tree.h weight_balanced_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) weight_balanced_tree_benchmark.cc $(BENCHMARK_FLAGS) -o weight_balanced_tree_benchmark
	./weight_balanced_tree_benchmark

perf: weight_balanced_tree.h weight_balanced_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) weight_balanced_tree_benchmark.cc $(PERF_FLAGS) -o weight_balanced_tree_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm weight_balanced_tree_test weight_balanced_tree_benchmark weight_balanced_tree_perf perf.data*
