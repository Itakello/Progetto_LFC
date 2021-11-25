
CC=gcc
CFLAGS=-I.
DEPS = .\classes\production.h .\classes\grammar.h .\classes\utility.h
OBJ = main.o .\classes\production.c .\classes\grammar.o .\classes\utility.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@ $(CC) -o $@ $^ $(CFLAGS)