include ../../../../flags.mk
SRC = rebalance.h rebalance_test.cc rebalance_benchmark.cc

test: rebalance.h rebalance_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rebalance_test.cc $(TEST_FLAGS) -o rebalance_test
	./rebalance_test

benchmark: rebalance.h rebalance_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rebalance_benchmark.cc $(BENCHMARK_FLAGS) -o rebalance_benchmark
	./rebalance_benchmark

perf: rebalance.h rebalance_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rebalance_benchmark.cc $(PERF_FLAGS) -o rebalance_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm rebalance_test rebalance_benchmark rebalance_perf perf.data*
