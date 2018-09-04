#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

//Appends a SongNode song to the tail of Song to a DoubleLinkedList list
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

//Safely deletes and frees from memory all all of the nodes and then frees the list pointer
void deleteList(struct SongDoubleLinkedList* list){
    struct SongNode* current = list->head;
    while(current != NULL){
        struct SongNode* to_delete = current;
        current=current->next;
        freeSong(to_delete);
    }
    free(list);
}

//Safely frees all of the data in the node and then the node itself
void freeSong(struct SongNode* song){
    free(song->song_artist);
    free(song->song_title);
    free(song->release_date);
    free(song->runtime);
    free(song);
}

//Given a char* artist it will delete all the nodes in the List list that has have the artist
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
                freeSong(current);
            }else if(current == list->tail){
                list->tail = list->tail->prev;
                list->tail->next = NULL;
                freeSong(current);
            }else{
                current->prev->next = current->next;
                current->next->prev = current->prev;
                freeSong(current);
            }
        }

        current = next;
    }
}