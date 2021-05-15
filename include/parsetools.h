
#ifndef PARSETOOLS_H
#define PARSETOOLS_H

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h> 
#include "constants.h"

// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//

struct Data_IDK
{
    int numPipes;
    int num_words;
    int num_redirects;
    char* line_words[MAX_LINE_WORDS + 1];
    char** ArgV_S;
    char* in;
    char* out;
    char* appendIn;
    char* appendOut;
};

int split_cmd_line(char* line, char** list_to_populate);
void pipeCount(struct Data_IDK *shell_struct);
void pipePrep(struct Data_IDK *shell_struct);
void runSimpleCommands(struct Data_IDK shell_struct);
void runPipes(struct Data_IDK shell_struct);
void printLineWords(struct Data_IDK shell_struct);
void printArgv(struct Data_IDK shell_struct);
void runRedirects(struct Data_IDK shell_struct);
void syserror(const char *s);
void redirectCount(struct Data_IDK *shell_struct);


#endif