// GON GON, ZHOE AERIS F.
// RANA, LUIS MIGUEL
// LBYARCH S15

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

// x86-64 kernel function
extern void daxpy_asm(int n, double A, double* X, double* Y, double* Z);

// C kernel function
void daxpy_c(int n, double A, double* X, double* Y, double* Z) {
    for (int i = 0; i < n; ++i) {
        Z[i] = A * X[i] + Y[i];
    }
}

// print first 10 elements of Z
void print_outputs(int n, double* Z) {
	for (int i = 0; i < 10; ++i) {
        if (i < 9) {
            printf("%f | ", Z[i]);
        }
        else {
            printf("%f \n", Z[i]);
        }
	}
}
int main() {

    int exponent = 27;
    int n = 2 << exponent; // size of vector n (2^n)
    printf("N: 2^%d (%d)\n\n", exponent, n);

    // Initialize variables
    double A = 2.0;
    double* X = (double*)malloc(n * sizeof(double));
    double* Y = (double*)malloc(n * sizeof(double));
    double* Z_c = (double*)malloc(n * sizeof(double));
    double* Z_asm = (double*)malloc(n * sizeof(double));
    printf("A --> %.1f\n", A);

    // Initialize X and Y for random values
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        X[i] = (double)rand() / RAND_MAX;
        Y[i] = (double)rand() / RAND_MAX;
    }

    // print first 10 elements of X and Y
    printf("X --> ");
    for (int i = 0; i < 10; ++i) {
        if (i < 9) {
            printf("%f | ", X[i]);
        }
        else {
            printf("%f \n", X[i]);
        }
    }

    printf("Y --> ");
    for (int i = 0; i < 10; ++i) {
        if (i < 9) {
            printf("%f | ", Y[i]);
        }
        else {
            printf("%f \n", Y[i]);
        }
    }
    printf("\n");

    // get elapsed time
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    double cpu_frequency = (double)frequency.QuadPart;
    double total_cpu_time_C = 0.0;
    double total_cpu_time_ASM = 0.0;
    

    printf("Average Execution Times:\n");

    // Perform C Kernel
    for (int i = 0; i < 30; ++i) {
        LARGE_INTEGER start_time_c, end_time_c;

        QueryPerformanceCounter(&start_time_c);
        daxpy_c(n, A, X, Y, Z_c);
        QueryPerformanceCounter(&end_time_c);

        double execution_time_seconds_c = (double)(end_time_c.QuadPart - start_time_c.QuadPart) / cpu_frequency;
        total_cpu_time_C += execution_time_seconds_c;
    }
    printf("C:   %.9f seconds\n", total_cpu_time_C / 30.0);

    // Perform x86-64 Kernel
    for (int i = 0; i < 30; ++i) {
        LARGE_INTEGER start_time_asm, end_time_asm;

        QueryPerformanceCounter(&start_time_asm);
        daxpy_asm(n, A, X, Y, Z_asm);
        QueryPerformanceCounter(&end_time_asm);

        double execution_time_seconds_ASM = (double)(end_time_asm.QuadPart - start_time_asm.QuadPart) / cpu_frequency;
        total_cpu_time_ASM += execution_time_seconds_ASM;
    }
    printf("ASM: %.9f seconds\n", total_cpu_time_ASM / 30.0);

    // Validate the results 
    printf("\nValidating the results...\n");
    bool is_correct = true;
    long int diff = 0;
    for (int i = 0; i < n; ++i) {
        if (Z_c[i] != Z_asm[i]) {
            is_correct = false;
            diff++;
            break;
        }
    }
    if (is_correct) {
        printf("%ld out of %ld elements are equal.\n", n - diff, n);
        printf("Results are correct\n");
    }
    else {
        printf("%ld out of %ld elements are not equal.\n", n - diff, n);
        printf("Results are incorrect\n");
    }

    printf("\nFirst Iteration Results of Z:\n");
    printf("C  : ");
    print_outputs(n, Z_c);
    printf("ASM: ");
    print_outputs(n, Z_asm);

    // free allocated memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);

    return 0;

}