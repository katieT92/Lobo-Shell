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

//IN: Char ** , int
//OUT: Integer
//checks and counts number of | symbols  in the line_words array based on the number of words in that array.
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

