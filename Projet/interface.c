#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>


void commandes(Slot* stocks, int nbStocks, int* pages, int nbPages){

  char* err;
  char s[BUFSIZ];
  int input,i;

  for(i = 0; i < nbStocks; i++){
    stocks[i].cpt= -1;
    stocks[i].num= -2;
  }

  for(i = 0; i < nbPages; i++){
      pages[i]= -1;
  }

  while(1){
    scanf("%s\n", s);

    // s = read(0, buf, strlen(buf));
    if(strcmp(s, "x") == 0){
      exit(EXIT_SUCCESS);
    }
    if(strcmp(s, "p") == 0){
      print_stocks(stocks, nbStocks);
      print_pages(pages, nbPages);
    }
    // strtol(s, &err, 10);
    // if(strcmp(err, "\0") == 0){
    //   perror("erreur de commande");
    //   exit(EXIT_FAILURE);
    // }

    input = atoi(s);
    if(input >= 0 && input < nbPages){
        add_Slot(input, stocks, pages, nbStocks, nbPages);
    }
    else{
        perror("mauvaise entrée");
    }
  }
  return;
}
