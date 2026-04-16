#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct {
	int first;
	int second;
} Pair;

typedef struct {
	int **matrix;
	int row_start;
	int row_end;
	int column_start;
	int column_end;
	int matrix_average;
} ThreadArgument;

typedef struct {
	int timestamp;
	int data_size;
} Header;

void display_matrix(int **matrix, int rows, int columns) {
	if (matrix==NULL) {
		return;
	}
	for (int i=0; i<rows; ++i) {
		for (int j=0; j<columns; ++j) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

Pair get_children_values() {
	Pair values={0, 0};
	int parent_child_1[2], parent_child_2[2];
	pipe(parent_child_1);
	pipe(parent_child_2);
	// first child
	if (!fork()) {
		int child_grand_1[2], child_grand_2[2];
		pipe(child_grand_1);
		pipe(child_grand_2);
		// first grand child
		if (!fork()) {
			srand(time(NULL)^getpid()); /* same numbers were being generated */
			int number=rand()%101;
			close(child_grand_2[0]);
			close(child_grand_2[1]);
			close(child_grand_1[0]);
			write(child_grand_1[1], &number, sizeof(int));
			close(child_grand_1[0]);
			exit(0);
		}
		// second grand child
		if (!fork()) {
			srand(time(NULL)^getpid());
			int number=rand()%101;
			close(child_grand_1[0]);
			close(child_grand_1[1]);
			close(child_grand_2[0]);
			write(child_grand_2[1], &number, sizeof(int));
			close(child_grand_2[0]);
			exit(0);
		}
		close(parent_child_2[0]);
		close(parent_child_2[1]);
		close(parent_child_1[0]);
		close(child_grand_1[1]);
		close(child_grand_2[1]);
		int first_child_number, second_child_number;
		read(child_grand_1[0], &first_child_number, sizeof(int));
		read(child_grand_2[0], &second_child_number, sizeof(int));
		int number=(first_child_number+second_child_number)/2;
		close(child_grand_1[0]);
		close(child_grand_2[0]);
		write(parent_child_1[1], &number, sizeof(int));
		close(parent_child_1[1]);
		exit(0);
	}

	// second child
	if (!fork()) {
		int child_grand_3[2], child_grand_4[2];
		pipe(child_grand_3);
		pipe(child_grand_4);
		// third grand child
		if (!fork()) {
			srand(time(NULL)^getpid());
			int number=rand()%101;
			close(child_grand_4[0]);
			close(child_grand_4[1]);
			close(child_grand_3[0]);
			write(child_grand_3[1], &number, sizeof(int));
			close(child_grand_3[0]);
			exit(0);
		}
		// fourth grand child
		if (!fork()) {
			srand(time(NULL)^getpid());
			int number=rand()%101;
			close(child_grand_3[0]);
			close(child_grand_3[1]);
			close(child_grand_4[0]);
			write(child_grand_4[1], &number, sizeof(int));
			close(child_grand_4[0]);
			exit(0);
		}
		close(parent_child_1[0]);
		close(parent_child_1[1]);
		close(parent_child_2[0]);
		close(child_grand_3[1]);
		close(child_grand_4[1]);
		int first_child_number, second_child_number;
		read(child_grand_3[0], &first_child_number, sizeof(int));
		read(child_grand_4[0], &second_child_number, sizeof(int));
		int number=(first_child_number+second_child_number)/2;
		close(child_grand_3[0]);
		close(child_grand_4[0]);
		write(parent_child_2[1], &number, sizeof(int));
		close(parent_child_2[1]);
		exit(0);
	}

	// parent
	close(parent_child_1[1]);
	close(parent_child_2[1]);
	int first_child_number, second_child_number;
	read(parent_child_1[0], &first_child_number, sizeof(int));
	read(parent_child_2[0], &second_child_number, sizeof(int));
	// printf("%d %d\n", first_child_number, second_child_number);
	close(parent_child_1[0]);
	close(parent_child_2[0]);
	wait(NULL);
	wait(NULL);
	values.first=first_child_number;
	values.second=second_child_number;
	return values;
}

int get_average(int **matrix, const int rows, const int columns) {
	if (matrix==NULL) {
		return 0;
	}
	int sum=0;
	for (int i=0; i<rows; ++i) {
		for (int j=0; j<columns; ++j) {
			sum+=matrix[i][j];
		}
	}
	int total_cells=rows*columns;
	return (sum/total_cells);
}

void *remove_critical(void *argument) {
	ThreadArgument *data=(ThreadArgument*)argument;
	for (int i=data->row_start; i<data->row_end; ++i) {
		for (int j=data->column_start; j<data->column_end; ++j) {
			const int critical_value=80;
			if (data->matrix[i][j]>=critical_value) {
				data->matrix[i][j]=data->matrix_average;
				// data->matrix[i][j]=0;
			}
		}
	}
	return NULL;
}

#define ROWS	10
#define COLUMNS	10

int main(void) {
	int **matrix=malloc(ROWS*sizeof(int*));
	for (int i=0; i<ROWS; ++i) {
		matrix[i]=malloc(COLUMNS*sizeof(int));
	}
	for (int i=0; i<10; i+=2) {
		for (int j=0; j<10; j+=1) {
			const Pair values=get_children_values();
			matrix[i][j]=values.first;
			matrix[i+1][j]=values.second;
		}
	}
	pthread_t first_thread, second_thread, third_thread, fourth_thread;
	ThreadArgument data={.matrix=matrix, .row_start=0, .row_end=5, .column_start=0, .column_end=5,
		.matrix_average=get_average(matrix, ROWS, COLUMNS)};
	pthread_create(&first_thread, NULL, remove_critical, &data);
	data.row_start=0; data.row_end=5; data.column_start=5, data.column_end=10;
	pthread_create(&second_thread, NULL, remove_critical, &data);
	data.row_start=5; data.row_end=10; data.column_start=0, data.column_end=5;
	pthread_create(&third_thread, NULL, remove_critical, &data);
	data.row_start=5; data.row_end=10; data.column_start=5, data.column_end=10;
	pthread_create(&fourth_thread, NULL, remove_critical, &data);
	pthread_join(first_thread, NULL);
	pthread_join(second_thread, NULL);
	pthread_join(third_thread, NULL);
	pthread_join(fourth_thread, NULL);
	display_matrix(matrix, ROWS, COLUMNS);

	int a_b[2], b_c[2];
	pipe(a_b);
	pipe(b_c);
	// Process B
	if (!fork()) {
		close(a_b[1]);
		close(b_c[0]);
		int buffer[ROWS][COLUMNS];
		// read matrix from A as it is in heap
		for (int i=0;i<ROWS;++i) {
			read(a_b[0], buffer[i], COLUMNS*sizeof(int));
		}
		close(a_b[0]);
		for (int i=0;i<ROWS;++i) {
			for (int j=0;j<COLUMNS;++j) {
				buffer[i][j]+=5;
			}
		}
		// send encrypted matrix to C
		for (int i=0;i<ROWS;++i) {
			write(b_c[1], buffer[i], COLUMNS*sizeof(int));
		}
		close(b_c[1]);
		exit(0);
	}
	// Process C
	if (!fork()) {
		close(a_b[0]);
		close(a_b[1]);
		close(b_c[1]);
		int buffer[ROWS][COLUMNS];
		for (int i=0;i<ROWS;++i) {
			read(b_c[0], buffer[i], COLUMNS*sizeof(int));
		}
		close(b_c[0]);

		const Header header={.timestamp=(int)time(NULL), .data_size=ROWS*COLUMNS*sizeof(int)};
		const int file=open("vaultDB", O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if (file==-1) {
			perror("open failed");
			exit(1);
		}
		write(file, &header, sizeof(Header));
		for (int i=0;i<ROWS;++i) {
			ssize_t bytes=write(file, buffer[i], COLUMNS*sizeof(int));
			printf("C: row %d wrote %p bytes", i, &bytes);
		}
		close(file);
		exit(0);
	}
	// Process A
	close(b_c[0]);
	close(b_c[1]);
	close(a_b[0]);
	for (int i=0;i<ROWS;++i) {
		write(a_b[1], matrix[i], COLUMNS*sizeof(int));
	}
	close(a_b[1]);
	wait(NULL);
	wait(NULL);




	mkfifo("query_gate", 0644);
	mkfifo("formatter_gate", 0644);
	while (1) {
		// blocked until dashboard connects
		const int query_file=open("query_gate", O_RDONLY);
		int request_code;
		read(query_file, &request_code, sizeof(int));
		close(query_file);

		if (request_code == 0) {
			break;;
		}

		// open vaultDB
		const int db_file = open("vaultDB", O_RDONLY);
		Header header;
		read(db_file, &header, sizeof(Header));

		if (!fork()) {
			execl("./formatter", "formatter", NULL);
			exit(0);
		}

		const int formatter_file = open("formatter_gate", O_WRONLY);

		if (request_code == 1) {
			write(formatter_file, &request_code, sizeof(int));
			write(formatter_file, &header, sizeof(Header));
		}
		else if (request_code == 2) {
			int encrypted_matrix[ROWS][COLUMNS];
			for (int i=0;i<ROWS;++i) {
				read(db_file, encrypted_matrix[i], COLUMNS*sizeof(int));
			}
			write(formatter_file, &request_code, sizeof(int));
			write(formatter_file, &header, sizeof(Header));
			for (int i=0;i<ROWS;++i) {
				write(formatter_file, encrypted_matrix[i], COLUMNS*sizeof(int));
			}
		}
		close(db_file);
		close(formatter_file);
		wait(NULL);
	}
	return 0;
}