include ../../../flags.mk
SRC = fib.h fib.cc fib_test.cc fib_benchmark.cc

test: fib.h fib.cc fib_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) fib.cc fib_test.cc $(TEST_FLAGS) -o fib_test
	./fib_test

benchmark: fib.cc fib.h fib_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) fib.cc fib_benchmark.cc $(BENCHMARK_FLAGS) -o fib_benchmark
	./fib_benchmark

perf: fib.cc fib.h fib_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) fib.cc fib_benchmark.cc $(PERF_FLAGS) -o fib_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm fib_test fib_benchmark fib_perf perf.data*
