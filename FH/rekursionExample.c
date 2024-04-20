#include <stdio.h>

void printNumbers(int n){
    if (n == 1){
        printf("%d ", n);
        return;
    }
    printNumbers(n-1);
    printf("%d ", n);
}

int main (int argc, char const *argv[])
{
    printNumbers(10);
    return 0;
}