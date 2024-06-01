/*
Otto Detki 30.05.2024

Die Aufgabe: 
Verkettete Liste in einen Binären Suchbaum umwandeln
Erweitern Sie ihre bestehende Implementierung einer (doppelt) verketteten Liste mit Header um eine
Methode, die die Liste in einen Binären Suchbaum umwandelt. Es muss also jedes Element in der
verketteten Liste in den Binären Suchbaum eingefügt werden. Dabei starten Sie einfach am Anfang
der Liste und fügen jedes Element einzeln ein. Die Methode sollte die Adresse des Wurzelknotens des
so erstellten Binären Suchbaums zurückgeben.

ACHTUNG: Basis-Code kopiert aus MOODLE übernommen
https://elearn.fh-salzburg.ac.at/mod/resource/view.php?id=47966
Autor: Dorian Achim Prill (Kommentare Otto Detki)

Erweiterung des Codes sind in den Kommentaren gekennzeichnet
Autor Otto Detki
*/

#include <stdio.h>
#include <stdlib.h> //für malloc
#include <string.h>//für memcpy

#define MAX_NAME_LENGTH 128

// Definition einer Struktur zur Speicherung von Video-Metadaten
typedef struct {
    char name[MAX_NAME_LENGTH];//Name des Videos (maximale Länge durch MAX_NAME_LENGTH definiert)
    int duration_seconds;//Dauer des Videos in Sekunden
} VideoMetadata;//Der neue Typname ist VideoMetadata

// Definition einer Struktur zur Speicherung eines Knotens einer doppelt verketteten Liste
typedef struct node_s {
    VideoMetadata* video;//Zeiger auf die Metadaten des Videos
    struct node_s* next;//Zeiger auf den nächsten Knoten in der Liste
    struct node_s* prev;//Zeiger auf den vorherigen Knoten in der Liste
} node_t;//Der neue Typname ist node_t

// Definition einer Struktur zur Speicherung einer Video-Playlist
typedef struct {
    node_t* head;//Zeiger auf den ersten Knoten der Playlist
    node_t* tail;//Zeiger auf den letzten Knoten der Playlist
    int length;//Anzahl der Videos in der Playlist
    int duration_seconds;//Gesamtdauer der Videos in der Playlist in Sekunden
} VideoPlaylist;//Der neue Typname ist VideoPlaylist

// CODE IMPLEMENTIERUNG 1 OTTO DETKI ANFANG
//Baum Struktur
typedef struct treeNodeStruct {
    VideoMetadata* video;//Zeiger auf Matadaten des Baumes
    struct treeNodeStruct* left;//linker Knoten (Kind)
    struct treeNodeStruct* right;//linker Knoten (Kind)
} tree_node_type;//Neuer Typname tree_node_typeype
// CODE IMPLEMENTIERUNG 1 OTTO DETKI ENDE   


// Erstellt ein neues Video und gibt einen Zeiger darauf zurück
VideoMetadata* new_video(char* name, int duration_seconds) {
    VideoMetadata* video = (VideoMetadata*) malloc(sizeof(VideoMetadata));
    if (!video) {//Kontrolle ob Speicher mit malloc reserviert ist
        return NULL;
    }
    memcpy(video->name, name, MAX_NAME_LENGTH); //memcpy: Diese Funktion wird verwendet,
                                                //um den name-String in die name-Charakter-Array von
                                                //VideoMetadata zu kopieren. Dies ist notwendig, da
                                                //name ein char* ist und VideoMetadata.name ein
                                                //char[MAX_NAME_LENGTH] ist. -> Stackoverflow
    video->duration_seconds = duration_seconds;
    return video;
}

