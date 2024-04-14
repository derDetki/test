#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INITSIZE 2
#define MAXSIZE 26

int main (void){

    uint32_t* arr = calloc(INITSIZE, sizeof(uint32_t));

    if(!arr){
        return EXIT_FAILURE;
    }

    puts("Test");

    if (sizeof(calloc)>INITSIZE){
        printf("test2");
    }

    return 0;
}