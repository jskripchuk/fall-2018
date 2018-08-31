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
    
    
    //printSong(song);
    test();
    return 0;
}

void test(){
    struct SongDoubleLinkedList* list = malloc(sizeof(struct SongDoubleLinkedList));
    //printf("%d", list->head==NULL);
    struct SongNode* song = malloc(sizeof(struct SongNode));
    song->song_title = "A";
    song->song_artist = "1";
    struct SongNode* song2 = malloc(sizeof(struct SongNode));
    song2->song_title = "B";
    song2->song_artist = "0";
    struct SongNode* song3 = malloc(sizeof(struct SongNode));
    song3->song_title = "C";
    song3->song_artist = "0";
    struct SongNode* song4 = malloc(sizeof(struct SongNode));
    song4->song_title = "D";
    song4->song_artist = "1";
    //song->song_artist = "Maxo";
    //song->release_date ="A while ago";
    //song->runtime=4*60;

    appendSong(list, song);
    appendSong(list, song2);
    appendSong(list, song3);
    appendSong(list, song4);
    printForwards(list);
    printf("####################\n");
    deleteArtist(list, "1");
    printBackwards(list);
    printf("######################\n");
    deleteArtist(list, "0");
    printForwards(list);

    free(list);


    //free(song);f
    //free(list);
    //deleteList(list);
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

//Safely deletes and frees the memory for the whole list
void deleteList(struct SongDoubleLinkedList* list){
    struct SongNode* current = list->head;
    while(current != NULL){
        struct SongNode* to_delete = current;
        current=current->next;
        free(to_delete);
    }
    free(list);
}

void deleteArtist(struct SongDoubleLinkedList* list, char* artist){
    //Four Cases
    //1) List is Empty
    //2) Artist is at the HEAD
    //3) Artist is in the middle
    //4) Artist is at the TAIL

    struct SongNode* current = list->head;

    //First see if the list is empty
    while(current != NULL){
        struct SongNode* next = current->next;
        //If the strings are the same, we delete the node
        if(strcmp(artist, current->song_artist)==0){
            //Artist is at the head
            if(current == list->head){
                list->head = current->next;
                if(current-> next != NULL){
                    list->head->prev = NULL;
                }else{
                    //If we are at the head and the next item is NULL
                    //This is also the tail of the list
                    list->tail = list->head;
                }
                free(current);
            }else if(current == list->tail){
                list->tail = list->tail->prev;
                list->tail->next = NULL;
                free(current);
            }else{
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
            }
        }

        current = next;
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