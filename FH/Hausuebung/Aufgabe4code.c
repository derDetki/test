// 26.04.2024 Otto Detki
// Ein Programm, das Zahlen aus zwei Dateien liest, sie vergleicht und
// das Ergebnis in einer neuen Datei dokumentiert, wobei "L" für eine
// größere Zahl in der ersten Datei und "R" für eine größere in der zweiten steht.


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Überprüfen, ob genau zwei Argumente übergeben wurden (Programmname + 2 Dateinamen)
    if(argc != 3) {
        // Wenn nicht, Ausgabe einer Fehlermeldung und Beendigung des Programms mit Fehlercode 1
        fprintf(stderr, "Verwendung: %s <datei1> <datei2>\n", argv[0]);
        return 1;
    }

    // Erste Datei zum Lesen zu öffnen
    FILE *file1 = fopen(argv[1], "r");
    // Zweite Datei zum Lesen zu öffnen
    FILE *file2 = fopen(argv[2], "r");

    // Überprüfen, ob beide Dateien erfolgreich geöffnet wurden
    if(file1 == NULL || file2 == NULL) {
        // Fehlermeldung ausgeben, wenn eine der Dateien nicht geöffnet werden konnte
        fprintf(stderr, "Fehler beim Öffnen der Dateien.\n");
        // Freigabe von Ressourcen, wenn nötig, und Programmende mit Fehlercode
        if(file1 != NULL) fclose(file1);
        if(file2 != NULL) fclose(file2);
        return 1;
    }

    // Ausgabedatei Schreiben
    FILE *outputFile = fopen("vergleichErgebnis.txt", "w"); // Datei öffnen
    // Überprüfen, ob die Ausgabedatei erfolgreich geöffnet wurde
    if(outputFile == NULL) {
        // Fehlermeldung ausgeben, wenn die Ausgabedatei nicht erstellt werden konnte
        fprintf(stderr, "Fehler beim Erstellen der Ausgabedatei.\n");
        // Freigabe von Ressourcen und Programmende mit Fehlercode
        fclose(file1);   // ;-) clesn code
        fclose(file2);   //  -||-
        return 1;
    }

    // Initialisierung der Variablen zum Speichern der gelesenen Zahlen
    int num1, num2;
    // Schleife läuft, bis das Ende einer der Dateien erreicht ist
    while(fscanf(file1, "%d", &num1) != EOF && fscanf(file2, "%d", &num2) != EOF) {
        // Vergleich der gelesenen Zahlen und Schreiben des Ergebnisses in die Ausgabedatei
        if(num1 > num2) {
            fputc('L', outputFile);  // L für links, wenn die Zahl in der ersten Datei größer ist
        } else if(num2 > num1) {
            fputc('R', outputFile);  // R für rechts, wenn die Zahl in der zweiten Datei größer ist
        }
        fputc('\n', outputFile);  // Zeilenumbruch hinzufügen nach jeder geschriebenen Ausgabe
    }

    // Schließen aller geöffneten Dateien und Freigabe von Ressourcen
    fclose(file1);
    fclose(file2);
    fclose(outputFile);

    // Ende des Programms mit Erfolgsmeldung
    return 0;
}


// zum Ausfühern: ./Aufgabe4 Zahlen1.txt Zahlen2.txt