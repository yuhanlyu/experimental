include ../../flags.mk
SRC = biased_search.h biased_search_test.cc biased_search_benchmark.cc

test: biased_search.h biased_search_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) biased_search_test.cc $(TEST_FLAGS) -o biased_search_test
	./biased_search_test

benchmark: biased_search.h biased_search_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) biased_search_benchmark.cc $(BENCHMARK_FLAGS) -o biased_search_benchmark
	./biased_search_benchmark

perf: biased_search.h biased_search_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) biased_search_benchmark.cc $(PERF_FLAGS) -o biased_search_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm biased_search_test biased_search_benchmark biased_search_perf perf.data*
