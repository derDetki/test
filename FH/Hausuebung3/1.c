/*
Otto Detki 28.05.2024

Die Aufgabe: 
Erweitern Sie ihre bestehende Implementierung einer (doppelt) verketteten Liste mit Header um eine
Methode, die den Mittelknoten der Liste zurückgibt. Verwenden Sie dazu den Zwei-Zeiger-Ansatz, bei
dem ein langsamer und ein schneller Zeiger verwendet werden, um die Adresse des Mittelknoten zu
finden. In diesem Fall ist schnelle Zeiger doppelt so schnell wie der langsame Zeiger. Falls die Länge
der Liste eine gerade Anzahl ist, geben Sie die Adresse des zweiten Mittelknoten zurück.

ACHTUNG: Basis-Code kopiert aus MOODLE
https://elearn.fh-salzburg.ac.at/mod/resource/view.php?id=47966
Autor Dorian Achim Prill (Kommentare Otto Detki)

Erweiterung des Codes Zeilen 118 bis 138 und
Autor Otto Detki
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 128

// Die Struktur und Daten des Videos werden definiert
typedef struct {
    char name[MAX_NAME_LENGTH];
    int duration_seconds;
} VideoMetadata;

// Definition der Knoten
typedef struct node_s {
    VideoMetadata* video;
    struct node_s* next;
    struct node_s* prev;
} node_t;


// Verwaltung der Liste (Zeiger auf Kopf und Ende, länge der Liste und Gesamtdauer aller Videos)
typedef struct {
    node_t* head;
    node_t* tail;
    int length;
    int duration_seconds;
} VideoPlaylist;

// Funktion zum Erstellen eines neuen Videos
VideoMetadata* new_video(char* name, int duration_seconds) {
    // Speicher für das neue Video allozieren (Zuweisung Speicherplatz)
    VideoMetadata* video = (VideoMetadata*) malloc(sizeof(VideoMetadata));
    if (!video) {
        return NULL; // wir geprüft of Zeiger video Wert NULL hat ((!video) = (video == NULL))
                     // -> ob Speicher richtig reserviert ist
    }
    // Name und Dauer des Videos setzen
    // strncpy Funktion aus Standardbibliothek <string.h>
    strncpy(video->name, name, MAX_NAME_LENGTH);
    video->name[MAX_NAME_LENGTH - 1] = '\0'; // Ende des Strings wird sichergestellt (nullterminiert)
    video->duration_seconds = duration_seconds;
    return video;
}

// Funktion zum Erstellen eines neuen Knotens in der Liste
node_t* new_node(VideoMetadata* video) {
    // Speicher für den neuen Knoten allozieren
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    if (!new_node) {
        return NULL;
    }
    // Video und Zeiger des Knotens setzen
    new_node->video = video;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Funktion zum Ausgeben der gesamten Playlist
void print_playlist(VideoPlaylist* playlist) {
    // Start bei Kopf der Liste
    node_t* current = playlist->head;
    while (current) {
        // Ausgabe von Name und Dauer des aktuellen Videos
        printf("Name: %s\n", current->video->name);
        printf("Duration: %d seconds\n", current->video->duration_seconds);
        // Weiter zum nächsten Knoten
        current = current->next;
    }
}

// Funktion zum Anfügen eines Videos an das Ende der Playlist
// Gibt 1 zurück, wenn erfolgreich, sonst 0
int append(VideoPlaylist* playlist, VideoMetadata* video) {
    // Speicher für neuen Knoten allozieren
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    if (!new_node) {
        return 0;
    }
    // Video und Zeiger des neuen Knotens setzen
    new_node->video = video;
    new_node->next = NULL;
    new_node->prev = playlist->tail;

    // Wenn die Liste nicht leer ist, den neuen Knoten ans Ende hängen
    if (playlist->tail) {
        playlist->tail->next = new_node;
    } else {
        // Wenn die Liste leer ist, neuen Knoten als Kopf setzen
        playlist->head = new_node;
    }
    // Neuen Knoten als Ende der Liste setzen
    playlist->tail = new_node;
    // Länge der Liste und Gesamtdauer aktualisieren
    playlist->length++;
    playlist->duration_seconds += video->duration_seconds;

    return 1;
}

// Code Otto Detki ab hier
// Neue Funktion zum Finden des Mittelknotens der Liste
node_t* find_middle_node(VideoPlaylist* playlist) {
    // Prüfung ob Liste leer ist, in dem Fall return NULL
    if (playlist->head == NULL) {
        return NULL;
    }

    // Zwei Zeiger am Kopf der Liste initialisieren
    node_t* slow = playlist->head;
    node_t* fast = playlist->head;

    // Schneller Zeiger bewegt sich doppelt so schnell wie der langsame Zeiger
    while (fast != NULL && fast->next != NULL) { // bei NULL würde kein nächster Knoten bestehen -> Ende der Liste
        slow = slow->next;
        fast = fast->next->next;
    }

    // Der langsame Zeiger zeigt nun auf den Mittelknoten
    return slow;
} // Implementierung Otto Detki erster Teil endet hier

int main(void) {
    // Speicher für die Playlist allozieren
    VideoPlaylist* playlist = (VideoPlaylist*) malloc(sizeof(VideoPlaylist));
    if (!playlist) {
        return -1;
    }
    // Initialisieren der Playlist
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->length = 0;
    playlist->duration_seconds = 0;

    // Erstellen einiger Videos und Hinzufügen zur Playlist
    VideoMetadata* video1 = new_video("DU GLAUBST NICHT, WAS DIE ECHSENMENSCHEN MIT DIESEN KINDERN MACHT", 601);
    VideoMetadata* video2 = new_video("SIE PROBIERTEN VON DIESER FRUCHT, DANN PASSIERTE dAS!11", 120);
    VideoMetadata* video3 = new_video("Wenn du eine dieser Impfungen erhalten hast, ist DIESER chip in deinem KOERPER111!!!", 1840);

    append(playlist, video1);
    append(playlist, video2);
    append(playlist, video3);

    // Ausgabe der gesamten Playlist
    print_playlist(playlist);

    // Code Otto Detki zweiter Teil ab hier
    // Finden und Ausgeben des Mittelknotens 
    node_t* middle_node = find_middle_node(playlist);

    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("ERWEITERUNG OTTO DETKI\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    if (middle_node) {
        printf("Middle node:\n");
        printf("Name: %s\n", middle_node->video->name);
        printf("Duration: %d seconds\n", middle_node->video->duration_seconds);
    } else {
        printf("\nThe playlist is empty.\n");
    } // Implementierung Otto Detki zweiter Teil endet hier
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");

    return 0;
}