#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matVecMulSeqOmp(int **mat, int *vec, int *res, int r, int c) {
    #pragma omp parallel for
    for (int i = 0; i < r; i++) {
        res[i] = 0;
        for (int j = 0; j < c; j++) {
            res[i] = res[i] + mat[i][j] * vec[j];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <rows> <cols>\n", argv[0]);
        return 1;
    }
    int r = atoi(argv[1]);
    int c = atoi(argv[2]);

    //Dynamically allocating the memory for matrix, vector, and result
    int **mat = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        mat[i] = (int *)malloc(c * sizeof(int));
    }
    int *vec = (int *)malloc(c * sizeof(int));
    int *res = (int *)malloc(r * sizeof(int));

    // Genearte random values
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = rand() % 10; //b/w 0 to 9
        }
    }
    for (int i = 0; i < c; i++) {
        vec[i] = rand() % 10; 
    }

    matVecMulSeqOmp(mat, vec, res, r, c);

    // Output 
    printf("Result:\n");
    for (int i = 0; i < r; i++) 
    {
    	printf("%d ", res[i]);
    }
        printf("\n");
  
    // Free memory
    for (int i = 0; i < r; i++) {
        free(mat[i]);
    }
    free(mat);
    free(vec);
    free(res);

    return 0;
}

