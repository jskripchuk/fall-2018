
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define	BUFFSIZE	10

//Going to have to do multiple system calls since buffer will get full with big files
//While loop?

//read call keeps a pointer and stuff so it's nice
//multiple reads iterate though the file


int main(int argc, char** argv){
    char buf[BUFFSIZE];

   // buf = "Hello!";

    int file1 = open("testfile.txt", O_RDONLY);
    read(file1, buf, BUFFSIZE);
    printf("%d\n", file1);
    printf("%s",buf);
    //sprintf(buf, )
    //printf("Hello world!");
    return 0;
}