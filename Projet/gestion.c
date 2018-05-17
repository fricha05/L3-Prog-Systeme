#include "gestion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_pages(int* tab, int n){
  int i;
  print("[");
  for(i = 0; i < n; i++){
    print("%d ; ", tab[i]);
  }
  print("]\n");
}

void print_stocks(Slot* stocks, int n){
    int i;
    print("[");
    for(i = 0; i < n; i++){
      print("%d ; ", num.stocks[i]);
    }
    print("]\n");
}

void minus_cpt(Slot* stock,int nb_Slot, int limit){
    int i;
    for(i = 0; i< nb_Slot -1;i++){
        if(num.Slot[i] == -2) return;
        if(cpt.Slot[i] >= limit) cpt.Slot[i] = cpt.Slot[i] -1;
    }
    return;
}

void add_pages(int new_num, int* pages, int nb_pages){
    int i;
    for(i=0; i<nb_pages-1; i++){
        if(pages[i] == -1) pages[i] = new_pages;
    }
}

int verif_pages(int num, int* pages, int nb_pages){
    int i;
    for(i = 0; i<nb_pages-1; i++){
        if (pages[i] == num) {
            return i;
        }
    }
    return -1;
}

void add_Slot(int new_num, Slot* stock,int* pages,int nb_Slot, int nb_pages){
    int i;
    int limit;
    int least_used;
    int fetch;
    int temp;
    least_used = -1;
    for(i=0;i<N;i++){
        switch(num.stock[i]){
            case (-2):
                num.stock[i] = new_num;
                cpt.stock[i] = nb_Slot;
                minus_cpt(Slot, nb_Slot, nb_Slot);
                return;

            case(new_num):
                limit = cpt.stock[i];
                cpt.stock[i] = nb_Slot;
                minus_cpt(Slot, nb_Slot, limit);
                return;
        }
        if(cpt.stock[i] == 0) least_use = i;
    }
    fetch = verif_pages(new_num, pages, nb_pages);
    if(fetch != -1){
        temp = pages[fetch];
        pages[fetch] = num.stock[least_used];
        num.stock[least_used] = temp;
        cpt.stock[least_used] = nb_Slot;
        minus_cpt(Slot, nb_Slot, nb_Slot);
        return;
    }

    add_pages(num.stock[least_used], pages, nb_pages);
    num.stock[least_used] = new_num;
    cpt.stock[least_used] = nb_Slot;
    minus_cpt(Slot, nb_Slot_, nb_Slot);
    return;


    //tableau de dates -> 0,1,2,3...n -> trouver la case à 0 -> envoyer dans
    //pages -> remplacer le 0 par n et -1 sur le reste

}
