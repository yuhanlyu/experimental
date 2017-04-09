include ../../../../flags.mk
SRC = wheel_sieve.h wheel_sieve.cc wheel_sieve_test.cc wheel_sieve_benchmark.cc

test: wheel_sieve.h wheel_sieve.cc wheel_sieve_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc wheel_sieve.cc wheel_sieve_test.cc $(TEST_FLAGS) -o wheel_sieve_test
	./wheel_sieve_test

benchmark: wheel_sieve.h wheel_sieve.cc wheel_sieve_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc ../segmented/segmented_sieve.cc wheel_sieve.cc wheel_sieve_benchmark.cc $(BENCHMARK_FLAGS) -o wheel_sieve_benchmark
	./wheel_sieve_benchmark

perf: wheel_sieve.h wheel_sieve.cc wheel_sieve_benchmark.cc
	  $(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) ../eratosthenes/eratosthenes.cc ../segmented/segmented_sieve.cc wheel_sieve.cc wheel_sieve_benchmark.cc $(PERF_FLAGS) -o wheel_sieve_perf


format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm wheel_sieve_test wheel_sieve_benchmark wheel_sieve_perf perf.data*
