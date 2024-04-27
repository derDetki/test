// 21.04.2024 Otto 
// Ein Programm, das mithilfe der Heron-Methode die Quadratwurzel
// einer positiven Zahl bis zu einer angegebenen Genauigkeit berechnet.

#include <stdio.h>
#include <math.h> // Für die "fabs"-Funktion

double sqrt_heron_recursive(double a, double epsilon, double x_n); // Rekursive Hilfsfunktion 
double sqrt_heron(double a, double epsilon); // Hilfs-Funktion

int main() {
    double zahl = 0.0, genauigkeit = 0.0;

    printf("Bitte geben Sie eine positive Zahl, von der die Quadratwurzel ermittelt werden soll ein und die gewünschte Genauigkeit: \n");
    scanf("%lf %lf", &zahl, &genauigkeit);

    if (zahl <= 0 || genauigkeit <= 0) {
        printf("Die Eingabe ist ungültig. Bitte positive Zahlen eingeben!\n");
    } else {
        double ergebnis = sqrt_heron(zahl, genauigkeit);
        printf("Das Ergebnis ist: %lf\n", ergebnis);
    }

    return 0;
}
//  Der weitere Code wurde mit Hilfe vom Herrn T. Anders am 21.04.24 erstellt
// Wrapper-Funktion, die die Rekursion initiiert
double sqrt_heron(double a, double epsilon) {
    return sqrt_heron_recursive(a, epsilon, a);
}

// Rekursive Funktion, die das Heron-Verfahren implementiert
double sqrt_heron_recursive(double a, double epsilon, double x_n) {
    double x_next = 0.5 * (x_n + a / x_n); // Berechnet die nächste Näherung
    if (fabs(x_next - x_n) < epsilon) { // Prüft, ob die Genauigkeit erreicht ist
                                        // fabs erstellt den Betrag der Zahl -> immer positiver Wert
        return x_next; // Wenn ja, beende die Rekursion
    } else {
        return sqrt_heron_recursive(a, epsilon, x_next); // Rekursion mit dem neuen Wert
    }
}
