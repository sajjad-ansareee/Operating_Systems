#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define ROWS    10
#define COLUMNS 10

typedef struct {
	int timestamp;
	int data_size;
} Header;

int main(void) {
	int file=open("formatter_gate", O_RDONLY);
	// check what type of request is sent
	int request_code;
	read(file, &request_code, sizeof(int));

	Header header;
	read(file, &header, sizeof(Header));
	if (request_code == 1) {
		printf("\nStatus:\n");
		printf("Timestamp:%d\n", header.timestamp);
		printf("Data Size:%d bytes\n", header.data_size);

	}
	else if (request_code == 2) {
		int data[ROWS][COLUMNS];
		for (int i=0;i<ROWS;++i) {
			read(file, data[i], COLUMNS*sizeof(int));
		}
		printf("\nLogs:\n");
		printf("Timestamp:%d\n", header.timestamp);
		printf("Data Size:%d bytes\n", header.data_size);
		printf("Matrix:\n");
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLUMNS; ++j) {
				printf("%d ", data[i][j]);
			}
			printf("\n");
		}
	}
	close(file);
	return 0;
}