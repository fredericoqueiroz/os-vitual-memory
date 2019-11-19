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
        return lru_alg(page_table);
    if(replacement_alg == SC)
        return sc_alg(page_table);
    if(replacement_alg == FIFO)
        return fifo_alg(page_table);
    if(replacement_alg == RANDOM)
        return random_alg(page_table);
    else
        return lru_alg(page_table);
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
    unsigned evicted_page = 0;
    double diference, max_diference = 0.0;

    time_t actual_time = time(NULL);
    //time(&actual_time);

    for(int i=0; i<PGTBL_SIZE; i++){
        diference = difftime(actual_time, page_table[i].stamp);
        if(diference > max_diference && page_table[i].valid){
            evicted_page = i;
            max_diference = diference;
        }
    }
    return evicted_page;
}

unsigned lru_alg(pgtbl* page_table) {

    int evicted_page = -1;
    for (int i = 0; i < PGTBL_SIZE; i++)
    {
        if (page_table[i].valid)
        {
            if (evicted_page == -1 || difftime(page_table[evicted_page].last_recently, page_table[i].last_recently) > 0)
            {
                evicted_page = i;
            }
        }
    }
    return evicted_page;
}

unsigned sc_alg(pgtbl* page_table)
{
    int evicted_page = 0, i = 0, selected_page = 0;
    time_t actual_time = time(NULL);
    double diff = 0.0;

    for (i = 0; i < PGTBL_SIZE; i++)
    {
        page_table[i].second_chance = 0;
    }

    while (1)
    { //gives second chance
        for (i = 0; i < PGTBL_SIZE; i++)
        { //finds page
            if (page_table[i].valid && !page_table[i].second_chance && difftime(actual_time, page_table[i].stamp) > diff)
            {
                selected_page = i;
                diff = difftime(actual_time, page_table[i].stamp);
            }
        }

        if (page_table[selected_page].ref == 0)
        {
            evicted_page = selected_page;
            break;
        }
        else
        {
            page_table[selected_page].ref = 0;
            page_table[selected_page].second_chance = 1;
        }
    }
    return evicted_page;
}