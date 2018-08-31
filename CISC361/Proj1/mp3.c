/*
James Skripchuk
CISC361
Assignment 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

int main(){
    
    struct SongDoubleLinkedList* list = malloc(sizeof(struct SongDoubleLinkedList));
    //printf("%d", list->head==NULL);
    struct SongNode* song = malloc(sizeof(struct SongNode));
    song->song_title = "A";
    struct SongNode* song2 = malloc(sizeof(struct SongNode));
    song2->song_title = "B";
    struct SongNode* song3 = malloc(sizeof(struct SongNode));
    song3->song_title = "C";
    struct SongNode* song4 = malloc(sizeof(struct SongNode));
    song4->song_title = "D";
    //song->song_artist = "Maxo";
    //song->release_date ="A while ago";
    //song->runtime=4*60;

    appendSong(list, song);
    appendSong(list, song2);
    appendSong(list, song3);
    appendSong(list, song4);
    printBackwards(list);
    //printSong(song);
    return 0;
}

void appendSong(struct SongDoubleLinkedList* list, struct SongNode* song){
    //If our list is empty, the new node is both the head and the tail
    if(list->head == NULL){
        list->head = song;
        list->tail = song;
    }else{
        //Current tail points to new song
        list->tail->next = song;
        //New song points behind to current tail
        song->prev = list->tail;
        //New tail is the new song
        list->tail = song;
    }
}

void deleteArtist(struct SongDoubleLinkedList* list, char* artist){
    //Four Cases
    //1) List is Empty
    //2) Artist is at the HEAD
    //3) Artist is in the middle
    //4) Artist is at the TAIL

    struct SongNode* current = list->head;

    //First see if the list is empty
    if(current != NULL){

    }
}

void printForwards(struct SongDoubleLinkedList* list){
    struct SongNode* current = list->head;
    while(current != NULL){
        printSong(current);
        current=current->next;
    }
}

void printBackwards(struct SongDoubleLinkedList* list){
    struct SongNode* current = list->tail;
    while(current != NULL){
        printSong(current);
        current=current->prev;
    }
}

//Formats song into a string to print to stdout
void printSong(struct SongNode* song){
    char* header = "----------";
    char buffer[512];
    sprintf(buffer, "%s\nSong Title: %s\nArtist: %s\nRelease: %s\nLength: %d\n%s\n", 
    header,
    song->song_title,
    song->song_artist,
    song->release_date,
    song->runtime,
    header);
    printf(buffer);
}