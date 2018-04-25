#include <stdio.h>
#include <stlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  if(argc != 5){
    perror("il faut 5 arguments");
    exit(EXIT_FAILURE);
  }

  //appel à getopt qui appelle interface qui appelle gestion
  exit(EXIT_SUCCESS);
}
