// 25.04.2024 Otto 
// Ein Programm, das Zahlen aus einer Datei liest, ihre Summe berechnet und
// das Ergebnis in einer anderen Datei speichert.

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Dateizeiger für die Eingabe- und Ausgabedatei deklarieren
    FILE *eingabeDatei, *ausgabeDatei;
    int zahl, summe = 0;
    char zeile[100]; // Nimmt an, dass eine Zeile nicht mehr als 99 Zeichen + Nullterminator hat

    // Eingabedatei zum Lesen öffnen
    eingabeDatei = fopen("Zahlen0.txt", "r");
    // Ausgabedatei zum Schreiben öffnen
    ausgabeDatei = fopen("Summen.txt", "w");

    // Überprüfe, ob die Dateien erfolgreich geöffnet wurden
    if (eingabeDatei == NULL || ausgabeDatei == NULL) {
        perror("Fehler beim Oeffnen der Dateien"); // Standardisierte Fehlermeldung
        return EXIT_FAILURE; // Beende das Programm mit einem Fehlercode
    }



    // Lies Zeilen aus der Eingabedatei bis zum Ende der Datei
    while (fgets(zeile, sizeof(zeile), eingabeDatei) != NULL) { // Zeile wird gelesen
        // Überprüfe, ob die aktuelle Zeile eine Zahl ist
        if (sscanf(zeile, "%d", &zahl) == 1) { // Zahl wird ausgelesen
            summe += zahl; // Zahl zur Summe hinzufügen
        }
        // Überprüfe, ob die aktuelle Zeile eine Leerzeile ist
        else if (zeile[0] == '\n') {
            // Wenn bisher Zahlen gelesen wurden, schreibe die Summe in die Ausgabedatei
            if (summe > 0) {
                fprintf(ausgabeDatei, "%d\n", summe);
                summe = 0; // Setze die Summe zurück für die nächste Gruppe
            }
        }
    }



    // Überprüfe, ob am Ende noch eine Summe vorhanden ist
    if (summe > 0) {
        fprintf(ausgabeDatei, "%d\n", summe); // Schreibe die letzte Summe in die Ausgabedatei
    }

    // Schließe beide Dateien
    fclose(eingabeDatei);
    fclose(ausgabeDatei);

    return EXIT_SUCCESS; // Beende das Programm erfolgreich
}
