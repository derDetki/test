#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10 // Adjust size as needed

typedef struct {
    char title[100];
    int length;
} VideoMetadata;

typedef struct {
    VideoMetadata videos[QUEUE_SIZE];
    int first;
    int last;
    int count;
} VideoQueue;

void enqueue(VideoQueue *queue, VideoMetadata video) {
    if (queue->count >= QUEUE_SIZE) {
        printf("Queue is full!\n");
        return;
    }
    queue->videos[queue->last] = video;
    queue->last = (queue->last + 1) % QUEUE_SIZE;
    queue->count++;
}

VideoMetadata dequeue(VideoQueue *queue) {
    VideoMetadata video = {.title = "", .length = -1};
    if (queue->count <= 0) {
        printf("Queue is empty!\n");
        return video;
    }
    video = queue->videos[queue->first];
    queue->first = (queue->first + 1) % QUEUE_SIZE;
    queue->count--;
    return video;
}

void print_video_queue(VideoQueue *queue) {
    printf("Video Queue:\n");
    int index = queue->first;
    for (int i = 0; i < queue->count; i++) {
        printf("Title: %s, Length: %d seconds\n", queue->videos[index].title, queue->videos[index].length);
        index = (index + 1) % QUEUE_SIZE;
    }
}

int main(void) {
    VideoQueue queue = {.first = 0, .last = 0, .count = 0};

    // Test the implementation
    VideoMetadata video1 = {.title = "Jesus war eine Frau ", .length = 120};
    VideoMetadata video2 = {.title = "Bruce Lee lebt ", .length = 300};
    VideoMetadata video3 = {.title = "Herpes genetalis heilt Krebs! ", .length = 1800};

    enqueue(&queue, video1);
    enqueue(&queue, video2);
    enqueue(&queue, video3);

    print_video_queue(&queue);

    printf("\nDequeuing: %s\n", dequeue(&queue).title);
    print_video_queue(&queue);

    return 0;
}
