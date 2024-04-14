#include <stdio.h>
#include <stdlib.h>

// Definieren der Startgröße und der maximalen Größe des Arrays
#define INITSIZE 2
#define MAXSIZE 16

int main(void) {
    // Initialisiere die aktuelle Größe des Arrays mit dem Wert von INITSIZE
    int current_size = INITSIZE;
    // Allokiere Speicher für das Array mit der Startgröße
    int *arr = malloc(current_size * sizeof(int));
    if (!arr) {
        perror("Initial malloc failed");
        return EXIT_FAILURE;
    }

    int input, count = 0;
    printf("Enter numbers (to end input, enter a non-numeric value):\n");

    // Lese Zahlen von der Standardeingabe, bis eine nicht numerische Eingabe erfolgt
    while (scanf("%d", &input) == 1) {
        // Wenn das Array voll ist, überprüfe die Größe und vergrößere wenn nötig
        if (count == current_size) {
            // Wenn die maximale Größe bereits erreicht ist, höre auf zu lesen
            if (current_size == MAXSIZE) {
                break;
            }
            // Verdopple die Größe des Arrays
            current_size *= 2;
            printf("Speicher wird vergrößert!");
            // Achte darauf, dass die maximale Größe nicht überschritten wird
            if (current_size > MAXSIZE) current_size = MAXSIZE;
            // Versuche, den Speicherplatz für das Array zu vergrößern
            int *temp = realloc(arr, current_size * sizeof(int));
            if (!temp) {
                perror("Realloc failed");
                free(arr);
                return EXIT_FAILURE;
            }
            arr = temp;
        }
        // Speichere die eingegebene Zahl im Array
        arr[count++] = input;
    }

    // Wenn die maximale Größe erreicht ist, informiere den Benutzer
    if (current_size == MAXSIZE) {
        printf("Maximum array size reached. Outputting numbers in reverse order:\n");
    }

    // Gib die Zahlen in umgekehrter Reihenfolge aus
    for (int i = count - 1; i >= 0; --i) {
        printf("%d ", arr[i]);
        // Wenn der halbe Weg erreicht ist, verkleinere das Array
        if (i == current_size / 2) {
            // Halbiere die aktuelle Größe des Arrays
            current_size /= 2;
            // Versuche, den Speicherplatz für das Array zu verkleinern
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
    // Gib den allokierten Speicher frei
    free(arr);
    return 0;
}
