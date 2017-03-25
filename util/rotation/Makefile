include ../../flags.mk
SRC = rotation.h rotation.cc rotation_test.cc rotation_benchmark.cc

test: rotation.h rotation.cc rotation_test.cc
		$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rotation.cc rotation_test.cc $(TEST_FLAGS) -o rotation_test
			./rotation_test

benchmark: rotation.h rotation.cc rotation_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rotation.cc rotation_benchmark.cc $(BENCHMARK_FLAGS) -o rotation_benchmark
	./rotation_benchmark

perf: rotation.h rotation.cc rotation_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) rotation.cc rotation_benchmark.cc $(PERF_FLAGS) -o rotation_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm rotation_test rotation_benchmark rotation_perf perf.data*
