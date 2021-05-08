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

<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======


int runPipes(char** line_words, int num_words, int number_Of_Pipes){
    //int pfd[number_Of_Pipes*2];                                     // read end and write end for each pipe
    int pfd[2];                                     // read end and write end for each pipe
    //int i = 0;
  //  int j = 0;
    int input = 0;
/*
    while (i < num_words){
        // START GETTING THE COMMAND TO PASS TO EXECVP. STORE IT IN variable, "command"
        while (j < num_words && strchr(line_words[j], '|') == NULL)     // find size that pointer to command should be
            j++;
        char *command[j*sizeof(char*)];                                // create correct size command pointer
        int insertIdx = 0;                                             // in each loop we' we'll insert into command starting at idx 0
        while (i < j){                                                  // insert into simple commands and args into command
            command[insertIdx] = line_words[i];
            printf("linewords: %s\n", line_words[i]);                   // testing correct contents of line_words to copy
            printf("command: %s\n", command[insertIdx]);                // testing correct contents of command
            i++;
            insertIdx++;
        }
        command[insertIdx] = NULL;                                      // all commands should end with null to pass to execvp
        printf("command: %s\n\n", command[insertIdx]);                  // testing
        i++;
        j++;                                                              
        // END GETTING THE COMMAND TO PASS TO EXECVP. Ready for use.

*/
        for(int pfdIdx = 0; pfdIdx <= number_Of_Pipes; pfdIdx += 2){     // pipes pfd(0), pfd(2), pfd(4), ... , pfd(number_Of_Pipes*2)
            if (pipe(pfd + pfdIdx) == -1)
                syserror( "Could not create a pipe" );
            createProcess(input, pfd[1], line_words);
            close(pfd[1]);
            input = pfd[0];
        }
        if (input != 0)
            dup2(input, 0);
        return execvp (line_words[0], line_words);
   // }
}


void pipePrep(char** line_words, char** arrayToReturn, int num_words){

    for(int i = 0; i < num_words; i++){
        if(strcmp(line_words[i], "|") != 0 && i != num_words){
            arrayToReturn[i] = line_words[i];
        } else if(strcmp(line_words[i],"|") == 0 || i == num_words){
            arrayToReturn[i] = NULL;
        }else{

        }
    }
arrayToReturn[num_words + 1] = NULL;
}

// void runPipes(char** line_words, int num_words, int number_Of_Pipes){
    
//     typedef struct commandStruct {
//         char **args;
//     } Command;

//     Command *command = malloc(number_Of_Pipes-1 * sizeof *command);
//     char *simpleCommand = malloc(sizeof *simpleCommand);
//     int commandIdxToInsert = 0;
//     int simpleCommandRunningLength = 0;
//     int lineWordsIdx = 0;
//     bool foundPipe = false;

//     while (lineWordsIdx < num_words){
//         foundPipe = strchr(line_words[lineWordsIdx], '|') == NULL ? false : true;
//         if (!foundPipe){
//             //strcpy( simpleCommand[simpleCommandRunningLength], *line_words[lineWordsIdx]);
//             simpleCommand[simpleCommandRunningLength] = *line_words[lineWordsIdx];   
//             simpleCommandRunningLength++; 
//         } 
//         else {
//             simpleCommand[simpleCommandRunningLength] = '\0'; 
//             command->args[commandIdxToInsert] = simpleCommand;
//             commandIdxToInsert++;
//             simpleCommandRunningLength = 0;
//             strcpy(simpleCommand,"");
//         }
//         lineWordsIdx++;
//     }
//     simpleCommand[simpleCommandRunningLength] = *line_words[lineWordsIdx];   
//     command->args[commandIdxToInsert] = simpleCommand;
//     free(simpleCommand);


//     int pfd[number_Of_Pipes*2]; // read end and write end for each pipe
//     pid_t pid;

//     for(int pfdIdx = 0; pfdIdx < number_Of_Pipes; pfdIdx += 2) // pipes pfd(0), pfd(2), pfd(4), ... , pfd(number_Of_Pipes*2)
//         if (pipe(pfd + pfdIdx) == -1)
//         syserror( "Could not create a pipe" );

    
//     for (int commandIdx = 0; commandIdx < number_Of_Pipes; commandIdx++){

//     }
//     switch ( pid = fork() ) {
//         case -1: 
//             syserror("First fork failed");
//             break;
//         case  0: 
//             if (close(0) == -1)
//                 syserror("Could not close stdin");
//             dup(pfd[0]);
//             if (close(pfd[0]) == -1 || close(pfd[1]) == -1)
//                 syserror( "Could not close pfds from first child" );
//             execlp(line_words[0], line_words[0], NULL);
//             syserror("Could not exec line_words[0]");
//             break;
//         default:
//             fprintf(stderr, "The first child's pid is: %d\n", pid);
//             break;
//     }

//     switch ( pid = fork() ) {
//         printf("Inside the second fork()\n");
//         case -1: 
//             syserror( "Second fork failed" );
//             break;
//         case  0: 
//             if (close(1) == -1)
//                 syserror("Could not close stdout");
//             dup(pfd[1]);
//             if (close(pfd[0]) == -1 || close(pfd[1]) == -1)
//                 syserror( "Could not close pfds from second child" );
//             execlp(line_words[1], line_words[1], NULL);
//             syserror( "Could not exec line_words[1]" );
//             break;
//         default:
//             fprintf(stderr, "The second child's pid is: %d\n", pid);
//             break;
//     }
    
//     if (close(pfd[0]) == -1)
//         syserror( "Parent could not close stdin" );
//     if (close(pfd[1]) == -1)
//         syserror( "Parent could not close stdout" );

//     while ( wait(NULL) != -1)
//         ;
// }


void syserror(const char *s)
{
    extern int errno;
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, " (%s)\n", strerror(errno));
    exit(1);
}



>>>>>>> Stashed changes
