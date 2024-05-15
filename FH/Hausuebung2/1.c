#include <stdio.h>
#include <stdlib.h>

// Makrodefinitionen für die anfängliche und maximale Größe des Stapels
#define INITIAL_SIZE 10
#define MAX_SIZE 1000

// Strukturdefinition für den Stapel
typedef struct {
    int *items;      // Zeiger auf das Array von Stack-Elementen
    int top;         // Index des nächsten freien Elements im Stapel
    int capacity;    // Aktuelle Kapazität des Stapels
} Stack;

// Funktionendeklarationen
Stack* init();                          // Initialisiert einen neuen Stapel
void push(Stack *s, int item);          // Fügt ein Element zum Stapel hinzu
int pop(Stack *s);                      // Entfernt und gibt das oberste Element zurück
int top(Stack *s);                      // Gibt das oberste Element zurück, ohne es zu entfernen
int is_full(Stack *s);                  // Prüft, ob der Stapel voll ist
int is_empty(Stack *s);                 // Prüft, ob der Stapel leer ist
void resize(Stack *s, int new_size);    // Ändert die Größe des Stapels

// Initialisiert einen neuen Stapel und gibt einen Zeiger darauf zurück
Stack* init() {
    Stack *s = malloc(sizeof(Stack));       // Speicher für den Stapel reservieren
    s->items = malloc(sizeof(int) * INITIAL_SIZE); // Speicher für die Stapel-Elemente reservieren
    s->capacity = INITIAL_SIZE;
    s->top = 0;
    return s;
}

// Fügt ein neues Element zum Stapel hinzu
void push(Stack *s, int item) {
    if (is_full(s)) {                   // Wenn der Stapel voll ist, verdoppeln wir die Kapazität
        resize(s, s->capacity * 2);
    }
    s->items[s->top++] = item;          // Element hinzufügen und top inkrementieren
}

// Entfernt das oberste Element vom Stapel und gibt es zurück
int pop(Stack *s) {
    if (is_empty(s)) {                  // Wenn der Stapel leer ist, Fehlermeldung zurückgeben
        return -1;
    }
    int item = s->items[--s->top];      // Oberstes Element entfernen und top dekrementieren
    if (s->top > INITIAL_SIZE && s->top <= s->capacity / 4) { // Wenn der Stapel zu einem Viertel gefüllt ist, Kapazität halbieren
        resize(s, s->capacity / 2);
    }
    return item;
}

// Gibt das oberste Element des Stapels zurück, ohne es zu entfernen
int top(Stack *s) {
    if (is_empty(s)) {                  // Wenn der Stapel leer ist, Fehlermeldung zurückgeben
        return -1;
    }
    return s->items[s->top - 1];
}

// Prüft, ob der Stapel voll ist
int is_full(Stack *s) {
    return s->top == s->capacity;
}

// Prüft, ob der Stapel leer ist
int is_empty(Stack *s) {
    return s->top == 0;
}

// Ändert die Größe des Stapels
void resize(Stack *s, int new_size) {
    if (new_size > MAX_SIZE) {          // Verhindern, dass die Größe über MAX_SIZE hinausgeht
        new_size = MAX_SIZE;
    }
    if (new_size < INITIAL_SIZE) {      // Verhindern, dass die Größe unter INITIAL_SIZE fällt
        new_size = INITIAL_SIZE;
    }
    s->items = realloc(s->items, sizeof(int) * new_size); // Speicher neu zuweisen
    s->capacity = new_size;
}

// Hauptprogramm zum Testen des Stapels
int main() {
    Stack *s = init();
    push(s, 1);
    push(s, 2);
    push(s, 3);
    printf("Top item: %d\n", top(s)); // Sollte 3 ausgeben
    pop(s);
    pop(s);
    pop(s);
    pop(s); // Sollte -1 ausgeben, da der Stapel leer ist
    printf("Stack empty: %d\n", is_empty(s)); // Sollte 1 ausgeben, da der Stapel leer ist

    free(s->items); // Speicher für Stapel-Elemente freigeben
    free(s);        // Speicher für den Stapel freigeben
    return 0;
}
