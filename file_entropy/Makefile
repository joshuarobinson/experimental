CC=g++
FLAGS=-std=c++11 -Werror -Wall -Wextra -O3

all:	entropy_cpp entropy_c

entropy_cpp:	entropy.cpp
		$(CC) $(FLAGS) -o entropy_cpp entropy.cpp

entropy_c:	entropy.c
		gcc -std=c99 -Werror -Wall -O3 -o entropy_c entropy.c -lm

clean:
		rm -f entropy_c entropy_cpp
