include ../../../flags.mk
SRC = stack_by_queue.h stack_by_queue_test.cc stack_by_queue_benchmark.cc

test: stack_by_queue.h stack_by_queue_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) stack_by_queue_test.cc $(TEST_FLAGS) -o stack_by_queue_test
	./stack_by_queue_test

benchmark: stack_by_queue.h stack_by_queue_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) stack_by_queue_benchmark.cc $(BENCHMARK_FLAGS) -o stack_by_queue_benchmark
		./stack_by_queue_benchmark

perf: stack_by_queue.h stack_by_queue_benchmark.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) stack_by_queue_benchmark.cc $(PERF_FLAGS) -o stack_by_queue_perf

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm stack_by_queue_test stack_by_queue_benchmark stack_by_queue_perf perf.data*
