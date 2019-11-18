#include "virtualmemory.h"

int get_replacement_algorithm(char *name){
    if(strcmp("lru", name) == 0)
        return LRU;
    if(strcmp("2a", name) == 0)
        return SC;
    if(strcmp("fifo", name) == 0 )
        return FIFO;
    if(strcmp("random", name) == 0 )
        return RANDOM;
    else
        return -1;
}

unsigned get_page_shift(unsigned int page_size){
    unsigned s = 0;
    unsigned tmp = page_size * 1024; //page size in bytes
    while (tmp>1){
        tmp = tmp>>1;
        s++;
    }
    return s;
}

unsigned get_addr_page(unsigned addr, unsigned page_shift){
    return addr >> page_shift;
}

unsigned get_evicted_page(pgtbl* page_table, int replacement_alg){
    if(replacement_alg == LRU)
        return random_alg(page_table);
    if(replacement_alg == SC)
        return random_alg(page_table);
    if(replacement_alg == FIFO)
        return random_alg(page_table);
    if(replacement_alg == RANDOM)
        return random_alg(page_table);
    else
        return random_alg(page_table);
}

unsigned random_alg(pgtbl* page_table){
    unsigned evicted_page;
    srand(time(NULL));

    while(1){
        evicted_page = (random() % PGTBL_SIZE);
        if(page_table[evicted_page].valid)
            return evicted_page;
    }
}

unsigned fifo_alg(pgtbl* page_table){
    
}