#include "interface.h"

int commandes(int* stocks, int nbStocks, int* pages, int nbPages){
  char s[BUFSIZ];
  char* err;
  int input;

  var = malloc(sizeof(int)*nbEmplacements);
  for(i = 0; i < nbEmplacements; i++){
    var[i]==0;
  }
  while(1){
    scanf("%c", &s);
    if(strcmp(s, "x") == 0){
      return 0;
    }

    if(strcmp(s, "p") == 0){
      print_tab(stocks, nbStocks);
      print_tab(pages, nbPages);
    }
    strtol(s, &err, 10)
    if(strcmp(err, "\0") == 0){
      perror("erreur de commande");
    }

    input = atoi(s);

    if(input >= 0 && input < nbStocks){
      //gestion et print des tableaux


    }
  }
}
