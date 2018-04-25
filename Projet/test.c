#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char* err;
  printf(" %d \n",strtol(argv[1], &err, 10));
  printf("%s \n", err);
  printf("%d\n", strcmp(argv[1], err));
  return 0;
}
