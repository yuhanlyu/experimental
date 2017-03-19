# Experimental library
This is a collection of algorithms that I had implemented/tested.

I use [googletest](https://github.com/google/googletest) for unit test and use [google benchmark](https://github.com/google/benchmark) to measure the performance. In order to run the test/benchmark, installation of these two libraries is required.

The source code is checked by [clang-tidy](http://clang.llvm.org/extra/clang-tidy/) and formatted by [clang-format](https://clang.llvm.org/docs/ClangFormat.html).

In order to find the bottleneck of the program, Linux [perf](https://en.wikipedia.org/wiki/Perf_(Linux)) and [pmu-tools](https://github.com/andikleen/pmu-tools) are used.

## Flags
The commonly used flags for Makefile is listed in flags.mk.

LIB\_DIR and INCLUDE\_DIR should include the library and header files for googletest and google benchmark in order to compile the program.

Address and undefined sanitizers are turned in the unit test to find potential bugs.

The performance is measured with -O3 -march=native -flto -fipa-pta flags.

## Usage

Please see the Makefile in each folder.Here are common targets:
* test: generate the test binary.
* benchmark: generate the benchmark library
* perf: generate the binary with debug symbol, which is useful in perf.
* clang-tidy: execute clang-tidy to check the source program.
* cppcheck: use cppcheck to check the source program.
* format: execute clang-format to format the source program.
* clean: remove all binaries and perf record.

Befure run the benchmark, please turn off the cpu scaling.
On linux, you can execute the following commdn to turn off the cpu scaling:
`sudo cpupower frequency-set -g performance`

On linux, you can execute the following commdn to turn on the cpu scaling:
`sudo cpupower frequency-set -g powersave`
