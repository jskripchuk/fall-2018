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
    int exit_program = 0;
    struct SongDoubleLinkedList* songList = malloc(sizeof(struct SongDoubleLinkedList));
    struct SongNode* song;

    while(exit_program != 1){
        int choice;
        printf("\nList Operations\n");
        printf("===============\n");
        printf("1. Add an MP3 to the list\n");
        printf("2. Delete MP3s based on artist\n");
        printf("3. Print List Forwards\n");
        printf("4. Print List Backwards\n");
        printf("5. Exit\n");
        printf("Choice: ");
        
        
        int BUFFERSIZE = 128;
        char buffer[BUFFERSIZE];
        int len;

        //Somehow eats the newline?
        //https://stackoverflow.com/questions/20150845/c-program-skips-fgets
        scanf("%d",&choice);
        getchar();
        //choice = 1;
        switch(choice){
            case 1:
                song =  malloc(sizeof(struct SongNode));
                printf("\nEnter the song's title: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                song->song_title = (char*)malloc(len);
                strcpy(song->song_title,buffer);

                printf("Enter the song's artist: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                song->song_artist = (char*)malloc(len);
                strcpy(song->song_artist,buffer);    

                printf("Enter the song's release date: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                song->release_date = (char*)malloc(len);
                strcpy(song->release_date,buffer);            
                //printf("\n Enter the song's runtime (in seconds): ");
                int* runtime = malloc(sizeof(int));
                printf("Enter the song's runtime (in seconds): ");
                scanf("%d", runtime);
                song->runtime = runtime;

                appendSong(songList, song);
                //printSong(song);
                //printf("\nEnter the song's artist: ");
                
                break;
            case 2:
                printf("\nEnter the artist's who's songs you want to delete: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                char* artist = (char*)malloc(len);
                strcpy(artist,buffer);
                printf("%s", artist);
                deleteArtist(songList, artist);
                free(artist);
                break;
            case 3:
                printForwards(songList);
                break;
            case 4:
                printBackwards(songList);
                break;
            case 5:
                free(songList);
                exit_program = 1;
                break;
        }
    }

    free(songList);

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

void freeSong(struct SongNode* song){
    free(song->song_artist);
    free(song->song_title);
    free(song->release_date);
    free(song->runtime);
    free(song);
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
    *(song->runtime),
    header);
    printf(buffer);
}