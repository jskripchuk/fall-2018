/*
James Skripchuk
CISC361
Assignment 1
Last Updated: 9/4/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

/*
This program gives the user and endpoint to a Doublely Linked List, and allows them to add,
delete, and print songs.
*/
int main(){
    int exit_program = 0;

    //The main list
    struct SongDoubleLinkedList* songList = malloc(sizeof(struct SongDoubleLinkedList));

    //A temporary pointer struct for adding new songs
    struct SongNode* song;

    //A control loop in order to persist the menu
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
        
        //Buffers for string input
        int BUFFERSIZE = 128;
        char buffer[BUFFERSIZE];
        int len;

        //For some reason, without the getchar() method, the program skips any proceeding fgets()
        //https://stackoverflow.com/questions/20150845/c-program-skips-fgets
        scanf("%d",&choice);
        getchar();
        switch(choice){
            //Adding an MP3 to the list
            case 1:
                song =  malloc(sizeof(struct SongNode));

                //Various rounds of user input...
                //Song Name
                printf("\nEnter the song's title: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                song->song_title = (char*)malloc(len);
                strcpy(song->song_title,buffer);

                //Artist
                printf("Enter the song's artist: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                song->song_artist = (char*)malloc(len);
                strcpy(song->song_artist,buffer);    

                //Release Date
                printf("Enter the song's release date: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                song->release_date = (char*)malloc(len);
                strcpy(song->release_date,buffer);            

                //Runtime
                int* runtime = malloc(sizeof(int));
                printf("Enter the song's runtime (in seconds): ");
                scanf("%d", runtime);
                song->runtime = runtime;

                //Append the song to the list
                appendSong(songList, song);
                
                break;
            //Deleting an MP3 from the list based on artist
            case 2:
                //Getting the input
                printf("\nEnter the artist's who's songs you want to delete: ");
                fgets(buffer, BUFFERSIZE, stdin);
                len = (int)strlen(buffer);
                buffer[len-1] = '\0';
                char* artist = (char*)malloc(len);
                strcpy(artist,buffer);

                //Delete the nodes from the list
                deleteArtist(songList, artist);

                //Free up the char memory
                free(artist);
                break;
            //Printing forwards
            case 3:
                printForwards(songList);
                break;
            //Printing Backwards
            case 4:
                printBackwards(songList);
                break;
            //Safely delete the list and exit the program
            case 5:
                deleteList(songList);
                exit_program = 1;
                break;
        }
    }

    return 0;
}

//Print the the linked list in the forwards direction starting from the head
void printForwards(struct SongDoubleLinkedList* list){
    struct SongNode* current = list->head;
    while(current != NULL){
        printSong(current);
        current=current->next;
    }
}

//Brint the linked list backwards starting from the tail
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
    //Uses a buffer to hold the string for temp storage
    char buffer[512];

    //Format the string
    sprintf(buffer, "%s\nSong Title: %s\nArtist: %s\nRelease: %s\nLength: %d\n%s\n", 
    header,
    song->song_title,
    song->song_artist,
    song->release_date,
    *(song->runtime),
    header);

    //Print
    printf("%s",buffer);
}