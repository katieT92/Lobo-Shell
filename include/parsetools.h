
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
int check_command(char** line_words, int num_words);
void printLineWords(char** line_words, int num_words);
void runSimpleCommands();
void runRedirects();
int runPipes();
=======
//int check_command(char** line_words, int num_words);
void printLineWords(char** line_words, int num_words);
void runSimpleCommands();
void runRedirects();
void runPipes();
void createProcess (int input, int output, char** command);



>>>>>>> Stashed changes

#endif