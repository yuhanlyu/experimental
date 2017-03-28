include ../../../flags.mk
SRC = stackless_qsort.h stackless_qsort_test.cc stackless_qsort_benchmark.cc

test: stackless_qsort.h stackless_qsort_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) stackless_qsort_test.cc $(TEST_FLAGS) -o stackless_qsort_test
	./stackless_qsort_test

benchmark: stackless_qsort.h stackless_qsort_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) stackless_qsort_benchmark.cc $(BENCHMARK_FLAGS) -o stackless_qsort_benchmark
	./stackless_qsort_benchmark

perf: stackless_qsort.h stackless_qsort_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) stackless_qsort_benchmark.cc $(PERF_FLAGS) -o stackless_qsort_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm stackless_qsort_test stackless_qsort_benchmark stackless_qsort_perf perf.data*
