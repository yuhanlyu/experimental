include ../../../../flags.mk
SRC = eratosthenes.h eratosthenes.cc eratosthenes_test.cc eratosthenes_benchmark.cc

test: eratosthenes.h eratosthenes.cc eratosthenes_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) eratosthenes.cc eratosthenes_test.cc $(TEST_FLAGS) -o eratosthenes_test
	./eratosthenes_test

benchmark: eratosthenes.h eratosthenes.cc eratosthenes_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) eratosthenes.cc eratosthenes_benchmark.cc $(BENCHMARK_FLAGS) -o eratosthenes_benchmark
	./eratosthenes_benchmark

perf: eratosthenes.h eratosthenes.cc eratosthenes_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) eratosthenes.cc eratosthenes_benchmark.cc $(PERF_FLAGS) -o eratosthenes_perf


format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm eratosthenes_test eratosthenes_benchmark eratosthenes_perf perf.data*
