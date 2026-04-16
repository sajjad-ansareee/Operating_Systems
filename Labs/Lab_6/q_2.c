#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	const int read_file=open("input.txt", O_RDONLY, 0444); /* file opened for reading purposes only */
	const int write_file=open("output.txt", O_WRONLY, 0666); /* file opened for writing purposes only */
	dup2(read_file, STDIN_FILENO);
	dup2(write_file, STDOUT_FILENO);
	close(read_file);
	close(write_file);
	// int n; scanf("%d", &n);
	// printf("%d", n);
	// scanf("%d", &n);
	// printf("%d", n);
	// // so the pattern here is that pointer moves forward on reading so read until the EOF
	int sum=0, n;
	while (scanf("%d", &n)==1) {
		sum+=n;
	}
	printf("%d", sum);
	return 0;
}