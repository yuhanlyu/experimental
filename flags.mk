CC = g++
CLANG_TIDY = clang-tidy
CLANG_FORMAT = clang-format
CPPCHECK = cppcheck

LIB_DIR = /usr/local/lib
INCLUDE_DIR = /usr/local/include
DEBUG_SYMBOL = -g
PTHREAD = -lpthread

CFLAGS = -std=c++14 -pedantic -Wall -Wextra
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
OPT_FLAGS = -O3 -march=native -flto -fipa-pta
CLANG_FORMAT_FLAGS = -i -style=Google -sort-includes
CLANG_TIDY_FLAGS = -checks=* -- -std=c++14 -I$(INCLUDE_DIR)
CPPCHECK_FLAGS = --enable=all


TEST_FLAGS = $(DEBUG_SYMBOL) $(SANITIZE_FLAGS) -lgtest -lgtest_main $(PTHREAD)

BENCHMARK_FLAGS = $(OPT_FLAGS) -lbenchmark -lpthread

PERF_FLAGS = $(OPT_FLAGS) $(DEBUG_SYMBOL) -lbenchmark $(PTHREAD)
