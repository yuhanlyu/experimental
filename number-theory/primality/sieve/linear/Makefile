include ../../../../flags.mk
SRC = linear_sieve.h linear_sieve.cc linear_sieve_test.cc linear_sieve_benchmark.cc

test: linear_sieve.h linear_sieve.cc linear_sieve_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc linear_sieve.cc linear_sieve_test.cc $(TEST_FLAGS) -o linear_sieve_test
	./linear_sieve_test

benchmark: linear_sieve.h linear_sieve.cc linear_sieve_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc linear_sieve.cc linear_sieve_benchmark.cc $(BENCHMARK_FLAGS) -o linear_sieve_benchmark
	./linear_sieve_benchmark

perf: linear_sieve.h linear_sieve.cc linear_sieve_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc linear_sieve.cc linear_sieve_benchmark.cc $(PERF_FLAGS) -o linear_sieve_perf


format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm linear_sieve_test linear_sieve_benchmark linear_sieve_perf perf.data*
