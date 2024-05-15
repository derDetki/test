#include <stdio.h>
#include <stdlib.h>

// Struktur für Videometadaten, die jetzt auch eine Priorität enthält
typedef struct {
    char* name;               // Name des Videos
    int duration_seconds;     // Dauer des Videos in Sekunden
    int priority;             // Priorität des Videos, kleinere Zahlen bedeuten höhere Priorität
} VideoMetadata;

// Struktur für die Warteschlange
typedef struct {
    VideoMetadata* metadata;  // Dynamisches Array von Videometadaten
    int first;                // Index des ersten Elements in der Warteschlange
    int last;                 // Index des letzten Elements in der Warteschlange
    int size;                 // Maximale Größe der Warteschlange
} VideoQueue;

// Funktion zum Initialisieren der Video-Warteschlange
VideoQueue* init_video_queue(int size);

// Funktion zum Hinzufügen eines Videos in die Warteschlange basierend auf der Priorität
int enqueue(VideoQueue* video_queue, VideoMetadata videometa);

// Funktion zum Entfernen eines Videos aus der Warteschlange
int dequeue(VideoQueue* video_queue, VideoMetadata* videometa_out);

// Funktion zum Ausgeben der Video-Warteschlange
void print_video_queue(VideoQueue* video_queue);

int main(void) {
    VideoQueue* video_queue = NULL;
    VideoMetadata video = {"", 0, 0};
    VideoMetadata videometa[] = {
        {"Video A", 120, 5},
        {"Video B", 300, 2},
        {"Video C", 150, 1},
        {"Video D", 240, 3},
        {"Video E", 360, 2}
    };

    // Initialisiert eine neue Warteschlange mit Platz für 5 Videos
    video_queue = init_video_queue(5);

    // Fügt mehrere Videos mit verschiedenen Prioritäten in die Warteschlange ein
    for (long unsigned int i = 0; i < sizeof(videometa)/sizeof(VideoMetadata); i++) {
        if (enqueue(video_queue, videometa[i])) {
            printf("Enqueued video: %s\n", videometa[i].name);
        } else {
            printf("Failed to enqueue video: %s\n", videometa[i].name);
        }
    }
    
    // Druckt den aktuellen Inhalt der Warteschlange
    print_video_queue(video_queue);

    // Entfernt alle Videos aus der Warteschlange und gibt sie aus
    for (long unsigned int i = 0; i < sizeof(videometa)/sizeof(VideoMetadata); i++) {
        if (dequeue(video_queue, &video)) {
            printf("Dequeued video: %s\n", video.name);
        } else {
            printf("Failed to dequeue video\n");
        }
    }

    return 0;
}

// Initialisiert die Warteschlange mit einer bestimmten Größe
VideoQueue* init_video_queue(int size) {
    if (size <= 0) {
        return NULL;
    }
    VideoQueue* video_queue = (VideoQueue*) malloc(sizeof(VideoQueue));
    if (video_queue == NULL) {
        return NULL;
    }
    video_queue->metadata = (VideoMetadata*) malloc(size * sizeof(VideoMetadata));
    if (video_queue->metadata == NULL) {
        free(video_queue);
        return NULL;
    }
    video_queue->size = size;
    video_queue->first = 0;
    video_queue->last = 0;
    return video_queue;
}

// Fügt ein Video basierend auf seiner Priorität in die Warteschlange ein
int enqueue(VideoQueue* video_queue, VideoMetadata videometa) {
    if (!video_queue) {
        return 0;
    }
    int nextLast = (video_queue->last + 1) % video_queue->size;
    if (nextLast == video_queue->first) {
        return 0; // Warteschlange ist voll
    }
    
    int insertPos = video_queue->last;
    while (insertPos != video_queue->first) {
        int prevPos = (insertPos - 1 + video_queue->size) % video_queue->size;
        if (video_queue->metadata[prevPos].priority <= videometa.priority) {
            break;
        }
        video_queue->metadata[insertPos] = video_queue->metadata[prevPos];
        insertPos = prevPos;
    }
    video_queue->metadata[insertPos] = videometa;
    video_queue->last = nextLast;
    return 1;
}

// Entfernt das älteste Element aus der Warteschlange
int dequeue(VideoQueue* video_queue, VideoMetadata* videometa_out) {
    if (!video_queue || video_queue->first == video_queue->last) {
        return 0; // Warteschlange ist leer
    }
    *videometa_out = video_queue->metadata[video_queue->first];
    video_queue->first = (video_queue->first + 1) % video_queue->size;
    return 1;
}

// Gibt den aktuellen Inhalt der Warteschlange aus
void print_video_queue(VideoQueue* video_queue) {
    for (int i = video_queue->first; i != video_queue->last; i = (i + 1) % video_queue->size) {
        printf("\"%s\" (Duration: %d:%02d) Priority: %d\n", video_queue->metadata[i].name, video_queue->metadata[i].duration_seconds / 60, video_queue->metadata[i].duration_seconds % 60, video_queue->metadata[i].priority);
    }
}
