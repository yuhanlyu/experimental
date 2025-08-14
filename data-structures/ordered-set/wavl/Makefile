CC = clang++-19
CLANG_TIDY = clang-tidy
CLANG_FORMAT = clang-format

DEBUG_SYMBOL = -g
PTHREAD = -lpthread

CFLAGS = -std=c++23 -pedantic -Wall -Wextra -fno-rtti -fno-exceptions -no-pie
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
OPT_FLAGS = -O3 -march=native -mtune=native -flto=full

CLANG_FORMAT_FLAGS = -i -sort-includes -style='{BasedOnStyle: Google, UseTab: Never, IndentWidth: 2}'

TEST_FLAGS = $(DEBUG_SYMBOL) $(SANITIZE_FLAGS) -lgtest -lgtest_main $(PTHREAD)

BENCHMARK_FLAGS = $(OPT_FLAGS) $(PTHREAD) -lbenchmark -g

SRC = wavl.h wavl_standard.h wavl_test.cc wavl_benchmark.cc

test: wavl.h wavl_standard.h wavl_test.cc
	$(CC) $(CFLAGS) wavl_test.cc $(TEST_FLAGS) -o wavl_test
	./wavl_test

benchmark: wavl.h wavl_benchmark.cc
	$(CC) $(CFLAGS) wavl_benchmark.cc $(BENCHMARK_FLAGS) -o wavl_benchmark
	./wavl_benchmark --benchmark_repetitions=100 --benchmark_report_aggregates_only=true --benchmark_min_warmup_time=1

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clean:
	rm wavl_test wavl_benchmark wavl_perf perf.data*
