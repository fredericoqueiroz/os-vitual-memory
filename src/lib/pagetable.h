#ifndef __PAGETABLE_H_
#define __PAGETABLE_H_

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PGTBL_SIZE 2097152

// page table entry
typedef struct {
    int valid;          // page valid, set if in memory
    int ref;            // page reference, set if page has been referenced
    int dirty;          // dirty 'bit', set if modified 
    time_t stamp; // last time the page has been referenced
} pgtbl;

pgtbl* init_pagetable(int pgtbl_size);

//for debugging
void print_pagetable(pgtbl *page_table, int pgtbl_size);

#endif