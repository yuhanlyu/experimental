include ../../../flags.mk
SRC = aa_tree.h aa_tree_test.cc aa_tree_benchmark.cc

test: aa_tree.h aa_tree_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) aa_tree_test.cc $(TEST_FLAGS) -o aa_tree_test
	./aa_tree_test

benchmark: aa_tree.h aa_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) aa_tree_benchmark.cc $(BENCHMARK_FLAGS) -o aa_tree_benchmark
	./aa_tree_benchmark

perf: aa_tree.h aa_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) aa_tree_benchmark.cc $(PERF_FLAGS) -o aa_tree_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm aa_tree_test aa_tree_benchmark aa_tree_perf perf.data*
