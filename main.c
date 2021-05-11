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
        printLineWords(ShellStruct);

        //char **ArgV = malloc(sizeof(char*)*(ShellStruct.num_words+1));
        ShellStruct.ArgV_S = malloc(sizeof(char*)*(ShellStruct.num_words+1));
        //strcpy(ShellStruct.ArgV_S, ArgV);

        pipeCount(&ShellStruct);

        pipePrep(&ShellStruct);
        printArgv(ShellStruct);

        // if (ShellStruct.num_words == 1){
        //     runSimpleCommands(ShellStruct);
        // }
        // else{
        // runPipes(ShellStruct);
        // }
        // //runRedirects();

        free(ShellStruct.ArgV_S);
        printf("Conch Shell: ");                            // Loop until user hits Ctrl-D (end of input) or other input error
    }
    return 0;
}