#include "parsetools.h"


void syserror(const char *);


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

//IN: Char *
//OUT: Integer
//checks if there is a pipe, if there is, will request the number of pipes in the line from countPipe
//If there are no pipes will return 0
//If there are pipes, will return the number of pipes found.
void pipeCount(struct Data_IDK **shell_struct){
    int pipeCount = 0;
    for(int i = 0; i < shell_struct->num_words; i++){
        if(strchr(shell_struct->line_words[i], '|') != NULL){
            pipeCount++;
        }
    }
    shell_struct->numPipes = pipeCount;
}

void pipePrep(struct Data_IDK **shell_struct){
    for(int i = 0; i < shell_struct->num_words; i++){
        if(i < shell_struct->num_words - 1 && strchr(shell_struct->line_words[i], '|') == NULL)                 // If not last command and not a pipe
            shell_struct->ArgV_S[i] = shell_struct->line_words[i];                                       // Append word
        else if (i == shell_struct->num_words - 1 || strchr(shell_struct->line_words[i], '|') != NULL)        // If last command or is pipe
            shell_struct->ArgV_S[i] = NULL;                                                 // Append null
        // else if ( > or >> or < or <<)
            // do something? Maybe we need a differnt funciton to handle redirections.  
    }
}

void runSimpleCommands(struct Data_IDK shell_struct){
    pid_t pid;
    switch (pid = fork()) {
        case -1: 
            syserror("First fork failed");
            break;
        case  0: 
            execvp(shell_struct.ArgV_S[0], shell_struct.ArgV_S);
        default:
            fprintf(stderr, "The first child's pid is: %d\n", pid);
            break;
    }
    while (wait(NULL) != -1); 
}

void runPipes(struct Data_IDK shell_struct){        
    int numCommands = shell_struct.numPipes + 1;                                          // Used for pipe loop variable
    int endNullSearchIdx = 0;                                                       // Idx for end of current command in "commands"
    int startNullSearchIdx = endNullSearchIdx;                                      // Idx for start of current command in "commands" 
    int pfd[2];                                                                     // Read(0) and write(1) ends of pipe
    pid_t pid;                                                                      // Process id
    int oldFd = 0;                                                                  // Reference to fd from a child p's parent's previous pipe. 

    // START PIPE PROCESSES
    for (int i = 0; i < numCommands; i++){                                          // For each command


        // START GET SINGLE COMMMAND FROM COMMANDS TO PASS TO EXEC
        int commandInsertIdx = 0;                                                   // Will always insert into "command" starting at idx 0 
        while (endNullSearchIdx <= shell_struct.num_words && shell_struct.ArgV_S[endNullSearchIdx])         // Find next null for current command in "commands"           
            endNullSearchIdx++;
        endNullSearchIdx++;
        char *command[(endNullSearchIdx-startNullSearchIdx)*sizeof(char*)];         // Create "command" to hold current command in "commands"
        while (startNullSearchIdx < endNullSearchIdx){                              // Current command length in these bounds of "commands"
            command[commandInsertIdx] = shell_struct.ArgV_S[startNullSearchIdx];               // Insert word into "command" always starting at 0
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

void printLineWords(struct Data_IDK shell_struct){
    for (int i=0; i < shell_struct.num_words; i++) {
        printf("Line Words: %s\n", shell_struct.line_words[i]);
    }
    printf("DONE WITH PRINTLINEWORDS\n");
}

void printArgv(struct Data_IDK shell_struct){
    for (int i=0; i < shell_struct.num_words+1; i++) {
        printf("Argv Words: %s\n", shell_struct.ArgV_S[i]);
    }
    printf("DONE WITH PRINTARGV\n");
}

void runRedirects(struct Data_IDK shell_struct){    //https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
    // char direction = '<';
    // if(direction == '<'){
    //     fd = open(command, O_RDONLY, 0);
    //     dup2(fd, STDIN_FILENO);
    //     in = 0;
    //     current_in = dup(0);  // Fix for symmetry with second paragraph
    // }
    // else if (direction == ' >'){
    //     fd = creat(output, 0644);
    //     dup2(fd, STDOUT_FILENO);
    //     out = 0;
    //     current_out = dup(1);
    // }
    exit;
}


void syserror(const char *s){
    extern int errno;
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, " (%s)\n", strerror(errno));
    exit(1);
}