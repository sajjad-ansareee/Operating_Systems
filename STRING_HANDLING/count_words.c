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

int main(int argc, char *argv[]) {
    return 0;
}