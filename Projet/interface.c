#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int commandes(Slot* stocks, int nbStocks, int* pages, int nbPages){
  char s[BUFSIZ];
  char* err;
  int input;

  for(i = 0; i < nbStocks; i++){
    cpt.stocks[i]= -1;
    num.stocks[i]= -2;
  }

  for(i = 0; i < nbPages; i++){
      pages[i]= -1;
  }

  while(1){
    scanf("%c", &s);
    if(strcmp(s, "x") == 0){
      exit(EXIT_SUCCESS);
    }

    if(strcmp(s, "p") == 0){
      print_stocks(stocks, nbStocks);
      print_pages(pages, nbPages);
    }
    strtol(s, &err, 10)
    if(strcmp(err, "\0") == 0){
      perror("erreur de commande");
      exit(EXIT_FAILURE);
    }

    input = atoi(s);

    if(input >= 0 && input < nbStocks){
        add_Slot(input, stocks, pages, nbStocks, nbPages);
    }
    else{
        perror("mauvaise entrée");
        exit(EXIT_FAILURE);
    }
  }
}
