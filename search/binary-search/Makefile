CC = clang++-19
CLANG_TIDY = clang-tidy
CLANG_FORMAT = clang-format
CPPCHECK = cppcheck

DEBUG_SYMBOL = -g
PTHREAD = -lpthread

CFLAGS = -std=c++23 -pedantic -Wall -Wextra -fno-rtti -fno-exceptions -no-pie
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
OPT_FLAGS = -O3 -march=native -mtune=native -flto=full -falign-loops=64 -mllvm -x86-cmov-converter=false

CLANG_FORMAT_FLAGS = -i -sort-includes -style='{BasedOnStyle: Google, UseTab: Never, IndentWidth: 2}'

TEST_FLAGS = $(DEBUG_SYMBOL) $(SANITIZE_FLAGS) -lgtest -lgtest_main $(PTHREAD)

BENCHMARK_FLAGS = $(OPT_FLAGS) $(PTHREAD) -lbenchmark -stdlib=libc++

SRC = binary_search.h binary_search_test.cc binary_search_benchmark.cc

test: binary_search.h binary_search_test.cc
	$(CC) $(CFLAGS) binary_search_test.cc $(TEST_FLAGS) -o binary_search_test
	./binary_search_test

benchmark: binary_search.h binary_search_benchmark.cc
	$(CC) $(CFLAGS) binary_search_benchmark.cc $(BENCHMARK_FLAGS) -o binary_search_benchmark
	./binary_search_benchmark --benchmark_repetitions=100 --benchmark_report_aggregates_only=true --benchmark_min_warmup_time=1

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clean:
	rm binary_search_test binary_search_benchmark binary_search_perf perf.data*
