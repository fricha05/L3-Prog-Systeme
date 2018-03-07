NOMFICHIER = tp3
CC = gcc
CFLAGS = -g -O2 -Wall -Wfatal-errors
LDFLAGS = 
LDLIBS = 
OBJ = tp3.o ex1.o ex2.o ex3.o ex4.o ex5.o

$(NOMFICHIER): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

tp3.o : tp3.c

ex1.o : ex1.c ex1.h

ex2.o : ex2.c ex2.h

ex3.o : ex3.c ex3.h

ex4.o : ex4.c ex4.h

ex5.o : ex5.c ex5.h

%.o : %.c
	$(CC) -c $< $(CFLAGS)
