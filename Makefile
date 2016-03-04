CC		:= icc
CXXFLAG	:= -g -O2 -Wall -Wextra -qopt-report=3

all		: Kmp

Kmp.o	: Kmp.cpp
	$(CC) $^ -o $@ $(CXXFLAG) -c

clean	:
	rm -rf Kmp.o Kmp

rebuild	: clean all

