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


int main()
{
    // Buffer for reading one line of input
    char line[MAX_LINE_CHARS];
    // holds separated words based on whitespace
    char* line_words[MAX_LINE_WORDS + 1];

    // Loop until user hits Ctrl-D (end of input)
    // or some other input error occurs
    printf("Conch Shell: ");
    while( fgets(line, MAX_LINE_CHARS, stdin) ) {

        int num_words = split_cmd_line(line, line_words);
        printf("Num Words: %d\n", num_words);

        for (int i=0; i < num_words; i++) {
            printf("Line Words: %s\n", line_words[i]);
        }

        int pipeLoop = 0;
        pipeLoop = pipeCount(line_words, num_words);
        printf("Pipe Loop Number: %d\n", pipeLoop);










/*
            // Extract the first token
            char * token = strtok(line, "|");
            pipeCommandArray[pipeLoop] = token;
            // loop through the string to extract all other tokens
            while( token != NULL ) {
                printf( "Print Inside While: %s\n", pipeCommandArray[pipeLoop] ); //printing each token
                token = strtok(NULL, "| ");
                pipeCommandArray[--pipeLoop] = token;
            }


            for (int i = 0; i < pipeCount(line_words, num_words); i++) {
                printf("pipeCommand : %s\n", pipeCommandArray[i]);

            }
            */



        printf("Conch Shell: ");
    }

    return 0;
}

