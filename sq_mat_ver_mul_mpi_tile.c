#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

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

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != MATRIX_SIZE) {
        if (rank == 0)
            printf("Number of processes must be equal to %d\n", MATRIX_SIZE);
        MPI_Finalize();
        return 1;
    }

    double matrix[MATRIX_SIZE][MATRIX_SIZE];
    double vector[MATRIX_SIZE];
    double local_result[TILE_SIZE] = {0};
    double result[MATRIX_SIZE] = {0};

    if (rank == 0) {
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
    }

    MPI_Bcast(vector, MATRIX_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < MATRIX_SIZE; i += TILE_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            local_result[j % TILE_SIZE] += matrix[i + rank][j] * vector[j];
        }
    }

    MPI_Reduce(local_result, result, MATRIX_SIZE, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result:\n");
        print_vector(result, MATRIX_SIZE);
    }

    MPI_Finalize();
    return 0;
}
