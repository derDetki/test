#include <stdio.h>
#define MAX 1000

// Definition der Struktur für den Stack
typedef struct {
    int top;         // Index des obersten Elements im Stack
    int items[MAX];  // Array, das die Elemente des Stacks speichert
} Stack;

// Prototypen der Funktionen, um Compiler-Warnungen zu vermeiden
void push(Stack *s, int new_item);
int pop(Stack *s);

int main() {
    Stack s;          // Stack-Instanz
    s.top = -1;       // Initialisiert 'top' auf -1, was bedeutet, dass der Stack leer ist
    
    // Demonstration des Push- und Pop-Vorgangs
    push(&s, 10);    // Fügt eine Zahl in den Stack ein
    int item = pop(&s); // Entfernt das oberste Element vom Stack
    if (item != -1) {
        printf("Popped: %d\n", item); // Druckt das entfernte Element
    }
    return 0;
}

// Funktion zum Hinzufügen eines Elements in den Stack
void push(Stack *s, int new_item) {
    if (s->top == (MAX - 1)) {
        // Überprüft, ob der Stack voll ist
        printf("Stack is full. Can't push %d\n", new_item);
    } else {
        // Erhöht 'top' und speichert das neue Element
        s->items[++(s->top)] = new_item;
    }
}

// Funktion zum Entfernen des obersten Elements aus dem Stack
int pop(Stack *s) {
    if (s->top == -1) {
        // Überprüft, ob der Stack leer ist
        printf("Stack is empty\n");
        return -1;
    } else {
        // Gibt das oberste Element zurück und verringert 'top'
        return s->items[(s->top)--];
    }
}
