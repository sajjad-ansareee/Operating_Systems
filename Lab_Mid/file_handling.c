#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *arg[]) {
    // open(file_name, flags)
    int file_descriptor=open("read_file.txt", O_RDONLY, 0777);
    const int buffer_size=1024;
    char buffer[buffer_size];
    // read(file_descriptor, (void*)buffer, buffer_size)
    int read_count=read(file_descriptor, (void*)buffer, buffer_size);
    printf("%s\n", buffer);
    int line_count=0;
    for (int i=0; i<read_count; ++i) {
        if (buffer[i]=='\n') {
            line_count+=1;
        }
    }
    printf("%d\n", line_count);
    // close(file_descriptor
    close(file_descriptor);
    file_descriptor=open("write_file.txt", O_WRONLY|O_APPEND|O_CREAT, 0644);    /* append data in write_file.txt */
    char output_count;
    if (line_count>=0 && line_count<=9) {
        output_count=line_count+'0';
    }
    // write(file_descriptor, (const void*)buffer, buffer_size)
    int write_count=write(file_descriptor, &output_count, sizeof(char));
    printf("Successfully written %d bytes to file\n", write_count);
    close(file_descriptor);
    return 0;
}