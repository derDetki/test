/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
Otto Detki 29.05.2024
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
Aufgabe:
Schnittmenge zweier verketteter Listen
Schreiben Sie eine Funktion, die die Schnittmenge zweier verketteter Listen berechnet, diese in einer
neuen Liste speichert und dann den Kopf dieser neuen Liste zurückgibt.
• Die Funktion soll die Adresse des Kopfes der neuen Liste zurückgeben.
• Die Listen sind sortiert und enthalten keine Duplikate.
• Die Funktion soll die beiden Listen nicht verändern.
• Alle Listen haben einen Header.
Testen Sie Ihre Imeplementierung mit den folgenden Listen:
List 1: 1 -> 3 -> 4 -> 6 -> 7 -> NULL
List 2: 2 -> 3 -> 4 -> 5 -> 7 -> NULL
Intersection: 3 -> 4 -> 7 -> NULL
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

#include <stdio.h>
#include <stdlib.h>

//Definition eines Listenknotens
struct Node {
    int data; //Daten im Knoten
    struct Node* next; //Zeiger auf den nächsten Knoten
};

// Hilfsfunktion zum Erstellen eines neuen Knotens
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));//Speicher reservieren
    newNode->data = data;//Wert data wird in Element data gesetzt
    newNode->next = NULL;//der aktuelle Konoten ist das letzte Element der Liste
    return newNode;
}

// Funktion zum Hinzufügen eines Knotens am Ende der Liste
void addNodeToEnd(struct Node** headReference, int data) {//headReference = Verweich Kopf
    struct Node* newNode = createNode(data);
    if (*headReference == NULL) {
        *headReference = newNode; // Wenn die Liste leer ist, ist der neue Knoten der Kopf
    } else {
        struct Node* current = *headReference;
        while (current->next != NULL) {
            current = current->next; // Gehe zum letzten Knoten
        }
        current->next = newNode; // Füge den neuen Knoten ans Ende
    }
}

// Funktion zur Schnittmenge zweier Listen
struct Node* getIntersection(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL; // Kopf der neuen Liste für die Schnittmenge
    struct Node* temporary1 = head1;
    struct Node* temporary2 = head2;

    // Durchlaufe beide Listen: die Zahlen in beiden listen müssen der größe anch geordnet in aufsteigender
    // Reihenfolge sortiert sein -> die Funktion vergleicht schrittweise einzelne Werte
    while (temporary1 != NULL && temporary2 != NULL) {
        if (temporary1->data == temporary2->data) {
            // Wenn die Daten gleich sind, füge sie zur Schnittmenge hinzu
            addNodeToEnd(&result, temporary1->data);
            temporary1 = temporary1->next;
            temporary2 = temporary2->next;
        } else if (temporary1->data < temporary2->data) {
            temporary1 = temporary1->next; // Gehe zum nächsten Knoten in Liste 1
        } else {
            temporary2 = temporary2->next; // Gehe zum nächsten Knoten in Liste 2
        }
    }
    return result;
}

// Funktion zum Drucken einer Liste
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    // Ersete Liste erstellen
    struct Node* list1 = NULL;
    addNodeToEnd(&list1, 1);
    addNodeToEnd(&list1, 3);
    addNodeToEnd(&list1, 4);
    addNodeToEnd(&list1, 6);
    addNodeToEnd(&list1, 7);

    // Zweite Liste erstellen
    struct Node* list2 = NULL;
    addNodeToEnd(&list2, 2);
    addNodeToEnd(&list2, 3);
    addNodeToEnd(&list2, 4);
    addNodeToEnd(&list2, 5);
    addNodeToEnd(&list2, 7);

    // Schnittmenge berechnen
    struct Node* intersection = getIntersection(list1, list2);

    // Listen ausdrucken
    printf("List 1: ");
    printList(list1);

    printf("List 2: ");
    printList(list2);

    printf("Intersection: ");
    printList(intersection);

    // Speicher freigeben
    free(list1);
    free(list2);
    free(intersection);

    return 0;
}