// Erstellt einen neuen Knoten für die doppelt verkettete Liste und gibt einen Zeiger darauf zurück
node_t* new_node(VideoMetadata* video) {
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    if (!new_node) {
        return NULL;
    }
    new_node->video = video;//Das Video wird dem Video-Feld des neuen Konotens zugewiesen
    new_node->next = NULL;  //Setzt den Zeiger auf den nächsten Knoten auf NULL, da der Knoten
                            //derzeit nicht mit einem anderen Knoten verbunden ist
    new_node->prev = NULL;  //Setzt den Zeiger auf den vorherigen Knoten auf NULL, da der Knoten
                            //derzeit nicht mit einem anderen Knoten verbunden ist.
    return new_node;
}

// Druckt die gesamte Playlist aus
void print_playlist(VideoPlaylist* playlist) {
    node_t* current = playlist->head;
    while (current) {
        printf("Name: %s\n", current->video->name);
        printf("Duration: %d\n", current->video->duration_seconds);
        current = current->next;
    }
}

// Hängt ein Video an das Ende der Playlist an
// Gibt 1 zurück, wenn erfolgreich, sonst 0
int append(VideoPlaylist* playlist, VideoMetadata* video) {
    // Neuen Knoten mit dem Video erstellen
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    if (!new_node) {
        return 0; // Speicherzuweisung fehlgeschlagen
    }
    new_node->video = video;
    new_node->next = NULL;
    new_node->prev = playlist->tail;

    // Wenn die Playlist leer ist, setze Kopf und Schwanz auf den neuen Knoten
    if (playlist->head == NULL) {
        playlist->head = new_node;
        playlist->tail = new_node;
    } else {
        // Wenn die Playlist nicht leer ist, setze tail->next auf den neuen Knoten, setze new_node->prev auf tail, setze tail auf den neuen Knoten
        playlist->tail->next = new_node;
        playlist->tail = new_node;
    }

    // Aktualisiere die Länge und Gesamtdauer der Playlist
    playlist->length++;
    playlist->duration_seconds += video->duration_seconds;
    return 1; // Erfolg
}

// CODE IMPLEMENTIERUNG 2 OTTO DETKI ANFANG
// Hilfsfunktion zum Einfügen eines Videos in den binären Suchbaum
tree_node_type* insert_into_tree(tree_node_type* root, VideoMetadata* video) {
    // Wenn der Baum leer ist, gebe einen neuen Baumknoten zurück
    if (root == NULL) {
        tree_node_type* new_tree_node = (tree_node_type*) malloc(sizeof(tree_node_type));//Speicher für einen neuen Baumknoten reservieren
        if (!new_tree_node) {//Wenn die Speicherzuweisung fehlschlägt -> NULL 
            return NULL;
        }
        //Den neuen Knoten initialisieren
        new_tree_node->video = video;
        new_tree_node->left = NULL;
        new_tree_node->right = NULL;
        return new_tree_node;   //Gebe den neuen Knoten zurück, der als neuer Wurzelknoten oder Kindknoten dient
    }                           //rekursiv ;-)

    // Andernfalls rekursiv den Baum hinunter gehen
    if (strcmp(video->name, root->video->name) < 0) {   //Vergleicht die Namen der Videos,
                                                        //erster Buxhstabe ASCII Wert, um die Einfügeposition zu
                                                        //finden
        root->left = insert_into_tree(root->left, video);//Füge das Video in den linken Teilbaum ein
    } else {
        root->right = insert_into_tree(root->right, video);//Füge das Video in den rechten Teilbaum ein
    }

    // Gebe den (unveränderten) Knotenzeiger zurück
    return root;
}
// CODE IMPLEMENTIERUNG 2 OTTO DETKI ENDE


// CODE IMPLEMENTIERUNG 3 OTTO DETKI ANFANG
// Konvertiert die Playlist in einen binären Suchbaum
tree_node_type* convert_to_tree(VideoPlaylist* playlist) {
    // Starte mit einem leeren Baum
    tree_node_type* root = NULL;//Initialisierung eines leeren Baums
    node_t* current = playlist->head;//Initialisierung des aktuellen Knotens

    // Durchlaufe die verkettete Liste und füge jedes Video in den Baum ein
    while (current) {
        root = insert_into_tree(root, current->video);
        current = current->next;
    }

    // Gebe die Wurzel des Baumes zurück
    return root;
}
// CODE IMPLEMENTIERUNG 3 OTTO DETKI ENDE

