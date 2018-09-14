/*
James Skripchuk
CISC361
Project 1b: mycp
*/

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define	BUFFSIZE 2048

int main(int argc, char** argv){
    //A temporary char buffer for reading/writing
    char buf[BUFFSIZE];

    //Various strings to print when errors/messages happen
    char ARG_ERROR[] = "Incorrect amount of arguments!\n";
    char SOURCE_ERROR[] = "Source file does not exist!\n";
    char PERMISSIONS_ERROR[] = "Insufficent permissions for source file!\n";
    char WRITE_ERROR[] = "Error writing to file! \n";
    char EXISTS_MESSAGE[] = "Destination file already exists. Overwrite? [Y/N]: \n";


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
        read(STDIN_FILENO, buf, BUFFSIZE);

        int len;
        len = (int)strlen(buf);
        buf[len-1]='\0';

        //Loops until a valid input is reached
        while(strcmp(buf, "Y") != 0 && strcmp(buf, "N") != 0){
            write(STDOUT_FILENO, EXISTS_MESSAGE, strlen(EXISTS_MESSAGE));
            read(STDIN_FILENO, buf, BUFFSIZE);
            len = (int)strlen(buf);
            buf[len-1]='\0';
        }

        //Exit if N is selected
        if(strcmp(buf, "N") == 0){
          return 0;
        }
    }

    //Open files
    int source = open(argv[1], O_RDONLY);
    int dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC);

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
