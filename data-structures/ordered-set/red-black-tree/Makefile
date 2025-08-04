CC = clang++-19
CLANG_TIDY = clang-tidy
CLANG_FORMAT = clang-format
CPPCHECK = cppcheck

DEBUG_SYMBOL = -g
PTHREAD = -lpthread

CFLAGS = -std=c++23 -pedantic -Wall -Wextra -fno-rtti -fno-exceptions -no-pie
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
OPT_FLAGS = -O3 -march=native -mtune=native -flto=full

CLANG_FORMAT_FLAGS = -i -style=Google -sort-includes

TEST_FLAGS = $(DEBUG_SYMBOL) $(SANITIZE_FLAGS) -lgtest -lgtest_main $(PTHREAD)

BENCHMARK_FLAGS = $(OPT_FLAGS) $(PTHREAD) -lbenchmark -g

SRC = red_black_tree.h red_black_tree_test.cc red_black_tree_benchmark.cc red_black_tree_standard.h red_black_tree_standard_link.h

test: red_black_tree.h red_black_tree_test.cc
	$(CC) $(CFLAGS) red_black_tree_test.cc $(TEST_FLAGS) -o red_black_tree_test
	./red_black_tree_test

benchmark: red_black_tree.h red_black_tree_standard.h red_black_tree_benchmark.cc
	$(CC) $(CFLAGS) red_black_tree_benchmark.cc $(BENCHMARK_FLAGS) -o red_black_tree_benchmark
	./red_black_tree_benchmark --benchmark_min_time=30s

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

clean:
	rm red_black_tree_test red_black_tree_benchmark red_black_tree_perf perf.data*
