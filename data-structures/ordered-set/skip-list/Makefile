include ../../../flags.mk
SRC = skip_list.h skip_list_test.cc skip_list_benchmark.cc

test: skip_list.h skip_list_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) skip_list_test.cc $(TEST_FLAGS) -o skip_list_test
	./skip_list_test

benchmark: skip_list.h skip_list_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) skip_list_benchmark.cc $(BENCHMARK_FLAGS) -o skip_list_benchmark
	./skip_list_benchmark

perf: skip_list.h skip_list_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) skip_list_benchmark.cc $(PERF_FLAGS) -o skip_list_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm skip_list_test skip_list_benchmark skip_list_perf perf.data*
