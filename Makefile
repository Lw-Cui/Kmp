CC		:= g++
CXXFLAG	:= -g -O2 -Wall -Wextra -W -fprofile-arcs -ftest-coverage -pg

all		: Kmp.out

Kmp.out	: Kmp.o
	$(CC) $^ -o $@ $(CXXFLAG)

Kmp.o	: Kmp.cpp
	$(CC) $^ -o $@ $(CXXFLAG) -c

clean	:
	rm -rf Kmp.o Kmp *.gcov *.gcno *.gcda gmon.out

rebuild	: clean all

