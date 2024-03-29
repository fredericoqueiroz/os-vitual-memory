#ifndef __VIRTUALMEMORY_H_
#define __VIRTUALMEMORY_H_

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "pagetable.h"

#define NUM_ARGS 4

enum ALG{LRU, SC, FIFO, RANDOM};

int get_replacement_algorithm(char *name);

unsigned get_page_shift(unsigned int page_size);

unsigned get_addr_page(unsigned addr, unsigned page_shift);

unsigned get_evicted_page(pgtbl* page_table, int replacement_alg);

// replacement algorithms 
unsigned random_alg(pgtbl* page_table);

unsigned fifo_alg(pgtbl* page_table);

unsigned lru_alg(pgtbl* page_table);

unsigned sc_alg(pgtbl* page_table);

#endif