
// 21.04.2024 Otto Detki
// Ein Programm, das einen String Zeichen für Zeichen ausgibt,
// indem es einen Zeiger entlang des Strings fortschreitend verändert.

#include <stdio.h>
#define SIZE 24

// Diese Funktion erhält einen Zeiger auf char und gibt den Zeiger
// auf das nächste Zeichen zurück.
char* advance_ptr(char* ptr) {
    return ptr + 1; // Rückgabe des Zeigers auf das nächste Zeichen
}

int main(void) {
    char* str = "Ornithorhynchus anatinus";
    for (int i = 0; i < SIZE; i++) {
        printf("%c", *str);     // Gibt das aktuelle Zeichen aus
        str = advance_ptr(str); // Aktualisiert 'str' auf das nächste Zeichen
    }
    printf("\n");

    return 0;
}
