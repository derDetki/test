#include <stdio.h>

typedef struct {
        char* name;int duration_sec;
    } VideoMetadata;

typedef struct{
        VideoMetadata* metadata;
        int first;
        int last;
    }VideoQueue;

// Adds a video description to the queue
// returns
int enqueue (VideoQueue* video_queue, VideoMetadata videometa);
int dequeue (VideoQueue* video_dequue);
void print_video_queue (VideoQueue* video_queue);



int main (void){

    


    return 0;
}

void print_vido_queue (VideoQueue* video_queue){
    
}

