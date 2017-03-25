include ../../../flags.mk
SRC = sum_benchmark.cc

benchmark: sum_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) sum_benchmark.cc $(BENCHMARK_FLAGS) -o sum_benchmark
	./sum_benchmark

perf: sum_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) sum_benchmark.cc $(PERF_FLAGS) -o sum_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm sum_benchmark sum_perf perf.data*
