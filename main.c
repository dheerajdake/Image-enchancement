/* Author: Dheeraj Dake
 * Date:   10/31/16
 * Description: Given an MxN array, it prints an MxN array with the neighbouring element count for
 * 				each element of the array
 * 				For example, if the user input MxN array is
 * 				1 1 2
 * 				1 1 1
 * 				2 2 1
 * 				then the array returned is
 * 				3 4 0
 * 				3 5 3
 * 				1 1 2
 *
 * 				User inputs M,N and the elements of the array
 */
#include<stdio.h>
#include<stdlib.h>

int rows, columns;
int **createMatrix(int rows, int columns);	//creates a matrix with given rows and columns
int **paddedMatrix(int **matrix, int rows, int columns); //creates a padded matrix with 0's around the matrix
void fillMatrix(int **matrix); //fills the matrix with user elements
void printMatrix(int **matrix, int rows, int columns); //prints the matrix
int **countElements(int **padded_matrix, int **matrix); //counts the neighbouring element and replaces the count for
														//each element in the original matrix

int main() {
	setbuf(stdout, NULL);
	printf("Counting nearest neighbours of an array\n");
	printf("Enter M and N for size of array MxN: ");

	//Input the rows and columns
	scanf("%d %d", &rows, &columns);

	//Create a matrix of the given dimensions
	int **matrix = createMatrix(rows, columns);

	//Fill the matrix
	printf("Enter the elements of the matrix[>0]: ");
	fillMatrix(matrix);
	printMatrix(matrix, rows, columns);

	//Create a zero padding around the matrix
	printf("Matrix after padding it: \n");
	int **padded_matrix = paddedMatrix(matrix, rows + 2, columns + 2);
	printMatrix(padded_matrix, rows + 2, columns + 2);

	//Count the neighbouring elements and replace them in the final matrix
	printf("Final matrix after counting neighbours: \n");
	int **final_matrix = countElements(padded_matrix, matrix);
	printMatrix(final_matrix, rows, columns);

	//Free memory
	int f;
	for(f=0; f<rows; f++)
	{
		free(matrix[f]);
		free(padded_matrix[f]);
		free(final_matrix[f]);
	}

	free(matrix);
	free(padded_matrix);
	free(final_matrix);
	return 0;
}

int **createMatrix(int rows, int columns) {
	int **matrix = (int **) calloc(rows, sizeof(int *)); //create rows
	int a;
	for (a = 0; a < columns; a++) {
		matrix[a] = (int *) calloc(columns, sizeof(int));
	}
	return matrix;
}

void printMatrix(int **matrix, int rows, int columns) {
	int r, c;
	for (r = 0; r < rows; r++) {
		for (c = 0; c < columns; c++) {
			printf("%d ", matrix[r][c]);
		}
		printf("\n");
	}
}

void fillMatrix(int **matrix) {
	int r, c;
	for (r = 0; r < rows; r++) {
		for (c = 0; c < columns; c++) {
			scanf("%d ", &matrix[r][c]);
		}
	}
	printf("Filled up\n");
}

int **paddedMatrix(int **matrix, int rows, int columns) {
	int **_matrix = (int **) calloc(rows, sizeof(int *)); //create rows
	int a;
	for (a = 0; a < columns; a++) {
		_matrix[a] = (int *) calloc(columns, sizeof(int));
	}

	//Place the user matrix into the zero matrix
	int r, c;
	for (r = 0; r < rows - 2; r++) {
		for (c = 0; c < columns - 2; c++) {
			_matrix[r + 1][c + 1] = matrix[r][c];
		}
	}
	return _matrix;
}

int **countElements(int **padded_matrix, int **matrix) {
	int r, c, count;
	for (r = 0; r < rows; r++) {
		for (c = 0; c < columns; c++) {
			count = 0;
			int r1, c1;
			for (r1 = 0; r1 < 3; r1++) {
				for (c1 = 0; c1 < 3; c1++) {
					if ((r1 == 1) && (c1 == 1)) {
					} else if (padded_matrix[r + r1][c + c1]
							== padded_matrix[r + 1][c + 1]) {
						count++;
					}
				}
			}
			matrix[r][c] = count;
		}
	}
	return matrix;
}
