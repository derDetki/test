#include <stdio.h>
#include <stdlib.h>

// Definition des Datenstrukturtyps für einen Knoten in einer doppelt verlinkten Liste.
typedef struct node_s
{
    int value;                // Wert, den der Knoten speichert
    struct node_s *next;      // Zeiger auf den nächsten Knoten in der Liste
    struct node_s *prev;      // Zeiger auf den vorherigen Knoten in der Liste
} node_t; // Der Suffix '_t' ist eine Konvention, um Typedefs zu kennzeichnen.

// Funktionsdeklarationen
node_t *createNode(int value);
node_t *insertIntoList(node_t *list, node_t *node);
node_t *deleteNode(node_t *list, int value);
void printListForwards(node_t *list);
void printListBackwards(node_t *list);

int main(int argc, char const *argv[])
{
    node_t *list = NULL; // Anfangs ist die Liste leer.

    // Knoten zur Liste hinzufügen.
    list = insertIntoList(list, createNode(5));
    list = insertIntoList(list, createNode(7));
    list = insertIntoList(list, createNode(34));
    list = insertIntoList(list, createNode(9));

    // Einen Knoten aus der Liste löschen.
    list = deleteNode(list, 7);

    // Liste von vorne nach hinten ausgeben.
    printListForwards(list);
    // Liste von hinten nach vorne ausgeben.
    printListBackwards(list);

    return 0;
}

// Erstellt einen neuen Knoten und initialisiert ihn.
node_t *createNode(int value)
{
    node_t *newNode = calloc(1, sizeof(node_t)); // Speicherplatz für einen neuen Knoten reservieren und initialisieren.
    if (newNode != NULL)
    {
        newNode->value = value;
        newNode->next = NULL;
        newNode->prev = NULL;
    }

    return newNode; // Adresse des neuen Knotens zurückgeben oder NULL, falls Speicherzuweisung fehlschlägt.
}

// Fügt einen neuen Knoten am Ende der Liste ein.
node_t *insertIntoList(node_t *list, node_t *node)
{
    if (list != NULL)
    {
        node_t *iterator = list; // Anfang der Liste.

        // Suche das Ende der Liste.
        while (iterator->next)
        {
            iterator = iterator->next;
        }

        node->prev = iterator; // Setze den vorherigen Knoten des neuen Knotens.
        iterator->next = node; // Hänge den neuen Knoten ans Ende.
    }
    else
    {
        list = node; // Der neue Knoten ist der erste Knoten, wenn die Liste leer war.
    }

    return list;
}

// Löscht einen Knoten mit einem bestimmten Wert aus der Liste.
node_t *deleteNode(node_t *list, int value)
{
    node_t *iterator = list;

    // Suche den Knoten mit dem gegebenen Wert.
    while (iterator != NULL && iterator->value != value)
    {
        iterator = iterator->next;
    }

    if(iterator == NULL)
    {
        // Der Wert wurde nicht gefunden.
        printf("Element nicht in der Liste\n");
        return list;
    }
    else
    {
        // Der zu löschende Knoten ist gefunden worden.
        if (iterator->prev) // Überprüfung, ob es sich nicht um den ersten Knoten handelt.
            iterator->prev->next = iterator->next;
        if (iterator->next) // Überprüfung, ob es sich nicht um den letzten Knoten handelt.
            iterator->next->prev = iterator->prev;

        free(iterator); // Speicher des Knotens freigeben.
    }

    return list;
}

// Gibt alle Knotenwerte der Liste von vorne nach hinten aus.
void printListForwards(node_t *list)
{
    node_t *iterator = list;

    while (iterator)
    {
        printf("%d ", iterator->value);
        iterator = iterator->next;
    }

    printf("\n");
}

// Gibt alle Knotenwerte der Liste von hinten nach vorne aus.
void printListBackwards(node_t *list)
{
    node_t *iterator = list;

    // Gehe zum letzten Knoten.
    while (iterator->next)
    {
        iterator = iterator->next;
    }

    // Gehe rückwärts durch die Liste.
    
    while (iterator)
    {
        printf("%d ", iterator->value);
        iterator = iterator->prev;
    }

    printf("\n");
}
node_t *deleteNode(node_t *list, int value)
{
    node_t *iterator = list;

    // Suche den Knoten mit dem gegebenen Wert.
    while (iterator != NULL && iterator->value != value)
    {
        iterator = iterator->next;
    }

    if(iterator == NULL)
    {
        // Der Wert wurde nicht gefunden.
        printf("Element nicht in der Liste\n");
        return list;
    }

    // Anpassungen, wenn der Knoten am Anfang oder Ende ist.
    if (iterator->prev)
        iterator->prev->next = iterator->next;
    else
        list = iterator->next; // Aktualisiere den Listenkopf, wenn der erste Knoten gelöscht wird.

    if (iterator->next)
        iterator->next->prev = iterator->prev;

    free(iterator); // Speicher des Knotens freigeben.
    return list;
}
