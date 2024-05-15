#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    int duration_seconds;
} VideoMetadata;

typedef struct {
    VideoMetadata* metadata;
    int first;
    int last;
    int size;
    int count;  // Hält die Anzahl der Elemente im Deque
} VideoDeque;

// Initialisiert einen neuen Video-Deque mit `size` Video-Slots
VideoDeque* init_video_deque(int size) {
    if (size <= 0) return NULL;
    VideoDeque* deque = (VideoDeque*) malloc(sizeof(VideoDeque));
    if (!deque) return NULL;
    deque->metadata = (VideoMetadata*) malloc(size * sizeof(VideoMetadata));
    if (!deque->metadata) {
        free(deque);
        return NULL;
    }
    deque->size = size;
    deque->first = 0;   // Startet am Anfang des Arrays
    deque->last = 0;    // Startet am Anfang des Arrays
    deque->count = 0;   // Keine Elemente zu Beginn
    return deque;
}

// Überprüft, ob der Deque leer ist
int is_empty(VideoDeque* deque) {
    return deque->count == 0;
}

// Überprüft, ob der Deque voll ist
int is_full(VideoDeque* deque) {
    return deque->count == deque->size;
}

// Fügt ein Video vorne in den Deque ein
int insert_front(VideoDeque* deque, VideoMetadata videometa) {
    if (!deque || is_full(deque)) {
        return 0; // Deque ist voll
    }
    deque->first = (deque->first - 1 + deque->size) % deque->size;
    deque->metadata[deque->first] = videometa;
    deque->count++;
    return 1;
}

// Fügt ein Video hinten in den Deque ein
int insert_back(VideoDeque* deque, VideoMetadata videometa) {
    if (!deque || is_full(deque)) {
        return 0; // Deque ist voll
    }
    deque->metadata[deque->last] = videometa;
    deque->last = (deque->last + 1) % deque->size;
    deque->count++;
    return 1;
}

// Entfernt ein Video von vorne aus dem Deque
int remove_front(VideoDeque* deque, VideoMetadata* videometa_out) {
    if (!deque || is_empty(deque)) return 0;
    *videometa_out = deque->metadata[deque->first];
    deque->first = (deque->first + 1) % deque->size;
    deque->count--;
    return 1;
}

// Entfernt ein Video von hinten aus dem Deque
int remove_back(VideoDeque* deque, VideoMetadata* videometa_out) {
    if (!deque || is_empty(deque)) return 0;
    deque->last = (deque->last - 1 + deque->size) % deque->size;
    *videometa_out = deque->metadata[deque->last];
    deque->count--;
    return 1;
}

void print_video_deque(VideoDeque* deque) {
    if (is_empty(deque)) {
        printf("Der Deque ist leer.\n");
        return;
    }
    int index = deque->first;
    do {
        VideoMetadata vm = deque->metadata[index];
        printf("\"%s\" (Dauer: %d:%02d)\n", vm.name, vm.duration_seconds / 60, vm.duration_seconds % 60);
        index = (index + 1) % deque->size;
    } while (index != deque->last);
}

// Beispiel für die Verwendung des Deques
int main() {
    VideoDeque* deque = init_video_deque(5);
    // Beispiel-Videos einfügen und entfernen
    return 0;
}
