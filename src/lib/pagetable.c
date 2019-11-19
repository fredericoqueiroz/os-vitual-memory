#include "pagetable.h"

pgtbl* init_pagetable(int pgtbl_size){

    pgtbl *page_table = malloc(pgtbl_size * sizeof(pgtbl));

    //memset(page_table, 0, pgtbl_size * sizeof(pgtbl));

    for(int i=0; i<pgtbl_size; i++){
        page_table[i].valid = 0;
        page_table[i].ref = 1;
        page_table[i].dirty = 0;
    }

    return page_table;
}

//for debugging
void print_pagetable(pgtbl *page_table, int pgtbl_size){
    for(int i=0; i<pgtbl_size; i++){
        printf("%d %d %d\n", page_table[i].valid, page_table[i].ref, page_table[i].dirty);
    }
}


