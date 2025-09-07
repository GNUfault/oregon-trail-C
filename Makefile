CC      := gcc
SRC     := main.c
BIN     := oregon
MARCH   := i386
MTUNE   := generic
OPT     := s
BITS    := 32
CVER    := c99
GDB     := 0
LDFLAGS := -s
CFLAGS  := -march=$(MARCH) -mtune=$(MTUNE) -O$(OPT) -m$(BITS) -std=$(CVER) -g$(GDB) \ 
		   -Wall -pipe -Wextra -pedantic -pedantic-errors

all:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS)
	strip $(LDFLAGS) $(BIN)
