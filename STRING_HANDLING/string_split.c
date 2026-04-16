#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

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
    char **words=string_split("Sajjad Ansari", ' ');    /* fine */
    const char* name="Sajjad Ansari";
    words=string_split(name, ' ');                      /* fine */
    return 0;
}