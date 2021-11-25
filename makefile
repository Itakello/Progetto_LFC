
CC=gcc
CFLAGS=-I.
DEPS = .\classes\production.h .\data_s\vector.h .\classes\grammar.h
OBJ = main.o .\classes\production.c .\data_s\vector.o .\classes\grammar.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@ $(CC) -o $@ $^ $(CFLAGS)