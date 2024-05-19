#include <stdio.h> // Einbinden der Standard-Input-Output-Headerdatei für die Ein-/Ausgabe-Funktionen

int main() { // Hauptfunktion des Programms
    int zahlen[10], i, j, temp; // Deklaration eines Arrays für zehn Zahlen und Variablen für Schleifen und temporäre Speicherung

    printf("Bitte geben Sie zehn Zahlen ein:\n"); // Aufforderung an den Benutzer, zehn Zahlen einzugeben
    for (i = 0; i < 10; i++) { // Schleife zum Einlesen der zehn Zahlen
        scanf("%d", &zahlen[i]); // Liest eine Zahl und speichert sie im Array
    }

    // Sortieren der Zahlen mittels Bubble Sort
    for (i = 0; i < 9; i++) { // Äußere Schleife, die durchläuft bis das Array sortiert ist
        for (j = 0; j < 9 - i; j++) { // Innere Schleife, vergleicht benachbarte Elemente
            if (zahlen[j] > zahlen[j + 1]) { // Wenn das aktuelle Element größer ist als das nächste
                temp = zahlen[j]; // Tauscht die Elemente
                zahlen[j] = zahlen[j + 1]; // Verschiebt das kleinere Element nach links
                zahlen[j + 1] = temp; // Verschiebt das größere Element nach rechts
            }
        }
    }

    printf("Zahlen in aufsteigender Reihenfolge:\n"); // Gibt eine Nachricht aus, dass die Zahlen sortiert sind
    for (i = 0; i < 10; i++) { // Schleife, die durch das Array geht
        printf("%d ", zahlen[i]); // Druckt jedes Element des sortierten Arrays
    }

    return 0; // Beendet das Programm
}