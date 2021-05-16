#include "parsetools.h"
#include "constants.h"


int main() {
    struct Data_IDK ShellStruct;

    char line[MAX_LINE_CHARS];                                              // Buffer for reading one line of input
    char *line_words[MAX_LINE_WORDS + 1];                                   // Holds separated words based on whitespace
    char *pipeLHS[MAX_LINE_WORDS + 1];
    char *pipeRHS[MAX_LINE_WORDS + 1];

    //printf("Conch Shell: ");                            // Loop until user hits Ctrl-D (end of input) or other input error
    while (fgets(line, MAX_LINE_CHARS, stdin)) {
        if (line[strlen(line) - 1] ==
            '\n')               // Delete the new line character from end of line if present
            line[strlen(line) - 1] = '\0';

        ShellStruct.num_words = split_cmd_line(line, line_words);
        memcpy(ShellStruct.line_words, line_words, sizeof(line_words));
        ShellStruct.num_ArgV_S = GetSizeArgV_S(&ShellStruct);
        ShellStruct.ArgV_S = malloc(sizeof(char *) * (ShellStruct.num_ArgV_S));

        pipeCount(&ShellStruct);
        //printLineWords(ShellStruct);
        pipePrep(&ShellStruct);
        //printArgv(ShellStruct);


        if (ShellStruct.numPipes > 0) {
            runPipes(ShellStruct);
        } else {
            runSimpleCommands(ShellStruct);
        }
        free(ShellStruct.ArgV_S);

        //printf("Conch Shell: ");                                // Loop until user hits Ctrl-D (end of input) or other input error
    }

    return 0;
}