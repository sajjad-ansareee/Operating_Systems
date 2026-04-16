#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void check(const char *string) {
    printf("%s\n", string);
    return;
}

int main(void) {
    check("Sajjad");        /*fine*/
    char name[]="Sajjad";   
    check(name);            /*fine*/
    char *pointer=malloc(6*sizeof(char));
    pointer="Sajjad";
    check(pointer);         /*fine*/
    return 0;
}