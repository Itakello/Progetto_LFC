
CC=gcc
DEPS = classes/production.h classes/grammar.h classes/utility.h classes/finiteAutoma.h data_s/set.h
OBJ = main.o classes/production.o classes/grammar.o classes/utility.o classes/finiteAutoma.o data_s/set.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

main: $(OBJ)
	@ $(CC) -o $@ $^