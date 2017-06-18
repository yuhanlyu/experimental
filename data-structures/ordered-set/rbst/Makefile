include ../../../flags.mk
SRC = rbst.h rbst_test.cc rbst_benchmark.cc

test: rbst.h rbst_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rbst_test.cc $(TEST_FLAGS) -o rbst_test
	./rbst_test

benchmark: rbst.h rbst_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rbst_benchmark.cc $(BENCHMARK_FLAGS) -o rbst_benchmark
	./rbst_benchmark

perf: rbst.h rbst_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rbst_benchmark.cc $(PERF_FLAGS) -o rbst_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm rbst_test rbst_benchmark rbst_perf perf.data*
