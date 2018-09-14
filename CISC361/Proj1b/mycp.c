/*
James Skripchuk
CISC361
Project 1b: mycp
*/

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define	BUFFSIZE 2048

int main(int argc, char** argv){
    //A temporary char buffer for reading/writing
    char buf[BUFFSIZE];

    //Various strings to print when errors/messages happen
    char ARG_ERROR[] = "Incorrect amount of arguments!\n";
    char SOURCE_ERROR[] = "Source file does not exist!\n";
    char PERMISSIONS_ERROR[] = "Insufficent permissions for source file!\n";
    char WRITE_ERROR[] = "Error writing to file! \n";
    char STAT_ERROR[] = "Error grabbing permissions of file! \n";

    char EXISTS_MESSAGE[] = "Destination file already exists. Overwrite? [0/1]: \n";

    //mycp must take 3 arguments
    if(argc != 3){
        write(STDERR_FILENO, ARG_ERROR, strlen(ARG_ERROR));
        return -1;
    }

    //Check if the source file exists 
    if(access(argv[1], F_OK) != 0){
        write(STDERR_FILENO, SOURCE_ERROR, strlen(SOURCE_ERROR));
        return -1;
    //Check if we have permissions to read the source file
    }else if(access(argv[1], R_OK) != 0){
        write(STDERR_FILENO, PERMISSIONS_ERROR, strlen(PERMISSIONS_ERROR));
        return -1;
    }

    //If destination file already exists, prompt user if they want to overwrite
    if(access(argv[2], F_OK) == 0){
        write(STDOUT_FILENO, EXISTS_MESSAGE, strlen(EXISTS_MESSAGE));
      
	//Tried my hardest to use only system calls but getting user input here was difficult
	//SO we're back to being sane programmers and using scanf 
	int input;
	scanf("%d", &input);

        //Loops until a valid input is reached
        while(input != 0 && input != 1){
            write(STDOUT_FILENO, EXISTS_MESSAGE, strlen(EXISTS_MESSAGE));
            scanf("%d",&input);
        }

        //Exit if N is selected
        if(input == 0){
          return 0;
        }
    }

    //Open files
    int source = open(argv[1], O_RDONLY);
    struct stat st;

    //Stat the file to give the copied file the same permissions as the original
    if(fstat(source, &st) == -1){
	write(STDOUT_FILENO, STAT_ERROR, strlen(STAT_ERROR));
	return -1;    
    }

    //Open the destination file - create it if it doesn't exits, and if it does exist zero it out.	
    int dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, st.st_mode);

    int n;
    //Write in data from source file into destination file
    while ((n = read(source, buf, BUFFSIZE)) > 0){
	if (write(dest, buf, n) != n){
            write(STDERR_FILENO, WRITE_ERROR, strlen(WRITE_ERROR));
            return -1;
        }
    }

    //Close up files
    close(source);
    close(dest);

    return 0;
}
