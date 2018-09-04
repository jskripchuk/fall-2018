/*
James Skripchuk
CISC361
Assignment 1
Last Updated: 9/4/18
*/


typedef struct SongNode{
    char* song_artist;
    char* song_title;
    char* release_date;
    struct SongNode* next;
    struct SongNode* prev; 
    int* runtime;
} song_t;

void printSong(struct SongNode*);
void freeSong(struct SongNode*);

struct SongDoubleLinkedList{
    struct SongNode* head;
    struct SongNode* tail;
};

void appendSong(struct SongDoubleLinkedList*, struct SongNode*);
void deleteArtist(struct SongDoubleLinkedList*, char*);
void printForwards(struct SongDoubleLinkedList*);
void printBackwards(struct SongDoubleLinkedList*);
void deleteList(struct SongDoubleLinkedList*);