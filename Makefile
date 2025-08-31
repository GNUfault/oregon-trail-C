all:
	gcc main.c -o oregon -march=i386 -mtune=generic -Os -m32 -Wall -pipe -Wextra -std=c99 -pedantic -pedantic-errors -g0
	strip -s oregon
