#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "parsetools.h"


// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//
int split_cmd_line(char* line, char** list_to_populate) {
   char* saveptr;  // for strtok_r; see http://linux.die.net/man/3/strtok_r
   char* delimiters = " \t\n"; // whitespace
   int i = 0;

   list_to_populate[0] = strtok_r(line, delimiters, &saveptr);

   while(list_to_populate[i] != NULL && i < MAX_LINE_WORDS - 1)  {
       list_to_populate[++i] = strtok_r(NULL, delimiters, &saveptr);
   };

   return i;
}
<<<<<<< Updated upstream
=======

//IN: Char *
//OUT: Integer
//checks if there is a pipe, if there is, will request the number of pipes in the line from countPipe
//If there are no pipes will return 0
//If there are pipes, will return the number of pipes found.
int pipeCount(char** line_words, int numberOfWords){
    int pipeCount = 0;
    for(int i = 0; i < numberOfWords; i++){
        if(strchr(line_words[i], '|') != NULL){
            pipeCount++;
        }
    }
    return pipeCount;
}



void printLineWords(char** line_words, int num_words){
    for (int i=0; i < num_words; i++) {
        printf("Line Words: %s\n", line_words[i]);
    }
}




int check_command(char** line_words, int num_words){
    int command = 0;
    // for (int i=0; i < num_words; i++) {
    //     if (line_words[i] == 32 || line_words[i] == 45){       // If value at i is a space, '-', and possibly '|'
    //         break;
    //     }
    //     command += line_words[i];
    // }
    //printf("command value: %d\n", command);

    switch (command) {
        // Sometimes the first comman entered returns a different value than it does if entered after the first.
        // Seems to work better if you use a comman that starts with w?
        // Maybe some way to send a dummy value first to make it working
        // Or just scrap this idea of checking ascii value of command 
        case -1: 
            break;
        case  350: 
            printf("EXECUTE ls COMMAND\n");

            // https://support.sas.com/documentation/onlinedoc/sasc/doc/lr2/execv.htm
            pid_t pid;
            //char *const parmList[] = {"/bin/ls", "-l", "/u/userid/dirname", NULL};
            char *const parmList[] = {"/bin/ls"};
            if ((pid = fork()) == -1)
                perror("fork error");
            else if (pid == 0) {
                execv("/bin/ls", parmList);
                printf("Return not expected. Must be an execv error.n");
            }
            
            break;
        case  354: 
            printf("EXECUTE ps COMMAND\n");
            break;
        case  461: 
            printf("EXECUTE who COMMAND\n");
            break;
        case  345: 
            printf("EXECUTE wc COMMAND\n");
            break;
        case  357: 
            printf("EXECUTE tr COMMAND\n");
            break;
        case  439: 
            printf("EXECUTE cat COMMAND\n");
            break;
        default:
            break;
    }
}

void runSimpleCommands(){}
void runRedirects(){}
void runPipes(){}

>>>>>>> Stashed changes
