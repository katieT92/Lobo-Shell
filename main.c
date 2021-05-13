#include "parsetools.h"

#include "constants.h"


int main() {
    struct Data_IDK ShellStruct;

    char line[MAX_LINE_CHARS];                                              // Buffer for reading one line of input
    char* line_words[MAX_LINE_WORDS + 1];                                   // Holds separated words based on whitespace
    char* pipeLHS[MAX_LINE_WORDS + 1];
    char* pipeRHS[MAX_LINE_WORDS + 1];

    printf("Conch Shell: ");                            // Loop until user hits Ctrl-D (end of input) or other input error
    while( fgets(line, MAX_LINE_CHARS, stdin) ) {
        if (line[strlen(line)-1] == '\n')               // Delete the new line character from end of line if present   
            line[strlen(line)-1] = '\0';    

        ShellStruct.num_words = split_cmd_line(line, line_words);                     // Num words (including pipes) in line_words
        memcpy(ShellStruct.line_words, line_words, sizeof(line_words));
        //strcpy(ShellStruct.line_words, line_words);
        //printLineWords(ShellStruct);

        //char **ArgV = malloc(sizeof(char*)*(ShellStruct.num_words+1));
        ShellStruct.ArgV_S = malloc(sizeof(char*)*(ShellStruct.num_words));
        //strcpy(ShellStruct.ArgV_S, ArgV);

        pipeCount(&ShellStruct);

        pipePrep(&ShellStruct);
        //printArgv(ShellStruct);

        if (ShellStruct.num_words == 1){
            runSimpleCommands(ShellStruct);
        }
        else{
        runPipes(ShellStruct);
        }
        //runRedirects();

        free(ShellStruct.ArgV_S);

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

        int number_Of_Pipes = 0;
        number_Of_Pipes = pipeCount(line_words, num_words);

        runSimpleCommands();
        runRedirects();

        //char **ArgV;
        char **ArgV = malloc(sizeof(char*)*(num_words+1));
        pipePrep(line_words, ArgV, num_words+1);
       // printLineWords(ArgV, num_words);
        // printLineWords(ArgV, num_words+1);
        runPipes(ArgV, num_words, number_Of_Pipes);
        free(ArgV);

        printf("Conch Shell: ");                            // Loop until user hits Ctrl-D (end of input) or other input error
    }
    return 0;
}