include ../../../../flags.mk
SRC = traversal.h traversal_test.cc traversal_benchmark.cc

test: traversal.h traversal_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) traversal_test.cc $(TEST_FLAGS) -o traversal_test
	./traversal_test

benchmark: traversal.h traversal_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) traversal_benchmark.cc $(BENCHMARK_FLAGS) -o traversal_benchmark
	./traversal_benchmark

perf: traversal.h traversal_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) traversal_benchmark.cc $(PERF_FLAGS) -o traversal_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm traversal_test traversal_benchmark traversal_perf perf.data*
