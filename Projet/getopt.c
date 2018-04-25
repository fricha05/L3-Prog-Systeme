int test_int(char* argv){
  int i = atoi(argv);
  int* staocks, pages, dates;
  if(i == 0){
    perror("erreur taille");
    exit(EXIT_FAILURE);
  }
  return i;
}

void options(int argc, char const* argv[]){//nom à changer
  int o;
  int index = 0;

  //tests options
  if(o = getopt(argc, argv, "s:v:") != "s"){
    perror("erreur ordre/syntaxe options");
    exit(EXIT_FAILURE);
  }
  if(o = getopt(argc, argv, "s:v:") != "v"){
    perror("erreur ordre/syntaxe options");
    exit(EXIT_FAILURE);
  }

  //tests nombres de pages valides
  if(test_int(argv[2]) > test_int(argv[4])){
    perror("le nombre de pages doit être supérieur au nombre d'emplacements");
    exit(EXIT_FAILURE);
  }

  //création tableau
  if((stocks = malloc(sizeof(int) * argv[2])) == NULL){
    perror("malloc stocks error");
    exit(EXIT_FAILURE);
  }
  if((pages = malloc(sizeof(int) * argv[4]) == NULL){
    perror("malloc pages error");
    exit(EXIT_FAILURE);
  }

  if(dates = malloc(sizeof(int)*argv[2]) == NULL){
    perror("malloc dates error");
    exit(EXIT_FAILURE);
  }
  //appel au gestionnaire interface
  commande(stocks, argv[2], pages, argv[4]);
}
