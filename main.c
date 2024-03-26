#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// C kernel function
void daxpy_c(int n, double A, double* X, double* Y, double* Z) {
    for (int i = 0; i < n; ++i) {
        Z[i] = A * X[i] + Y[i];
    }
}

int main() {
    int n = 2 << 20; // size of vector n (2^n)
    double A = 2.0;
    double* X = (double*)malloc(n * sizeof(double));
    double* Y = (double*)malloc(n * sizeof(double));
    double* Z = (double*)malloc(n * sizeof(double));

    // initialize X and Y for random values
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        X[i] = (double)rand() / RAND_MAX;
        Y[i] = (double)rand() / RAND_MAX;
    }

    // perform C kernel
    clock_t start_time = clock(); // starting run time
    daxpy_c(n, A, X, Y, Z);
    clock_t end_time = clock(); // ending run time
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // calculate total time in seconds


    // print first 10 elements of Z
    printf("Results for C version:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%.2f \n", Z[i]);
    }

    printf("C Execution time: %.9f seconds\n", total_time);

    // free allocated memory
    free(X);
    free(Y);
    free(Z);

    return 0;
}
