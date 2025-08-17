CC = clang++-19
CLANG_TIDY = clang-tidy
CLANG_FORMAT = clang-format
CPPCHECK = cppcheck

DEBUG_SYMBOL = -g
PTHREAD = -lpthread

CFLAGS = -std=c++23 -pedantic -Wall -Wextra -fno-rtti -fno-exceptions -no-pie
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
OPT_FLAGS = -O3 -march=native -mtune=native -flto=full

CLANG_FORMAT_FLAGS = -i -sort-includes -style='{BasedOnStyle: Google, UseTab: Never, IndentWidth: 2}'

TEST_FLAGS = $(DEBUG_SYMBOL) $(SANITIZE_FLAGS) -lgtest -lgtest_main $(PTHREAD)

BENCHMARK_FLAGS = $(OPT_FLAGS) $(PTHREAD) -lbenchmark -g -stdlib=libc++

SRC = red_black_tree.h red_black_tree_test.cc red_black_tree_benchmark.cc red_black_tree_standard.h red_black_tree_standard_link.h

test: red_black_tree.h red_black_tree_test.cc
	$(CC) $(CFLAGS) red_black_tree_test.cc $(TEST_FLAGS) -o red_black_tree_test
	./red_black_tree_test

benchmark: red_black_tree.h red_black_tree_standard.h red_black_tree_benchmark.cc
	$(CC) $(CFLAGS) red_black_tree_benchmark.cc $(BENCHMARK_FLAGS) -o red_black_tree_benchmark
	./red_black_tree_benchmark --benchmark_repetitions=100 --benchmark_report_aggregates_only=true --benchmark_min_warmup_time=1

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clean:
	rm red_black_tree_test red_black_tree_benchmark red_black_tree_perf perf.data*
