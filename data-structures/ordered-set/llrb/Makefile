include ../../../flags.mk
SRC = llrb.h llrb_test.cc llrb_benchmark.cc

test: llrb.h llrb_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) llrb_test.cc $(TEST_FLAGS) -o llrb_test
	./llrb_test

benchmark: llrb.h llrb_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) llrb_benchmark.cc $(BENCHMARK_FLAGS) -o llrb_benchmark
	./llrb_benchmark

perf: llrb.h llrb_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) llrb_benchmark.cc $(PERF_FLAGS) -o llrb_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm llrb_test llrb_benchmark llrb_perf perf.data*
