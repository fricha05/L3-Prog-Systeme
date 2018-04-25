/**
L'exécutable est un listener ou un writer en testant son nom.
Il faut donc faire ln -s exo4mkfifo listener
et ln -s exo4mkfifo writer
et charger l'exécutable soit par ./listener, soit par ./writer
*/

#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

#define FIFO_NAME ("fifo")


int listener()
{
  printf ("I am listener\n");
  unsigned char c;
  int fd;
  ssize_t readsiz;

  fd = open(FIFO_NAME, O_RDONLY);
  while ((readsiz = read(fd, &c, 1)) != -1)
  {
    if (readsiz == 1)
      write(1, &c, 1);
  }
  close(fd);
  return 0;
}

int writer()
{
  printf ("I am writer");
  unsigned char c;
  int fd;
  ssize_t readsiz;

  fd = open(FIFO_NAME, O_WRONLY);
  while ((readsiz = read(0, &c, 1)) != -1)
  {
    c = toupper((int) c);
    write(fd, &c, 1);
  }
  close(fd);
  return 0;
}

int main(int argc, char **argv)
{
  printf("prog: %s\n", argv[0]);
  if (!strncmp(argv[0], "./listener", 10))
  {
    printf("ici\n");
    listener();
  }
  if (!strncmp(argv[0], "./writer", 8))
    writer();
  return 0;
}
