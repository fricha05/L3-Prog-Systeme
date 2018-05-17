NOMFICHIER = simvm
CC = colorgcc
CFLAGS = -g -O2 -Wall -Wfatal-errors
LDFLAGS =
LDLIBS =
OBJ = main.o getopt.o interface.o gestion.o

$(NOMFICHIER): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)



main.o: main.c getopt.o interface.o gestion.o

getopt.o: getopt.c getopt.h interface.h gestion.h

interface.o: interface.c interface.h gestion.h

gestion.o: gestion.c gestion.h

%.o : %.c
	$(CC) -c $< $(CFLAGS)
