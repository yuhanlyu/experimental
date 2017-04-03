include ../../../../flags.mk
SRC = eratosthenes.h eratosthenes.cc eratosthenes_test.cc

test: eratosthenes.h eratosthenes.cc eratosthenes_test.cc
	$(CC) $(CFLAGS) -L$(LIB_DIR) -I$(INCLUDE_DIR) eratosthenes.cc eratosthenes_test.cc $(TEST_FLAGS) -o eratosthenes_test
	./eratosthenes_test

format: $(SRC)
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(SRC)

clang-tidy: $(SRC)
	$(CLANG_TIDY) $(SRC) $(CLANG_TIDY_FLAGS)

cppcheck: $(SRC)
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC)

clean:
	rm eratosthenes_test
