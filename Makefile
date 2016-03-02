CC		:= clang++
CXXFLAG	:= -g -O0 -Wall -Wextra

all		: Kmp

Kmp.o	: Kmp.cpp
	$(CC) $^ -o $@ $(CXXFLAG) -c

clean	:
	rm -rf Kmp.o Kmp

rebuild	: clean all

