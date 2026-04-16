#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int get_floor(const double n) {
	return (int)n;
}

int get_ceil(const double n) {
	// get the floor value then simply add one to it
	return (int)n+1;
}

int main(void) {
	printf("Enter the integer: ");
	int n; scanf("%d", &n);
	if (n<2) {
		printf("False\n");
		return 0;
	}
	// now the parent process will create two child processes and take status from them
	if (!fork()) { /* first child inside the body */
		int sum=0;
		const int start=1, end=get_floor(n/4.0);
		for (int i=start;i<=end;++i) {
			if (n%i==0) {
				sum+=i;
			}
		}
		exit(sum);
	}
	if (!fork()) { /* second child inside the body */
		int sum=0;
		const int start=get_ceil(n/4.0), end=get_ceil(n/2.0);
		for (int i=start;i<=end;++i) {
			if (n%i==0) {
				sum+=i;
			}
		}
		exit(sum);
	}
	/* only parent here */
	int first_status, second_status;
	wait(&first_status);
	int first_sum=WEXITSTATUS(first_status);
	wait(&second_status);
	int second_sum=WEXITSTATUS(second_status);
	first_sum+second_sum==n?printf("True\n"):printf("False\n");
	return 0;
}