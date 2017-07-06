include ../../../flags.mk
SRC = wavl.h wavl_test.cc wavl_benchmark.cc

test: wavl.h wavl_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) wavl_test.cc $(TEST_FLAGS) -o wavl_test
	./wavl_test

benchmark: wavl.h wavl_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) wavl_benchmark.cc $(BENCHMARK_FLAGS) -o wavl_benchmark
	./wavl_benchmark

perf: wavl.h wavl_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) wavl_benchmark.cc $(PERF_FLAGS) -o wavl_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm wavl_test wavl_benchmark wavl_perf perf.data*
