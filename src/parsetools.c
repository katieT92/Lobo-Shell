#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "parsetools.h"



<<<<<<< Updated upstream
// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//
int split_cmd_line(ch#include "constants.h"
#include "parsetools.h"



// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//
=======
>>>>>>> Stashed changes
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

//IN: Char ** , int
//OUT: Integer
//checks and counts number of | symbols  in the line_words array based on the number of words in that array.
//If there are no pipes will return 0
//If there are pipes, will return the number of pipes found.
int pipeCount(char** line_words, int numberOfWords){
    int pipeCount = 0;
    for(int i = 0; i < numberOfWords; i++){
        if(strchr(line_words[i], '|') != NULL){
            if((strlen(line_words[i])) == 1){
                pipeCount++;
            }
        }
    }
    return pipeCount;
}

<<<<<<< Updated upstream
int check_command(char* line_words){
    int command = 0;
    
    for (int i=0; i < sizeof(line_words); i++) {
        if (line_words[i] == 32 || line_words[i] == 45){       // If value at i is a space, '-', and possibly '|'
            break;
        }
        command += line_words[i];
    }

    //printf("command value: %d\n", command);

    switch (command) {
        // Sometimes the first comman entered returns a different value than it does if entered after the first.
        // Seems to work better if you use a comman that starts with w?
        // Maybe some way to send a dummy value first to make it working
        // Or just scrap this idea of checking ascii value of command 
=======

void printLineWords(char** line_words, int num_words){
    for (int i=0; i < num_words; i++) {
        printf("Line Words: %s\n", line_words[i]);
    }
    printf("DONE WITH PRINTLINEWORDS\n");
}


void runSimpleCommands(char** commands){
    pid_t pid;
    switch (pid = fork()) {
>>>>>>> Stashed changes
        case -1: 
            break;
<<<<<<< Updated upstream
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
=======
        case  0: 
            // if (input != 0) {
            //     dup2 (input, 0);
            //     close (input);
            // }
            // if (output != 1) {
            //     dup2 (output, 1);
            //     close (output);
            // }
            
            execvp(commands[0], commands);
>>>>>>> Stashed changes
        default:
            break;
    }
<<<<<<< Updated upstream
=======
    while (wait(NULL) != -1); 
    //return pid;
>>>>>>> Stashed changes
}
ar* line, char** list_to_populate) {
   char* saveptr;  // for strtok_r; see http://linux.die.net/man/3/strtok_r
   char* delimiters = " \t\n"; // whitespace
   int i = 0;

<<<<<<< Updated upstream
   list_to_populate[0] = strtok_r(line, delimiters, &saveptr);
=======
void runRedirects(){    //https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
    char direction = '<';
    if(direction == '<'){
        fd = open(command, O_RDONLY, 0);
        dup2(fd, STDIN_FILENO);
        in = 0;
        current_in = dup(0);  // Fix for symmetry with second paragraph
    }
    else if (direction == ' >'){
        fd = creat(output, 0644);
        dup2(fd, STDOUT_FILENO);
        out = 0;
        current_out = dup(1);
    }
}
>>>>>>> Stashed changes

   while(list_to_populate[i] != NULL && i < MAX_LINE_WORDS - 1)  {
       list_to_populate[++i] = strtok_r(NULL, delimiters, &saveptr);
   };

<<<<<<< Updated upstream
   return i;
}
=======
// Creates a char* array of line_words
void pipePrep(char** words_array, char** arrayToReturn, int num_words){
    for(int i = 0; i < num_words; i++){
        if(i < num_words - 1 && strchr(words_array[i], '|') == NULL)                 // If not last command and not a pipe
            arrayToReturn[i] = words_array[i];                                       // Append word
        else if (i == num_words - 1 || strchr(words_array[i], '|') != NULL)        // If last command or is pipe
            arrayToReturn[i] = NULL;                                                 // Append null
        // else if ( > or >> or < or <<)
            // do something? Maybe we need a differnt funciton to handle redirections.  
    }
}


void runPipes(char** commands, int num_words, int number_Of_Pipes){        
    int numCommands = number_Of_Pipes + 1;                                          // Used for pipe loop variable
    int endNullSearchIdx = 0;                                                       // Idx for end of current command in "commands"
    int startNullSearchIdx = endNullSearchIdx;                                      // Idx for start of current command in "commands" 
    int pfd[2];                                                                     // Read(0) and write(1) ends of pipe
    pid_t pid;                                                                      // Process id
    int oldFd = 0;                                                                  // Reference to fd from a child p's parent's previous pipe. 

    // START PIPE PROCESSES
    for (int i = 0; i < numCommands; i++){                                          // For each command


        // START GET SINGLE COMMMAND FROM COMMANDS TO PASS TO EXEC
        int commandInsertIdx = 0;                                                   // Will always insert into "command" starting at idx 0 
        while (endNullSearchIdx <= num_words && commands[endNullSearchIdx])         // Find next null for current command in "commands"           
            endNullSearchIdx++;
        endNullSearchIdx++;
        char *command[(endNullSearchIdx-startNullSearchIdx)*sizeof(char*)];         // Create "command" to hold current command in "commands"
        while (startNullSearchIdx < endNullSearchIdx){                              // Current command length in these bounds of "commands"
            command[commandInsertIdx] = commands[startNullSearchIdx];               // Insert word into "command" always starting at 0
            commandInsertIdx++;
            startNullSearchIdx++;
        }
        // END GET SINGLE COMMAND FROM COMMANDS TO PASS TO EXEC


        if (i < numCommands-1)                                                          // Don't pipe for last command
            pipe(pfd);                                                                  // Create pipe in parent

        switch(pid = fork()){                                                           // Parent forks a new child
            case -1:                                                                    // Unsuccessful fork
                printf("Fork %d failed.\n", i);
                break;  
            case 0:                                                                     // In Child process
                if (i == 0){                                                            // First command in allCommands
                    dup2(pfd[1], 1);                                                    // Child stdout -> write end of pipe
                    if (close(pfd[0]) == -1 || close(pfd[1]) == -1)                     // Close both fd's, no longer need
                        syserror("Could not close pfd[0] or pfd[1] from child.\n");
                    execvp(command[0],  command);                                       // Exec first command
                    syserror("Could not exec simple command from first child.\n");
                }
                else if (i < numCommands - 1){                                          // A middle command in allCommands
                    if (close(0) == -1)                                                 // Close fd for stdin
                        printf("Could not close stdin from child.");
                    dup2(oldFd, 0);                                                     // Point fd for stdin at previous read end of pipe
                    dup2(pfd[1], 1);                                                    // Point fd for stdout at write end of pipe
                    execvp(command[0],  command); 
                    if (close(pfd[0]) == -1 || close(pfd[1]) == -1 || close(oldFd))     // Close fd's for stdin and stdout, no longer need
                        syserror("Could not close pfd[0] of pfd[1] or oldFd from child.\n");
                }
                else{                                                                    // Last command in allCommands
                    dup2(oldFd, 0);
                    if (close(oldFd))                                                    // Close fd for oldFd from previous pipe
                        syserror("Could not close oldFd from child.\n");
                    execvp(command[0], command);                                         // Exec last command
                    syserror("Could not exec simple command from last child.\n");
                }
            default:                                                                    // Parent
                if (i == 0){                                                            // First command        
                    oldFd = pfd[0];                                                     // Point oldFd at read end of pipe
                    if (close(pfd[1]) == -1)                                            // Close write end of pipe
                        syserror("Could not close pfd[1] from parent.\n");
                }
                else if (i < numCommands - 1){                                          // A middle command in allCommands
                    if (close(oldFd) == -1 || close(pfd[1]) == -1)                      // Close end of previous pipe oldFd points at
                        syserror("Could not close oldFd or pfd[1] from parent.\n");     
                    oldFd = pfd[0];                                                     // Point oldFd at read end of pipe
                }
                else{                                                                   // Last command in allCommands
                    if (close(oldFd) == -1)                                             // Close end of previous pipe that oldFd points at 
                        syserror( "Could not close oldFd from parent.\n");
                }
        }
    }
    while (wait(NULL) != -1);                                                           // Reap all the child processes!
}



void syserror(const char *s){
    extern int errno;
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, " (%s)\n", strerror(errno));
    exit(1);
}
>>>>>>> Stashed changes
