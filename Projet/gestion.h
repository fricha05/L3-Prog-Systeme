#ifndef gestion
#define gestion


typedef struct Slots{
    int cpt;
    int num;
}Slot;

void print_pages(int* tab, int n);
void print_stocks(Slot* stocks, int n);
void minus_cpt(Slot* stock,int nb_Slot, int limit);
void add_pages(int new_num, int* pages, int nb_pages);
int verif_pages(int num, int* pages, int nb_pages);
int get_least_used(Slot* stock, int nb_slot);
void add_Slot(int new_num, Slot* stock,int* pages,int nb_Slot, int nb_pages);

#endif
