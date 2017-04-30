include ../../../flags.mk
SRC = scapegoat_tree.h scapegoat_tree_test.cc scapegoat_tree_benchmark.cc

test: scapegoat_tree.h scapegoat_tree_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) scapegoat_tree_test.cc $(TEST_FLAGS) -o scapegoat_tree_test
	./scapegoat_tree_test

benchmark: scapegoat_tree.h scapegoat_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) scapegoat_tree_benchmark.cc $(BENCHMARK_FLAGS) -o scapegoat_tree_benchmark
	./scapegoat_tree_benchmark

perf: scapegoat_tree.h scapegoat_tree_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) scapegoat_tree_benchmark.cc $(PERF_FLAGS) -o scapegoat_tree_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm scapegoat_tree_test scapegoat_tree_benchmark scapegoat_tree_perf perf.data*
