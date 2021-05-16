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
void pipeCount(struct Data_IDK *shell_struct){
    int pipeCount = 0;
    for(int i = 0; i < shell_struct->num_words; i++){
        if(strchr(shell_struct->line_words[i], '|') != NULL){
            pipeCount++;
        }
    }
    shell_struct->numPipes = pipeCount;
}


void redirectCount(struct Data_IDK *shell_struct){
    int redirectCount = 0;
    for(int i = 0; i < shell_struct->num_words; i++){
        if(strchr(shell_struct->line_words[i], '<') || strchr(shell_struct->line_words[i], '>') || strcmp(shell_struct->line_words[i], ">>") == 0){
            redirectCount++;
        }
    }
    shell_struct->num_redirects = redirectCount;
}


void pipePrep(struct Data_IDK *shell_struct) {

    printf("in inside pipePrep %s\n", shell_struct->in);
    printf("out inside pipePrep %s\n", shell_struct->out);
    printf("appendOut inside pipePrep %s\n", shell_struct->appendOut);
    printf("inside pipePrep num_ArgV_S: %d\n", shell_struct->num_ArgV_S);
    printf("inside pipePrep num_words: %d\n", shell_struct->num_words);

    int numberOfWords;
    numberOfWords = shell_struct->num_words;
    numberOfWords++;


    int j = 0;
    for (int i = 0; i < numberOfWords; i++) {
        if (i == numberOfWords - 1 || j == shell_struct->num_ArgV_S ||
            strchr(shell_struct->line_words[i], '|') != NULL) {        // If last command or is pipe
            shell_struct->ArgV_S[j] = NULL;
            j++;
        } else if (strcmp(shell_struct->line_words[j], ">>") == 0) {

        } else if (strchr(shell_struct->line_words[j], '>') != NULL) {

        } else if (strchr(shell_struct->line_words[j], '<') != NULL) {
        }else if (i < numberOfWords - 1 && (strchr(shell_struct->line_words[i], '|') == NULL)) {                 // If not last command and not a pipe
            shell_struct->ArgV_S[j] = shell_struct->line_words[i];
            j++;
        }// Append word
    }

/*
    if (shell_struct->in != NULL){
        char *trimFrontArgV_S[shell_struct->num_words - 1];
        shell_struct->num_ArgV_S = (shell_struct->num_words - 1);
        for (int i = 0; i < shell_struct->num_words - 1; i++) {
            trimFrontArgV_S[i] = shell_struct->ArgV_S[i];
        }
        strncpy(shell_struct->ArgV_S[0], trimFrontArgV_S, sizeof(trimFrontArgV_S));

        for (int i = 0; i < shell_struct->num_words - 1; i++) {
            printf("trimFrontArgV_S Words: %s\n", trimFrontArgV_S[i]);
        }

    }


    if ((shell_struct->out != NULL || shell_struct->appendOut != NULL) && shell_struct->in == NULL) {
        char *adjustArgV[shell_struct->num_words - 1];
        for (int i = 0; i < shell_struct->num_words - 1; i++) {
            adjustArgV[i] = shell_struct->ArgV_S[i];
        }

        for (int i = 0; i < shell_struct->num_words - 1; i++) {
            printf("adjustArgV Words: %s\n", adjustArgV[i]);
        }

        strncpy(shell_struct->ArgV_S, adjustArgV, sizeof(adjustArgV));
        shell_struct->num_ArgV_S = (shell_struct->num_words - 1);
        printf("num_ArgV_S: %d", shell_struct->num_ArgV_S);
        //shell_struct->ArgV_S = (char **) realloc(shell_struct->ArgV_S, (shell_struct->num_words - 1));
        //memcpy(shell_struct->ArgV_S, adjustArgV, sizeof(adjustArgV));


    }else if(shell_struct->out != NULL || shell_struct->appendOut != NULL) && shell_struct->in != NULL){
        char *trimEndArgV_S[shell_struct->num_words - 3];
        for (int i = 0; i < shell_struct->num_words - 1; i++) {
            trimEndArgV_S[i] = shell_struct->ArgV_S[i];
        }

        for (int i = 0; i < shell_struct->num_words - 1; i++) {
            printf("trimEndArgV_S Words: %s\n", trimEndArgV_S[i]);
        }


        shell_struct->num_ArgV_S = (shell_struct->num_ArgV_S - 2);
        strncpy(shell_struct->ArgV_S, trimEndArgV_S, sizeof(trimEndArgV_S));

    }else{
        shell_struct->num_ArgV_S = (shell_struct->num_words + 1);
    }




       // free(adjustArgV);



    memcpy(ShellStruct.line_words, line_words, sizeof(line_words));
    numberOfWords: 6 - ArgV is 1 more than num_words
    num_words    : 5
    num_words -1 : 4

 a.in < ls >> b.out
[a.in][NULL][ls][NULL][b.out][null]

    [ls][NULL] - desired output


    ls | wc > a.out
    [ls][NULL][wc][null][a.out][null]  - current output

    [ls][NULL][wc][NULL] - desired output

    ls -l > a.out
*/
 }

