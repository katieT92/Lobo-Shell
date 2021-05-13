
#ifndef PARSETOOLS_H
#define PARSETOOLS_H

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <stdbool.h> 
#include "constants.h"
=======


// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//


struct Data_IDK
{
    int numPipes;
    int num_words;
    int AppendIn;
    int AppendOut;
    int numRedirectIn ;
    int numRedirectOut;
    char* line_words[MAX_LINE_WORDS + 1]; 
    char* IndexList;
    char** ArgV_S;

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
=======
int split_cmd_line(char* line, char** list_to_populate);
int pipeCount(char** line_words, int numberOfWords);
//int check_command(char** line_words, int num_words);
void printLineWords(char** line_words, int num_words);
void runSimpleCommands();
void runRedirects();
void runPipes(char** commands, int num_words, int number_Of_Pipes);   
void pipePrep(char** words_array, char** arrayToReturn, int num_words);


#endif