#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** matrix_malloc(int size_x, int size_y) {
	int** arr = (int**)malloc(size_x * sizeof(int**));
	for (int i = 0 ; i < size_x; ++i) 
		arr[i] = (int*)malloc(size_y * sizeof(int*));
	return arr;
}

void matrix_free(float** arr, int size_x) {
	for (int i = 0; i < size_x; ++i)
		free(arr[i]);
	free(arr);
}

void matrix_print(float** arr, int size_x, int size_y) {
	printf("Matrix: \n");
	for (int i = 0; i < size_x; ++i) {
		for (int j = 0; j < size_y; ++j)
			printf("%4f ", arr[i][j]);
		printf("\n");
	}
}

int** matrix_read(int* size_x, int* size_y) {
	printf("Enter size: ");
	scanf("%d %d", size_x, size_y);

	int** arr = matrix_malloc(*size_x, *size_y);
	printf("Enter matrix: \n");
	for (int i = 0; i < *size_x; ++i)
		for (int j = 0; j < *size_y; ++j)
			scanf("%d", &arr[i][j]);
	return arr;
}

float** read_data(int count_equ, int count_x) {
	printf("Enter equation system: \n");
	while ((getchar()) != '\n');
	float** mat = (float**)malloc(count_equ * sizeof(float**));
	for (int c = 0; c < count_equ; c++) {
		char str[100];
		mat[c] = (float*)malloc(count_x * sizeof(float*));
		int index;

		// fflush(stdin);
		fgets(str, 100, stdin);
		int junk;
		// while ((junk = getchar()) != '\n' && (junk = getchar()) != EOF);
		// printf("%s\n", str);
		bool flag_sign = true;
		for (int i = 0; i < strlen(str); ++i) {
			if ('0' <= str[i] && str[i] <= '9' || str[i] == 'x') {
				char num[10] = {};
				bool flag_value = false;
				for (int index_num = 0; index_num < 10 && '0' <= str[i] && str[i] <= '9' || str[i] == '.'; ++index_num, ++i) {
					num[index_num] = str[i];
					flag_value = true;
				}
				if (!flag_value)
					num[0] = '1';

				while (str[i++] != 'x');
				char str_index[10] = {};
				for (int ind = 0; i < strlen(str) && '0' <= str[i] && str[i] <= '9'; ++ind, ++i) str_index[ind] = str[i];
				mat[c][atoi(str_index) - 1] = (flag_sign) ? atof(num) : -1 * atof(num);
			}
			if (str[i] == '+')
				flag_sign = true;
			if (str[i] == '-')
				flag_sign = false;
		}
	}
	return mat;
}

int main() {
	int count_x, count_equ;
	printf("Enter count variable x: ");
	scanf("%d", &count_x);
	printf("Enter count equations: ");
	scanf("%d", &count_equ);
	float** mat = read_data(count_equ, count_x);
	matrix_print(mat, count_equ, count_x);
	matrix_free(mat, count_equ);
	return 0;
}