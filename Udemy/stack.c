#include <stdio.h>  // Standardbibliothek für Input/Output-Funktionen
#define SIZE 10     // Makrodefinition, setzt die Größe des Stacks auf 10

// Definition einer Struktur für den Stack
typedef struct {
    int item[SIZE];  // Array von Ganzzahlen, Speicher des Stacks
    int top;         // Ganzzahl, zeigt auf das oberste Element im Stack
} Stack;

// Prototypen der Funktionen zur Verwaltung des Stacks
void init(Stack *);
void push(Stack *, int);
int pop(Stack *);

// Implementierung der push-Funktion
void push(Stack *sp, int value){
    if (sp->top == SIZE - 1){  // Überprüft, ob der Stack voll ist
        printf("Stack overflow\n");  // Gibt eine Fehlermeldung aus, wenn der Stack voll ist
        return;  // Beendet die Funktion frühzeitig
    }
    
    sp->top++;  // Bewegt den top-Index nach oben
    sp->item[sp->top] = value;  // Speichert den übergebenen Wert am neuen top-Index
}

// Implementierung der pop-Funktion
int pop(Stack *sp){
    if (sp->top == -1){  // Überprüft, ob der Stack leer ist
        printf("Stack Underflow\n");  // Gibt eine Fehlermeldung aus, wenn der Stack leer ist
        return -9999;  // Gibt einen Fehlerwert zurück
    }
    int value;  // Deklariert eine lokale Variable zur Aufnahme des zu entfernenden Werts
    value = sp->item[sp->top];  // Holt den Wert vom aktuellen top-Index
    sp->top--;  // Verringert den top-Index, "entfernt" das oberste Element
    return value;  // Gibt den entfernten Wert zurück
}

// Implementierung der init-Funktion
void init(Stack *sp){
    sp->top = -1;  // Setzt den top-Index auf -1, was einen leeren Stack anzeigt
}

// Hauptfunktion des Programms
int main() {
    Stack s1, s2;  // Deklaration zweier Stack-Variablen
    init(&s1);  // Initialisiert den ersten Stack
    init(&s2);  // Initialisiert den zweiten Stack
    push(&s1, 100);  // Fügt 100 zum ersten Stack hinzu
    push(&s1, 200);  // Fügt 200 zum ersten Stack hinzu

    push(&s2, 10);  // Fügt 10 zum zweiten Stack hinzu
    push(&s2, 20);  // Fügt 20 zum zweiten Stack hinzu

    printf("deleted from s1: %d\n", pop(&s1));  // Entfernt das oberste Element von s1 und druckt es
    printf("deleted from s1: %d\n", pop(&s1));  // Entfernt das nächste oberste Element von s1 und druckt es

    printf("deleted from s2: %d\n", pop(&s2));  // Entfernt das oberste Element von s2 und druckt es
    printf("deleted from s2: %d\n", pop(&s2));  // Entfernt das nächste oberste Element von s2 und druckt es
        
    return 0;  // Beendet das Programm mit dem Rückgabewert 0
}