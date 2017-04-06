include ../../flags.mk
SRC = binary_search.h binary_search_test.cc binary_search_benchmark.cc

test: binary_search.h binary_search_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) binary_search_test.cc $(TEST_FLAGS) -o binary_search_test
	./binary_search_test

benchmark: binary_search.h binary_search_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) binary_search_benchmark.cc $(BENCHMARK_FLAGS) -o binary_search_benchmark
	./binary_search_benchmark

perf: binary_search.h binary_search_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) binary_search_benchmark.cc $(PERF_FLAGS) -o binary_search_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm binary_search_test binary_search_benchmark binary_search_perf perf.data*
