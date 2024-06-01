#include <stdio.h>

int main() {
    char ime[10];
    printf("Upisi svoje ime\n");
    scanf("%9s", ime); // Limit input to 9 characters to avoid buffer overflow
    printf("Ti se zoves %s\n", ime); // Print the whole string

    return 0;
}