// CODE IMPLEMENTIERUNG 4 OTTO DETKI ANFANG
// Hilfsfunktion zum Inorder-Ausdruck des Baunms (Inorder -> damit die Knoten in 
// aufsteigenden Reihenfolge sortiert angezeigt werden)
void print_tree_inorder(tree_node_type* root) {
    if (root == NULL) {
        return;
    }
    print_tree_inorder(root->left);
    printf("Name: %s, Duration: %d\n", root->video->name, root->video->duration_seconds);
    print_tree_inorder(root->right);
}
// CODE IMPLEMENTIERUNG 4 OTTO DETKI ENDE


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// AUFGABE 5 AB HIER
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// Hilfsfunktion zum Erstellen eines neuen Knotens der verketteten Liste aus Video-Metadaten
node_t* new_node_from_video(VideoMetadata* video) {
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    if (!new_node) {
        return NULL;
    }
    new_node->video = video;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Hilfsfunktion zum Hinzufügen eines Knotens am Ende der verketteten Liste
void append_to_list(VideoPlaylist* playlist, node_t* new_node) {
    if (playlist->head == NULL) {//Überprüfung ob Liste leer ist
        playlist->head = new_node;//Initialisierung der Playlist, wenn sie leer ist
        playlist->tail = new_node;// -||-
    } else {
        //Hinzufügen des Knotens am Ende der Playlist, wenn sie nicht leer ist
        playlist->tail->next = new_node;//Verbinden des aktuellen Endes der Playlist mit dem neuen Knoten
        new_node->prev = playlist->tail;//Verbinden des neuen Knotens mit dem vorherigen Endknoten
        playlist->tail = new_node;//Aktualisieren des Endes der Playlist auf den neuen Knoten.
        //Der tail-Zeiger der Playlist wird auf den neuen Knoten gesetzt. Dies bedeutet,
        //dass der neue Knoten jetzt das Ende der Playlist ist.
        /*
        playlist->tail -> [current_tail_node] -> NULL

        playlist->tail -> [current_tail_node] -> [new_node] -> NULL
                     ^                   ^
                     |                   |
                  NULL <--------------- [new_node]->prev
        */
    }
    //Aktualisieren der Länge und Gesamtdauer der Playlist
    playlist->length++;
    playlist->duration_seconds += new_node->video->duration_seconds;
}

// Inorder-Traversierung des Baums und Umwandlung in eine verkettete Liste
void inorder_to_list(tree_node_type* root, VideoPlaylist* playlist) {
    //Wenn der aktuelle Knoten NULL ist, beende die Rekursion
    if (root == NULL) {
        return;
    }
    //Rekursive Inorder-Traversierung des linken Teilbaums
    inorder_to_list(root->left, playlist);
    //Erstellen eines neuen Knotens der verketteten Liste aus den Video-Metadaten des aktuellen Baumknotens
    node_t* new_node = new_node_from_video(root->video);
    append_to_list(playlist, new_node);//Hinzufügen des neuen Knotens am Ende der verketteten Liste
    inorder_to_list(root->right, playlist);//Rekursive Inorder-Traversierung des rechten Teilbaums
/*
VISUELLE DARSTELLUNG:

        [D]
       /   \
    [B]     [F]
   /   \   /   \
 [A]   [C] [E] [G]



NULL <----------- [A] <----------> [B] <----------> [C] <----------> [D] <----------> [E] <----------> [F] <----------> [G] -> NULL
             prev         next  prev         next  prev         next  prev         next  prev         next  prev         next
                     |                    |                    |                    |                    |                    |                   
                    [A]                  [B]                  [C]                  [D]                  [E]                  [F] 
                    next                 next                 next                 next                 next                 next
                     |                    |                    |                    |                    |                    |                   
                  [B]                [C]                [D]                [E]                [F]                [G]
                  prev                prev                prev                prev                prev                prev
                     |                    |                    |                    |                    |                    |                   
                    [A]                  [B]                  [C]                  [D]                  [E]                  [F]

*/

}

// Methode zur Umwandlung eines binären Suchbaums in eine verkettete Liste
VideoPlaylist* tree_to_list(tree_node_type* root) {
    // Speicher für eine neue Playlist-Struktur allozieren
    VideoPlaylist* playlist = (VideoPlaylist*) malloc(sizeof(VideoPlaylist));
    if (!playlist) {
        return NULL;// Rückgabe NULL, falls die Speicherzuweisung fehlschlägt
    }
    playlist->head = NULL;// Kopf der Playlist auf NULL setzen
    playlist->tail = NULL;// Ende der Playlist auf NULL setzen
    playlist->length = 0;// Länge der Playlist auf 0 setzen
    playlist->duration_seconds = 0;// Gesamtdauer der Playlist auf 0 setzen

    inorder_to_list(root, playlist);//Playlist durch eine Inorder-Traversierung des Baums füllen
    return playlist;//Rückgabe -> gefüllte Playlist
}

// Hauptfunktion zum Testen der Umwandlung
int main(void) {
    // Initialisiere die Playlist
    VideoPlaylist* playlist = (VideoPlaylist*) malloc(sizeof(VideoPlaylist));
    if (!playlist) {
        return -1;
    }
    // Zeiger und Variablen werden auf NULL/0 gesetzt
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->length = 0;
    playlist->duration_seconds = 0;

    // Erstelle einige Videos
    VideoMetadata* video1 = new_video("DU GLAUBST NICHT, WAS DIE ECHSENMENSCHEN MIT DIESEN KINDERN MACHEN", 601);
    VideoMetadata* video2 = new_video("SIE PROBIERTEN VON DIESER FRUCHT, DANN PASSIERTE DAS!11", 120);
    VideoMetadata* video3 = new_video("Wenn du eine dieser Impfungen erhalten hast, ist DIESER Chip in deinem KOERPER!!!", 1840);
    VideoMetadata* video4 = new_video("JESUS'S SANDALEN GEFUNDEN!", 72);
    VideoMetadata* video5 = new_video("PUTIN LEIDET AN AKUTER VERSTOPFUNG", 43);
    VideoMetadata* video6 = new_video("ANZEICHEN VON LEBEN AUF DER SONNE", 664);
    VideoMetadata* video7 = new_video("MONTY PYTHONS SETZEN SICH FÜR FUSSPILZ EIN", 981);
    VideoMetadata* video8 = new_video("NARZISTISCHE GIRAFFEN GEHEN WENIGER OFT IN KRANKENSTAND", 870);
    VideoMetadata* video9 = new_video("LUGNER FÜR NOBELPREIS NOMINIERT", 329);

    // Hänge Videos an die Playlist an
    append(playlist, video1);
    append(playlist, video2);
    append(playlist, video3);
    append(playlist, video4);
    append(playlist, video5);
    append(playlist, video6);
    append(playlist, video7);
    append(playlist, video8);
    append(playlist, video9);

    // Drucke die Playlist aus
    printf("Playlist:\n");
    print_playlist(playlist);

    // Konvertiere die Playlist in einen Baum
    tree_node_type* bst_root = convert_to_tree(playlist);

    // Drucke den Baum in Inorder-Reihenfolge aus
    printf("\nBinary Search Tree (in-order):\n");
    print_tree_inorder(bst_root);

    // Konvertiere den Baum zurück in eine Playlist
    VideoPlaylist* restored_playlist = tree_to_list(bst_root);

    // Drucke die wiederhergestellte Playlist aus
    printf("\nRestored Playlist:\n");
    print_playlist(restored_playlist);

    return 0;
}