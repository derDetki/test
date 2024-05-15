#include <stdio.h>
#include <stdlib.h>

// Struktur eines Knotens in der verketteten Liste
struct Node {
    int data;            // Daten, die der Knoten speichert
    struct Node* next;   // Zeiger auf den nächsten Knoten
};

// Struktur des Stacks
struct Stack {
    struct Node* top;    // Zeiger auf das oberste Element des Stacks
};

// Funktion zur Initialisierung des Stacks
void init(struct Stack* stack) {
    stack->top = NULL;   // Der Stack ist anfangs leer, daher ist top NULL
}

// Funktion, um ein Element auf den Stack zu legen
void push(struct Stack* stack, int value) {
    // Erstellen eines neuen Knotens
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Speicherzuweisung fehlgeschlagen\n");
        return;
    }
    newNode->data = value;         // Setzen des Wertes des Knotens
    newNode->next = stack->top;    // Der neue Knoten zeigt auf den bisherigen top-Knoten
    stack->top = newNode;          // Der neue Knoten wird zum top-Knoten des Stacks
    printf("%d wurde auf den Stack gelegt\n", value);
}

// Funktion, um das oberste Element vom Stack zu nehmen
int pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Der Stack ist leer\n");
        return -1;  // Rückgabewert im Fehlerfall
    }
    struct Node* temp = stack->top;   // Temporärer Zeiger auf den obersten Knoten
    int poppedValue = temp->data;     // Speichern des Wertes des obersten Knotens
    stack->top = stack->top->next;    // Der top-Zeiger wird auf den nächsten Knoten gesetzt
    free(temp);                       // Speicher des entfernten Knotens freigeben
    return poppedValue;
}

// Funktion, um das oberste Element des Stacks zu sehen, ohne es zu entfernen
int top(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Der Stack ist leer\n");
        return -1;  // Rückgabewert im Fehlerfall
    }
    return stack->top->data;
}

// Hauptfunktion zur Demonstration der Stack-Operationen
int main() {
    struct Stack stack;  // Deklaration eines Stacks
    init(&stack);        // Initialisierung des Stacks

    push(&stack, 10);    // Elemente auf den Stack legen
    push(&stack, 20);
    push(&stack, 30);

    printf("Oberstes Element ist: %d\n", top(&stack));  // Oberstes Element anzeigen

    printf("Entferntes Element ist: %d\n", pop(&stack));  // Element vom Stack nehmen
    printf("Entferntes Element ist: %d\n", pop(&stack));
    printf("Entferntes Element ist: %d\n", pop(&stack));

    printf("Oberstes Element ist: %d\n", top(&stack));  // Oberstes Element anzeigen

    return 0;
}
