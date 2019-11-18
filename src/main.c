#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/pagetable.h"
#include "lib/virtualmemory.h"


int main(int argc, char *argv[]){

    // check if the arguments were passed
    if(argc-1 < NUM_ARGS){
        fprintf(stderr, "Parametros invalidos.\n");
        fprintf(stderr, "Uso: ./tp3virtual <Algoritmo> <Arquivo> <TamanhoPagina> <TamanhoMemoria>\n");
        exit(1);
    }

    // get the chosen page replacement algorithm
    int replacement_alg = get_replacement_algorithm(argv[1]);
    if(replacement_alg == -1){
        fprintf(stderr, "Algoritmo de substituicao nao reconhecido.\nDeve ser um dos seguintes: lru, 2a, fifo, random.\n");
        exit(1);
    }

    char *file_name = argv[2];
    unsigned int page_size = atoi(argv[3]); // value in kbytes
    unsigned int memory_size = atoi(argv[4]); // value in kbytes
    unsigned int frame_number = memory_size / page_size; // number of frames in physical memory
    
    printf("Executando o simulador...\n");
    printf("Arquivo de entrada: %s\n", file_name);
    printf("Tamanho das paginas: %d KB\n", page_size);
    printf("Tamanho da memoria: %d KB\n", memory_size);
    printf("Tecninca de reposicao: %s\n", argv[1]);

    // open file for reading
    FILE* file = fopen(file_name, "r");
    if(file == NULL){
        fprintf(stderr, "Erro ao abrir arquivo %s\n", file_name);
        exit(1);
    }

    // o tamanho da tabela de pagina eh a quantidade de frames da memoria fisica
    pgtbl *page_table = init_pagetable(PGTBL_SIZE);

    int dirty_count = 0;
    int page_faults = 0;
    int free_frames = frame_number;

    unsigned page_shift = get_page_shift(page_size);
    unsigned evicted_page;
    unsigned addr_page;
    unsigned addr;
    char rw;

    //start simulation
    while(!feof(file)){

        fscanf(file, "%x %c", &addr, &rw);

        addr_page = get_addr_page(addr, page_shift);

        if(rw == 'W')
            page_table[addr_page].dirty = 1;

        if(page_table[addr_page].valid)
            continue;

        page_faults++;

        if(free_frames){
            page_table[addr_page].valid = 1;
            page_table[addr_page].ref = 1;
            page_table[addr_page].stamp = time(NULL);
            free_frames--;
            continue;
        }
        
        evicted_page = get_evicted_page(page_table, PGTBL_SIZE, replacement_alg);

        if(page_table[addr_page].dirty)
            dirty_count++;

        page_table[evicted_page].valid = 0;
        page_table[evicted_page].dirty = 0;

        page_table[addr_page].valid = 1;
        page_table[addr_page].ref = 1;
        page_table[addr_page].stamp = time(NULL);
    }

    printf("Paginas lidas: %d\n", page_faults);
    printf("Paginas escritas: %d\n", dirty_count);

    free(page_table);
    fclose(file);

    return 0;
}