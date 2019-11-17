#ifndef __PAGETABLE_H_
#define __PAGETABLE_H_

typedef struct {
    int valid;          // page valid, set if in memory
    int ref;            // page reference, set if page has been referenced
    int dirty;          // dirty 'bit', set if modified 
    unsigned int frame; // physical frame holding page
    unsigned int stamp; // last time the page has been referenced
} pgtbl_entry;

#endif