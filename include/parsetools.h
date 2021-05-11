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

// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//

int split_cmd_line(char* line, char** list_to_populate);
int pipeCount(char** line_words, int numberOfWords);
<<<<<<< Updated upstream
int check_command(char* line_words);
=======
//int check_command(char** line_words, int num_words);
void printLineWords(char** line_words, int num_words);
void runSimpleCommands(char** commands);
void runRedirects();
void runPipes(char** commands, int num_words, int number_Of_Pipes);   
void pipePrep(char** words_array, char** arrayToReturn, int num_words);

>>>>>>> Stashed changes

#endif
