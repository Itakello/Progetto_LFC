
CC=gcc
DEPS = classes/production.h classes/grammar.h classes/utility.h classes/finiteAutoma.h
OBJ = main.o classes/production.o classes/grammar.o classes/utility.o classes/finiteAutoma.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

main: $(OBJ)
	@ $(CC) -o $@ $^