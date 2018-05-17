#include "gestion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_pages(int* tab, int n){
  int i;
  printf("[");
  for(i = 0; i < n; i++){
    printf(" %d ", tab[i]);
  }
  printf("]\n");
}

void print_stocks(Slot* stocks, int n){
    int i;
    printf("[");
    for(i = 0; i < n; i++){
      printf(" %d;%d ", stocks[i].num, stocks[i].cpt);
    }
    printf("]\n");
}

void minus_cpt(Slot* stock,int nb_Slot, int limit){
    int i;

    for(i = 0; i< nb_Slot -1;i++){
        if(stock[i].num == -2) return;
        if(stock[i].cpt >= limit){
            stock[i].cpt--;
        }
    }
    return;
}

void add_pages(int new_num, int* pages, int nb_pages){
    int i;
    for(i=0; i<nb_pages-1; i++){
        if(pages[i] == -1) pages[i] = new_num;
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

int get_least_used(Slot* stock, int nb_slot){
    int i;
    for(i=0; i<nb_slot; i++){
        if(stock[i].cpt == 1) return i;
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
    for(i=0;i<nb_Slot;i++){
        if(stock[i].num == -2){
            stock[i].num = new_num;
            stock[i].cpt = nb_Slot;
            minus_cpt(stock, nb_Slot, nb_Slot);
            return;
        }
        else if(stock[i].num == new_num){
            limit = stock[i].cpt;
            // printf("limit : %d\n", limit);
            stock[i].cpt = nb_Slot;
            minus_cpt(stock, nb_Slot, limit);
            return;
        }
        // if(stock[i].cpt == 0) least_used = i;
    }
    least_used = get_least_used(stock, nb_Slot);
    printf("least_used is %d\n", least_used);
    fetch = verif_pages(new_num, pages, nb_pages);
    if(fetch != -1){
        temp = pages[fetch];
        pages[fetch] = stock[least_used].num;
        stock[least_used].num = temp;
        stock[least_used].cpt = nb_Slot;
        minus_cpt(stock, nb_Slot, nb_Slot);
        return;
    }
    add_pages(stock[least_used].num, pages, nb_pages);
    stock[least_used].num = new_num;
    stock[least_used].cpt = nb_Slot;
    minus_cpt(stock, nb_Slot, nb_Slot);
    return;


    //tableau de dates -> 0,1,2,3...n -> trouver la case à 0 -> envoyer dans
    //pages -> remplacer le 0 par n et -1 sur le reste

}
