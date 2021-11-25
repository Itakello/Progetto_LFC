
CC=gcc
DEPS = ./classes/production.h ./classes/grammar.h ./classes/utility.h
OBJ = main.o ./classes/production.o ./classes/grammar.o ./classes/utility.o

all:main.
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

main: $(OBJ)
	@ $(CC) -o $@ $^