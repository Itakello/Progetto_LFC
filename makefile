
CC=gcc
CFLAGS=-I.
DEPS = .\classes\production.h .\data_s\vector.h .\classes\grammar.h .\classes\utility.h
OBJ = main.o .\classes\production.c .\data_s\vector.o .\classes\grammar.o .\classes\utility.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@ $(CC) -o $@ $^ $(CFLAGS)