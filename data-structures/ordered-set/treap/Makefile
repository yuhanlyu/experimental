include ../../../flags.mk
SRC = treap.h treap_test.cc treap_benchmark.cc

test: treap.h treap_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) treap_test.cc $(TEST_FLAGS) -o treap_test
	./treap_test

benchmark: treap.h treap_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) treap_benchmark.cc $(BENCHMARK_FLAGS) -o treap_benchmark
	./treap_benchmark

perf: treap.h treap_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) treap_benchmark.cc $(PERF_FLAGS) -o treap_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm treap_test treap_benchmark treap_perf perf.data*
