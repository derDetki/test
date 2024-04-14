#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define INITSIZE 2
#define MAXSIZE 16

int main(void) {
    int current_size = INITSIZE;
    int *arr = malloc(current_size * sizeof(int));
    if (!arr) {
        perror("Initiierte Malloc fehlgeschlagen");
        return EXIT_FAILURE;
    }

    int input, count = 0;
    printf("Zahl eingeben (um zu beenden, eine nicht Zahl eingeben!):\n");

    // Liest Zahlen von der Standardeingabe ein
    while (scanf("%d", &input) == 1) {
        if (count == current_size) {
            if (current_size == MAXSIZE) {
                break;
            }
            // Verdoppet die Groesse wenn zu klein
            current_size *= 2;
            if (current_size > MAXSIZE) current_size = MAXSIZE;
            int *temp = realloc(arr, current_size * sizeof(int));
            if (!temp) {
                perror("Realloc fehlgeschlagen");
                free(arr);
                return EXIT_FAILURE;
            }
            arr = temp;
        }
        arr[count++] = input;
    }

    if (current_size == MAXSIZE) {
        printf("Maximum array size reached. Outputting numbers in reverse order:\n");
    }

    // Output the numbers in reverse and half the size of the array when half of it is reached
    for (int i = count - 1; i >= 0; --i) {
        printf("%d ", arr[i]);
        if (i == current_size / 2) {
            current_size /= 2;
            int *temp = realloc(arr, current_size * sizeof(int));
            if (!temp) {
                perror("Realloc failed while shrinking");
                free(arr);
                return EXIT_FAILURE;
            }
            arr = temp;
            printf("\\nArray size halved to %d elements.\\n", current_size);
        }
    }

    printf("\\n");
    free(arr);
    return 0;
}
