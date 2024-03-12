#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MATRIX_SIZE 4
#define TILE_SIZE 2

void generate_matrix_vector(double *matrix, double *vector, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            matrix[i * size + j] = i + j;
        }
        vector[i] = i;
    }
}

void print_vector(double *vector, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%f ", vector[i]);
    }
    printf("\n");
}

int main() {
    double matrix[MATRIX_SIZE][MATRIX_SIZE];
    double vector[MATRIX_SIZE];
    double result[MATRIX_SIZE];

    generate_matrix_vector((double *)matrix, vector, MATRIX_SIZE);

    printf("Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Vector:\n");
    print_vector(vector, MATRIX_SIZE);
    printf("\n");

    #pragma omp parallel for
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0.0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    printf("Result:\n");
    print_vector(result, MATRIX_SIZE);

    return 0;
}
