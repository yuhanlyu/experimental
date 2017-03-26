include ../../flags.mk
SRC = josephus.h josephus.cc josephus_test.cc josephus_benchmark.cc

test: josephus.h josephus.cc josephus_test.cc
		$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) josephus.cc josephus_test.cc $(TEST_FLAGS) -o josephus_test
			./josephus_test

benchmark: josephus.h josephus.cc josephus_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) josephus.cc josephus_benchmark.cc $(BENCHMARK_FLAGS) -o josephus_benchmark
	./josephus_benchmark

perf: josephus.h josephus.cc josephus_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) josephus.cc josephus_benchmark.cc $(PERF_FLAGS) -o josephus_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm josephus_test josephus_benchmark josephus_perf perf.data*
