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
<<<<<<< Updated upstream

        int num_words = split_cmd_line(line, line_words);
        printf("Num Words: %d\n", num_words);

        for (int i=0; i < num_words; i++) {
            printf("Line Words: %s\n", line_words[i]);
            check_command(line_words[i]);
        }
=======
        if (line[strlen(line)-1] == '\n')               // Delete the new line character from end of line if present   
            line[strlen(line)-1] = '\0';    
        int num_words = split_cmd_line(line, line_words);                     // Num words (including pipes) in line_words
>>>>>>> Stashed changes

        char **ArgV = malloc(sizeof(char*)*(num_words+1));
        pipePrep(line_words, ArgV, num_words+1);

        if (num_words == 1){
            runSimpleCommands(ArgV);
        }
        else{
        int number_Of_Pipes = 0;
        number_Of_Pipes = pipeCount(line_words, num_words);
<<<<<<< Updated upstream
        printf("PipeCount: %d\n", number_Of_Pipes);










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
=======
        runPipes(ArgV, num_words, number_Of_Pipes);
        }
        //runRedirects();

        //char **ArgV;
        //char **ArgV = malloc(sizeof(char*)*(num_words+1));
        //pipePrep(line_words, ArgV, num_words+1);
        // printLineWords(ArgV, num_words);
        // printLineWords(ArgV, num_words+1);
        //runPipes(ArgV, num_words, number_Of_Pipes);
        free(ArgV);
        printf("Conch Shell: ");                            // Loop until user hits Ctrl-D (end of input) or other input error
>>>>>>> Stashed changes
    }

    return 0;
}

