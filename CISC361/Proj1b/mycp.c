
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define	BUFFSIZE	100

//Going to have to do multiple system calls since buffer will get full with big files
//While loop?

//read call keeps a pointer and stuff so it's nice
//multiple reads iterate though the file


int main(int argc, char** argv){
    char buf[BUFFSIZE];
    int len;

   // buf = "Hello!";

    int file1 = open("testfile.txt", O_RDONLY);
    int file2 = open("testfile2.txt", O_WRONLY | O_CREAT);
    
    read(file1, buf, BUFFSIZE);
    
    len = (int)strlen(buf);
    buf[len-1] = '\0';
    char str[len];
    strcpy(str, buf);
    //printf("%d\n", file1);
    //printf("%s",str);
    write(file2, buf, BUFFSIZE);
    close(file1);
    close(file2);
    //sprintf(buf, )
    //printf("Hello world!");
    return 0;
}