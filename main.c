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
/* 
    // check if the arguments were passed
    if(argc-1 != NUM_ARGS){
        printf("Parametros invalidos.\n");
        exit(1);
    } */

    // get the chosen page replacement algorithm
    int alg = get_replacement_algorithm(argv[1]);
    if(alg == -1){
        printf("Algoritmo de substituicao nao reconhecido.\nDeve ser um dos seguintes: lru, 2a, fifo, random.\n");
        exit(1);
    }
    else
        printf("Algorithm: %d\n", alg);

    return 0;
}