UNAME := $(shell uname)
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -I./src

all: s21_matrix_oop.a

alltest: clang-format test leaks clean

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o

s21_matrix_oop.o: s21_matrix_oop.cpp
	g++ $(CXXFLAGS) -c $< -o $@

test: s21_matrix_oop.a
ifeq ($(UNAME),Darwin)
	g++ $(CXXFLAGS) -I/opt/homebrew/include tests.cpp -o test_matrix -L. -L/opt/homebrew/lib s21_matrix_oop.a -lgtest -lgtest_main -lpthread
	./test_matrix
else
	g++ $(CXXFLAGS) -I/usr/include tests.cpp -o test_matrix -L. -L/usr/lib s21_matrix_oop.a -lgtest -lgtest_main -lpthread
	./test_matrix
endif

clang-format:
	clang-format -n *.cpp *.h

leaks:
ifeq ($(UNAME),Darwin)
	leaks -atExit -- ./test_matrix
else
	valgrind --tool=memcheck --leak-check=yes ./test_matrix
endif

clean:
	rm -f s21_matrix_oop.o matrix test_matrix s21_matrix_oop.a