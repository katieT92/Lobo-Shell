#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "constants.h"
#include "parsetools.h"
#include <stdbool.h>

bool runPipe(char **lhs, char **rhs);
int pipeCount(char** line_words, int numberOfWords);
void syserror(const char *s);


int main() {
    char line[MAX_LINE_CHARS];                                              // Buffer for reading one line of input
    char* line_words[MAX_LINE_WORDS + 1];                                   // Holds separated words based on whitespace
    char* pipeLHS[MAX_LINE_WORDS + 1];
    char* pipeRHS[MAX_LINE_WORDS + 1];

    printf("Conch Shell: ");                            // Loop until user hits Ctrl-D (end of input) or other input error
    while( fgets(line, MAX_LINE_CHARS, stdin) ) {
        
        if (line[strlen(line)-1] == '\n')               // Delete the new line character from end of line if present   
            line[strlen(line)-1] = '\0';    
        int num_words = split_cmd_line(line, line_words);                     // Num words (including pipes) in line_words
        printf("Num Words: %d\n", num_words);
        //printLineWords(line_words, num_words);              // This was used as an example to show passing a char* as a char**

        int number_Of_Pipes = 0;
        number_Of_Pipes = pipeCount(line_words, num_words);

        runSimpleCommands();
        runRedirects();
        int i = 0;
        i = runPipes(line_words, num_words, number_Of_Pipes);
    }
    return 0;
}