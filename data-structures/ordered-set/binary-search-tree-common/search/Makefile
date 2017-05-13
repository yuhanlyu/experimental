include ../../../../flags.mk
SRC = search.h search_test.cc search_benchmark.cc

test: search.h search_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) search_test.cc $(TEST_FLAGS) -o search_test
	./search_test

benchmark: search.h search_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) search_benchmark.cc $(BENCHMARK_FLAGS) -o search_benchmark
	./search_benchmark

perf: search.h search_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) search_benchmark.cc $(PERF_FLAGS) -o search_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm search_test search_benchmark search_perf perf.data*