void runSimpleCommands(struct Data_IDK shell_struct){
    printf("Top Simple Commands.\n");
    pid_t pid;
    switch (pid = fork()) {
        case -1: 
            syserror("First fork failed\n");
            break;
        case  0:
            if(shell_struct.in != NULL){
                int fd0;
                fd0 = open(shell_struct.in, O_RDONLY);
                dup2(fd0, 0);
                close(fd0);
            }
            if(shell_struct.out != NULL) {
                int fd1;
                fd1 = open(shell_struct.out, O_WRONLY|O_CREAT|O_TRUNC, 0664);
                dup2(fd1, 1);
                close(fd1);
            }else if(shell_struct.appendOut != NULL) {
                int fd1;
                fd1 = open(shell_struct.appendOut, O_RDWR | O_CREAT | O_APPEND, 0664);
                dup2(fd1, 1);
                close(fd1);
            }
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
    int fd_out;

    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    // START PIPE PROCESSES

    if(shell_struct.in != NULL){
        int fd0;
        fd0 = open(shell_struct.in, O_RDONLY);
        dup2(fd0, 0);
        close(fd0);
    }
    if(shell_struct.out != NULL) {
        int fd1;
        fd1 = open(shell_struct.out, O_WRONLY|O_CREAT|O_TRUNC, 0664);
        dup2(fd1, 1);
        close(fd1);
    }else if(shell_struct.appendOut != NULL) {
        int fd1;
        fd1 = open(shell_struct.appendOut, O_RDWR | O_CREAT | O_APPEND, 0664);
        dup2(fd1, 1);
        close(fd1);
    }


    for (int i = 0; i < numCommands; i++){                                          // For each command


        // START GET SINGLE COMMMAND FROM COMMANDS TO PASS TO EXEC
        int commandInsertIdx = 0;                                                   // Will always insert into "command" starting at idx 0
        while (endNullSearchIdx <= shell_struct.num_words && shell_struct.ArgV_S[endNullSearchIdx])         // Find next null for current command in "commands"
            endNullSearchIdx++;
        endNullSearchIdx++;
        char *command[(endNullSearchIdx-startNullSearchIdx)*sizeof(char*)];         // Create "command" to hold current command in "commands"
        while (startNullSearchIdx < endNullSearchIdx){
            // Current command length in these bounds of "commands"
            // Current command length in these bounds of "commands"
            command[commandInsertIdx] = shell_struct.ArgV_S[startNullSearchIdx];               // Insert word into "command" always starting at 0
            commandInsertIdx++;
            startNullSearchIdx++;
        }
        // END GET SINGLE COMMAND FROM COMMANDS TO PASS TO EXEC

        if (i < numCommands-1)



            // Don't pipe for last command
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
                        printf("Could not close stdin from child.\n");
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
                else{
                    // Last command in allCommands
                    if (close(oldFd) == -1)                                             // Close end of previous pipe that oldFd points at 
                        syserror( "Could not close oldFd from parent.\n");

                }

                }

        }
    if(shell_struct.in != NULL){
        int fd0;
        fd0 = saved_stdin;
        dup2(fd0, 0);
        close(fd0);
    }
    if(shell_struct.out != NULL) {
        int fd1;
        fd1 = saved_stdout;
        dup2(fd1, 1);
        close(fd1);
    }else if(shell_struct.appendOut != NULL) {
        int fd1;
        fd1 = saved_stdout;
        dup2(fd1, 1);
        close(fd1);
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
    for (int i=0; i < shell_struct.num_ArgV_S; i++) {
        printf("Argv Words: %s\n", shell_struct.ArgV_S[i]);
    }
    printf("DONE WITH PRINTARGV\n");
}

void runRedirects(struct Data_IDK shell_struct){    //https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection

/*
    if(shell_struct.in != NULL){
        printf("In if\n");
        printf("command[-1] = %s\n", command[commandInsertIdx-1]);
        int fd0;
        fd0 = open(shell_struct.line_words[fileDirect], O_RDONLY);
        dup2(fd0, 0);
        close(fd0);
    }else if(shell_struct.out != NULL) {
        printf("In if else\n");
        printf("command[-1] = %s\n", command[commandInsertIdx - 1]);
        int fd1;
        fd1 = open(shell_struct.line_words[fileDirect], O_RDONLY | O_CREAT, 1);
        dup2(fd1, 1);
        close(fd1);
    }else if(shell_struct.appendOut != NULL) {
        printf("In second if else\n");
        printf("command[-1] = %s\n", command[commandInsertIdx - 1]);
        int fd1;
        fd1 = open(shell_struct.line_words[fileDirect], O_RDWR | O_CREAT | O_APPEND, 1);
        dup2(fd1, 1);
        close(fd1);
    }else{
        printf("In else.\n");
    }

    execvp(redirectExec[0], redirectExec);
*/

    // int pid = fork();

    // if (pid == -1) {
    //     perror("fork");
    // } else if (pid == 0) {   

    //     if (in) { //if '<' char was found in string inputted by user
    //         int fd0 = open(input, O_RDONLY, 0);
    //         dup2(fd0, STDIN_FILENO);
    //         close(fd0);
    //         in = 0;
    //     }

    //     if (out) { //if '>' was found in string inputted by user
    //         int fd1 = creat(output, 0644);
    //         dup2(fd1, STDOUT_FILENO);
    //         close(fd1);
    //         out = 0;
    //     }   

    //     execvp(res[0], res);
    //     perror("execvp");
    //     _exit(1);
    // } else {
    //     waitpid(pid, 0, 0);
    //     free(res);
    // }
    exit;
}

int GetSizeArgV_S(struct Data_IDK *shell_struct){
    shell_struct->in = NULL;
    shell_struct->out = NULL;
    shell_struct->appendOut = NULL;

    int numberOfWords;
    numberOfWords = shell_struct->num_words;
    numberOfWords++;
    int ArgV_WordCount = 0;
        for (int j = 0; j < numberOfWords; j++) {
            if (j == numberOfWords - 1 || strchr(shell_struct->line_words[j], '|') != NULL) {
                ArgV_WordCount = ArgV_WordCount + 1;
            } else if (strcmp(shell_struct->line_words[j], ">>") == 0) {
                shell_struct->appendOut = shell_struct->line_words[j + 1];
                j++;
            } else if (strchr(shell_struct->line_words[j], '>') != NULL) {
                shell_struct->out = shell_struct->line_words[j + 1];
                j++;
            } else if (strchr(shell_struct->line_words[j], '<') != NULL) {
                shell_struct->in = shell_struct->line_words[j + 1];
                j++;
            } else if (j < numberOfWords - 1 && strchr(shell_struct->line_words[j], '|') ==
                                                NULL) {                 // If not last command and not a pipe
                ArgV_WordCount = ArgV_WordCount + 1;
            }// Append word
        }




   return ArgV_WordCount;
}



void syserror(const char *s){
    extern int errno;
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, " (%s)\n", strerror(errno));
    exit(1);
}