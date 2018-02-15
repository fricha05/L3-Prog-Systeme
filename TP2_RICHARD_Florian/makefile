NOMFICHIER = exo1
CC = gcc
CFLAGS = -g -O2 -Wall -Wfatal-errors
LDFLAGS = 
LDLIBS = 
OBJ = exo5.o stat.o display_files.o

$(NOMFICHIER): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

exo1.o : exo5.c

display_files.o : display_files.c display_files.h stat.h

stat.o : stat.c stat.h

%.o : %.c
	$(CC) -c $< $(CFLAGS)
