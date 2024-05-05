#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    int value;
    struct node_s *next;
    struct node_s *prev;
} node_t; // for alias; _t for typedef

node_t *createNode(int value);
node_t *insertIntoList(node_t *list, node_t *node);
node_t *deleteNode(node_t *list, int value);
void printListForwards(node_t *list);
void printListBackwards(node_t *list);

int main(int argc, char const *argv[])
{
    // richtig schlechte Liste
    /*node_t n1;
    node_t n2;

    n1.value = 5;
    n2.value = 7;

    n1.next = &n2;
    n2.next = NULL;*/

    node_t *list = NULL;
    list = insertIntoList(list, createNode(5));
    list = insertIntoList(list, createNode(7));
    list = insertIntoList(list, createNode(34));
    list = insertIntoList(list, createNode(9));

    list = deleteNode(list, 7);

    printListForwards(list);
    printListBackwards(list);

    return 0;
}

/// @brief creates a new node
/// @param value initialize value for node
/// @return heap address; null if not successfull
node_t *createNode(int value)
{
    node_t *newNode = calloc(1, sizeof(node_t));
    if (NULL != newNode)
    {
        newNode->value = value;
        newNode->next = NULL;
        newNode->prev = NULL;
    }

    return newNode;
}

/// @brief inserts node in the last place
/// @param list list where to add the node
/// @param node node to add
/// @return list
node_t *insertIntoList(node_t *list, node_t *node)
{
    if (NULL != list)
    {
        node_t *iterator = list;

        // bis wir beim letzten element der liste angekommen sind
        while (iterator->next)
        {
            iterator = iterator->next;
        }

        node->prev = iterator;
        iterator->next = node;
    }
    else
    {
        list = node;
    }

    return list;
}

/// @brief deletes a node from the list
/// @param list list to delete from
/// @param value value of node to delete
/// @return list header
node_t *deleteNode(node_t *list, int value)
{
    node_t *iterator = list;

    //von vorne bis hinten durchgehen
    while (iterator->value != value &&
           iterator != NULL)
    {
        iterator = iterator->next;
    }

    //nicht fuendig geworden
    if(iterator == NULL)
    {
        printf("Element nicht in liste");
        return list;
    }
    //zu loeschende Element gefunden
    else
    {
        //funktioniert nur fuer Elemente in der mitte der liste; vorne und hinten bei naechsten uebung
        node_t* temp = iterator;
        iterator->prev->next = iterator->next;
        iterator->next->prev = iterator->prev;
        free(temp);
    }

    return list;
}

/// @brief prints values of all nodes from the list from the first to last
/// @param list list to print
void printListForwards(node_t *list)
{
    node_t *iterator = list;

    // bis zum Ende der Liste durchlaufen
    while (iterator)
    {
        printf("%d ", iterator->value);
        iterator = iterator->next;
    }

    printf("\n");
}

/// @brief prints values of all nodes from the list from the last to first
/// @param list list to print
void printListBackwards(node_t *list)
{
    node_t *iterator = list;

    // bis wir beim letzten element der liste angekommen sind
    while (iterator->next)
    {
        iterator = iterator->next;
    }

    // bis zum Anfang der Liste durchlaufen
    while (iterator)
    {
        printf("%d ", iterator->value);
        iterator = iterator->prev;
    }

    printf("\n");
}