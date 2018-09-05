/*
James Skripchuk
CISC361
Assignment 1
Last Updated: 9/4/18
*/


//Represents one song
typedef struct SongNode{
    char* song_artist;
    char* song_title;
    char* release_date;
    struct SongNode* next;
    struct SongNode* prev; 
    int* runtime;
} song_t;

//Prints the song
void printSong(struct SongNode*);
//Safely frees the songs memory
void freeSong(struct SongNode*);

//A struct for a doublely linked list with a head and a tail
struct SongDoubleLinkedList{
    struct SongNode* head;
    struct SongNode* tail;
};

//Adds a song to the end of the list
void appendSong(struct SongDoubleLinkedList*, struct SongNode*);
//Deletes all the songs of a given artist from the list
void deleteArtist(struct SongDoubleLinkedList*, char*);
//Prints list forwards
void printForwards(struct SongDoubleLinkedList*);
//Prints list backwards
void printBackwards(struct SongDoubleLinkedList*);
//Safely deletes and frees the entire list
void deleteList(struct SongDoubleLinkedList*);