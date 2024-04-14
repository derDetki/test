#include <stdio.h>
#include <math.h> // Für die fabs-Funktion

double sqrt_heron(double a, double epsilon);

int main() {
    double y = 0.0; // Die Variablen sollten vom Typ double sein
    double z = 0.0; // für die Quadratwurzelberechnung und die Genauigkeit

    printf("Bitte geben Sie zwei positive Zahlen ein (Zahl und Genauigkeit): \n");
    scanf("%lf", &y);
    scanf("%lf", &z);
   
    if (y <= 0 || z <= 0) {
        printf("Die Eingabe ist ungültig!\n");
    } else {
        double ergebnis = sqrt_heron(y, z); // Ruft die Quadratwurzelfunktion auf
        printf("Das Ergebnis ist: %lf\n", ergebnis); // Gibt das Ergebnis aus
    }

    return 0;
}

double sqrt_heron(double a, double epsilon) {
    double x_n = a; // Startwert für die Iteration, könnte auch ein anderer Wert sein
    double x_next;

    // Schleife, die die Heron-Methode anwendet
    do {
        x_next = 0.5 * (x_n + a / x_n); // Berechnet die nächste Näherung
        // Wiederholt die Schleife, bis die Differenz zwischen zwei aufeinander folgenden
        // Näherungen kleiner als epsilon ist
    } while (fabs(x_next - x_n) > epsilon);

    return x_next; // Gibt die berechnete Näherung zurück
}
