/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
Otto Detki 28.05.2024
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
Aufgabe:
Eine Rotationsoperation an einer verketteten Liste bewegt die Knoten um eine bestimmte Anzahl
von Schritten nach rechts. Die Rotationsoperation beginnt mit dem Knoten an der Position k. Nach
der Rotation wird der Knoten an der Position länge-k (0-basierter index) der neue Kopf der Liste.
Beispiel:

Eingabe: 1->2->3->4->5->NULL, k = 2
Ausgabe: 4->5->1->2->3->NULL

Implementieren Sie eine Methode, die eine verkettete Liste um k Positionen nach rechts rotiert. Dazu
sollten Sie die Liste temporär in eine zirkuläre Liste umwandeln und dann den Kopf der Liste ent-
sprechend verschieben, bevor Sie die zirkuläre Liste wieder „kappen“. Die Methode sollte die Adresse
des neuen Kopfes zurückgeben. Erweitern Sie dazu ihre bestehende Implementierung einer (doppelt)
verketteten Liste mit Header.
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

#include <stdio.h>
#include <stdlib.h>

// Definition des Listenknotens
struct Node {
    int data;
    struct Node* next;
};

// Funktion neuen Knoten erstellen
struct Node* createNode(int data) {
    struct Node* new_Node = (struct Node*) malloc (sizeof(struct Node));// Speicher reservieren
    new_Node->data = data;// Daten initialisieren
    new_Node->next = NULL;// nächsten Knoten Setzen
    return new_Node;
}

// Funktion, um die Liste zu drucken
void printList(struct Node* start) {
    struct Node* current = start;// Initialisiere current mit dem Startknoten der Liste
    while (current != NULL) {// Solange current nicht NULL ist, iteriere durch die Liste
        printf("%d -> ", current->data);// Drucke die Daten des aktuellen Knotens gefolgt von " -> "
        current = current->next;// Setze current auf den nächsten Knoten
    }
    printf("NULL\n");// Wenn das Ende der Liste erreicht ist, drucke "NULL"
}

// Funktion, um die Liste um k Positionen nach rechts zu drehen
struct Node* rotateRight (struct Node* start, int k) {
    if (!start || k == 0) return start;// Wenn Liste leer oder keine Drehung erforderlich -> beenden

    // Länge der Liste bestimmen
    struct Node* last = start;
    int length = 1;
    while (last->next) {
        last = last->next;
        length++;
    }

    // Bestimme die neue Kopf-Position
    k = k % length; //Diese Zeile reduziert den Wert von k, indem der Rest der Division von k
                    //durch die Länge der Liste (length) berechnet wird.
                    //Beispiel: Angenommen, die Länge der Liste ist 5 (length = 5) und k = 12. Dann wird k % length = 12 % 5 = 2
                    //Diese Lösung Übernommen vom Stackoverflow
    if (k == 0) return start;// keine Rotation notwendig

    // Mache die Liste zu einem Kreis
    last->next = start;

    // Finde die neue Kopf-Position und schneide die Liste ab
    struct Node* newlast = start;
    for (int i = 0; i < length - k - 1; i++) {// -1 wegen newlast -> newstert ist 0!
        newlast = newlast->next;
    }
    struct Node* newstart = newlast->next;
    newlast->next = NULL;//Liste wird abgeschitten

    return newstart;
}

int main() {
    int n, k, value;
    struct Node* start = NULL;
    struct Node* last = NULL;

    printf("Geben Sie die Anzahl der Elemente in der Liste ein: ");
    scanf("%d", &n);

    printf("Geben Sie die Elemente der Liste ein:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        struct Node* new_Node = createNode(value);
        if (!start) {           //wenn Liste leer
            start = new_Node;   //Ersten Knoten erstellen
            last = new_Node;
        } else {
            last->next = new_Node;//sonst neuen Knoten ans Ende anhängen
            last = new_Node;
        }
    }

    printf("Geben Sie die Anzahl der Positionen ein, um die die Liste nach rechts gedreht werden soll: ");
    scanf("%d", &k);

    printf("Ursprüngliche Liste: ");
    printList(start);

    start = rotateRight(start, k);

    printf("Verschobene Liste: ");
    printList(start);

    return 0;
}