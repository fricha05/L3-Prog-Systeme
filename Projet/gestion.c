#include "gestion.h"

void print_tab(int* tab, int n){
  int i;
  print("[");
  for(i = 0; i < n; i++){
    print("%d ; ", tab[i]);
  }
  print("]\n");
}

void load_page(int* stocks, int* pages, int* date){
}
