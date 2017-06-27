include ../../../flags.mk
SRC = dsl.h dsl_test.cc dsl_benchmark.cc

test: dsl.h dsl_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) dsl_test.cc $(TEST_FLAGS) -o dsl_test
	./dsl_test

benchmark: dsl.h dsl_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) dsl_benchmark.cc $(BENCHMARK_FLAGS) -o dsl_benchmark
	./dsl_benchmark

perf: dsl.h dsl_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) dsl_benchmark.cc $(PERF_FLAGS) -o dsl_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm dsl_test dsl_benchmark dsl_perf perf.data*
