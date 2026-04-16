#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/* getting command from user through input not using command line */

#define STRING_SIZE 1024

/* we need to make sure the letter next to break is not the break */
int get_word_count(const char *string, char break_character) {  /* by default, we will have ' ' as the character breaker */
    unsigned long string_length=strlen(string);
    unsigned long word_count=0;
    for (int i=0; i<string_length; ++i) {
        if (string[i]==break_character) {
            word_count+=1;
        }
    }
    word_count+=1;  /* every word has a space after except the last one */
    return word_count;
}

char **string_split(const char* string, const char split_letter) {
    unsigned long string_length=strlen(string);

    if (string_length==1) {   /* we will have a '\n' in every case */
        perror("String is empty\n");
        exit(-1);
    }

    /* now need to separately store the words in argument string in an array */
    unsigned long word_count=get_word_count(string, ' ');
    char **words=malloc(word_count*sizeof(char(*)));

    int index=0;    /* it points to the current letter in the string */
    for (int i=0;i<word_count;++i) {
        unsigned long current_word_length=0;
        char current_word[1024];
        memset(current_word, '\0', 1024);

        int j=0;
        while (string[index]!=' ' && string[index]!='\n') {
            current_word[j]=string[index];
            j+=1;
            index+=1;
            current_word_length+=1;
        }
        index+=1;   /* point to letter next to space */
        words[i]=malloc(current_word_length*sizeof(char));
        for (int x=0; x<current_word_length; ++x) {
            words[i][x]=current_word[x];
        }
    }
    return words;
}

int main(int argc, char *argv[]) {
    /* 
        fork a child
        execute the command through child
        repeat first two process
    */
    bool is_running=true;
    while (is_running) {
        if (!fork()) {  /* child in the condition */

            /* this method is only taking the first word not taking complete sentence */
            /*
            char *string;
            scanf("%s", string);
            printf("%s\n", string);
            printf("%lu\n", strlen(string));
            */
            
            /* this is the correct method for getting string with spaces */
            char string[STRING_SIZE];
            fgets(string, STRING_SIZE, stdin);
            char **arguments=string_split(string, ' ');
            
            // execvp(arguments, &arguments);
            printf("%lu\n", sizeof(arguments));
            printf("%lu\n", strlen(arguments[0]));
            printf("%lu\n", strlen(arguments[1]));
            const int word_count=(const int)get_word_count(string, ' ');
            const char *pointers_array[];
            perror("Bash command not executed\n");
        }
    }
    return 0;
}