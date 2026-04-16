#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(void) {
	printf("1. Status\n");
	printf("2. Logs\n");
	printf("0. Exit\n");
	printf("Enter option: ");
	int option; scanf("%d", &option);
	if (option>2 || option<0) {
		printf("Wrong option!\n");
	}
	else {
		int pipe=open("query_gate", O_WRONLY, 0644);
		write(pipe, &option, sizeof(int));
		close(pipe);
	}
	return 0;
}