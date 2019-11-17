#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ARGS 4

enum ALG{LRU, SC, FIFO, RANDOM};

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


int main(int argc, char *argv[]){

    // check if the arguments were passed
    if(argc-1 < NUM_ARGS){
        fprintf(stderr, "Parametros invalidos.\n");
        fprintf(stderr, "Uso: ./tp3virtual <Algoritmo> <Arquivo> <TamanhoPagina> <TamanhoMemoria>");
        exit(1);
    }

    // get the chosen page replacement algorithm
    int alg = get_replacement_algorithm(argv[1]);
    if(alg == -1){
        printf("Algoritmo de substituicao nao reconhecido.\nDeve ser um dos seguintes: lru, 2a, fifo, random.\n");
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
    if(file = NULL){
        fprintf(stderr, "Erro ao abrir arquivo %s\n", file_name);
        exit(1);
    }


    // o tamanho da tabela de pagina eh a quantidade de frames da memoria fisica

    //start simulation
        

    return 0;
}