include ../../../../flags.mk
SRC = segmented_sieve.h segmented_sieve.cc segmented_sieve_test.cc segmented_sieve_benchmark.cc

test: segmented_sieve.h segmented_sieve.cc segmented_sieve_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc segmented_sieve.cc segmented_sieve_test.cc $(TEST_FLAGS) -o segmented_sieve_test
	./segmented_sieve_test

benchmark: segmented_sieve.h segmented_sieve.cc segmented_sieve_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc segmented_sieve.cc segmented_sieve_benchmark.cc $(BENCHMARK_FLAGS) -o segmented_sieve_benchmark
	./segmented_sieve_benchmark

perf: segmented_sieve.h segmented_sieve.cc segmented_sieve_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc segmented_sieve.cc segmented_sieve_benchmark.cc $(PERF_FLAGS) -o segmented_sieve_perf


format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm segmented_sieve_test segmented_sieve_benchmark segmented_sieve_perf perf.data*
