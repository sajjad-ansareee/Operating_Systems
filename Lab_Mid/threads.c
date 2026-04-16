#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#define ROW 3
#define COLUMN 3

typedef struct{
    int row_start;
    int column_start;
    int matrix[ROW][COLUMN];
} ThreadArgument;

void *thread_function(void *argument) {
    ThreadArgument *thread_argument=(ThreadArgument*)argument;
    int *sum=malloc(sizeof(int));
    *sum=0;
    // int sum=0;
    for (int i=thread_argument->row_start; i<ROW; ++i) {
        for (int j=thread_argument->column_start; j<COLUMN; ++j) {
            (*sum)+=thread_argument->matrix[i][j];
        }
    }
    printf("Value inside the function: %d\n", *sum);
    // unsigned long *return_value=(unsigned long*)&sum;
    return (void*)sum;
}

int main(int argc, char *arg[]) {
    ThreadArgument *thread_argument=malloc(sizeof(ThreadArgument));
    for (int i=0; i<ROW; ++i) {
        for (int j=0; j<COLUMN; ++j) {
            thread_argument->matrix[i][j]=j;
        }
    }
    // for (int i=0; i<ROW; ++i) {
    //     for (int j=0; j<COLUMN; ++j) {
    //         printf("%d ", thread_argument->matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    thread_argument->row_start=1;
    thread_argument->column_start=0;
    pthread_t thread_1, thread_2;
    /* pthread_create(pthread *thread, void *attribute, void *thread_function, void *function_argument) */
    pthread_create(&thread_1, NULL, thread_function, thread_argument);
    void *thread_return_value;
    /* pthread_join(pthread *thread, void **return_value) */
    pthread_join(thread_1, &thread_return_value);
    int *answer=(int*)thread_return_value;
    printf("%d\n", *answer);
    free(thread_argument);
    thread_argument=NULL;
    free(answer);
    answer=NULL;
    return 0;
}