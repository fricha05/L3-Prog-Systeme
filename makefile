# TP4 - Oscar Falmer

NOMFICHIER = TP5
CC = gcc
CFLAGS = -g -O2 -Wall -Werror
LDFLAGS = 
LDLIBS = 
OBJ = main.o code.o

$(NOMFICHIER): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

exo1.o : exo1.c

display_files.o : display_files.c display_files.h stat.h

stat.o : stat.c stat.h

%.o : %.c
	$(CC) -c $< $(CFLAGS)
