CC = clang++-19
CLANG_TIDY = clang-tidy
CLANG_FORMAT = clang-format
CPPCHECK = cppcheck

DEBUG_SYMBOL = -g
PTHREAD = -lpthread

CFLAGS = -std=c++23 -pedantic -Wall -Wextra -fno-rtti -fno-exceptions -no-pie
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
OPT_FLAGS = -O3 -march=native -mtune=native -flto=full -falign-loops=64 -mbranches-within-32B-boundaries

CLANG_FORMAT_FLAGS = -i -style=Google -sort-includes

TEST_FLAGS = $(DEBUG_SYMBOL) $(SANITIZE_FLAGS) -lgtest -lgtest_main $(PTHREAD)

BENCHMARK_FLAGS = $(OPT_FLAGS) $(PTHREAD) -lbenchmark

SRC = binary_search.h binary_search_test.cc binary_search_benchmark.cc

test: binary_search.h binary_search_test.cc
	$(CC) $(CFLAGS) binary_search_test.cc $(TEST_FLAGS) -o binary_search_test
	./binary_search_test

benchmark: binary_search.h binary_search_benchmark.cc
	$(CC) $(CFLAGS) binary_search_benchmark.cc $(BENCHMARK_FLAGS) -o binary_search_benchmark
	./binary_search_benchmark

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clean:
	rm binary_search_test binary_search_benchmark binary_search_perf perf.data*
