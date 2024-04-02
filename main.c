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

    int exponent = 20;
    int n = 2 << exponent; // size of vector n (2^n)
    printf("N: 2^%d (%d)\n", exponent, n);

    // Initialize variables
    double A = 2.0;
    double* X = (double*)malloc(n * sizeof(double));
    double* Y = (double*)malloc(n * sizeof(double));
    double* Z_c = (double*)malloc(n * sizeof(double));
    double* Z_asm = (double*)malloc(n * sizeof(double));
    printf("Input A: %.1f\n", A);

    // Initialize X and Y for random values
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        X[i] = (double)rand() / RAND_MAX;
        Y[i] = (double)rand() / RAND_MAX;
    }

    // print first 10 elements of X and Y
    printf("Input X: ");
    for (int i = 0; i < 10; ++i) {
        if (i < 9) {
            printf("%f | ", X[i]);
        }
        else {
            printf("%f \n", X[i]);
        }
    }

    printf("Input Y: ");
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

    // Perform x86-64 Kernel
    LARGE_INTEGER start_time_asm, end_time_asm;
    double total_cpu_time_ASM;

    QueryPerformanceCounter(&start_time_asm);
    daxpy_asm(n, A, X, Y, Z_asm);

    QueryPerformanceCounter(&end_time_asm);
    total_cpu_time_ASM = (double)(end_time_asm.QuadPart - start_time_asm.QuadPart);
    double execution_time_seconds_ASM = total_cpu_time_ASM / cpu_frequency;

    printf("Output Z (ASM): ");
    print_outputs(n, Z_asm);

    // Perform C Kernel
    LARGE_INTEGER start_time_c, end_time_c;
    double total_cpu_time_C;

    // start clock cycle
    QueryPerformanceCounter(&start_time_c);
    daxpy_c(n, A, X, Y, Z_c);

    // end clock cycle
    QueryPerformanceCounter(&end_time_c);

    // compute for total clock cycle and convert to seconds
    total_cpu_time_C = (double)(end_time_c.QuadPart - start_time_c.QuadPart);
    double execution_time_seconds_c = total_cpu_time_C / cpu_frequency;

    printf("Output Z (C): ");
    print_outputs(n, Z_c);

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

    printf("\nTotal Cycles:\n");
    printf("C: %.9f cycles \n", total_cpu_time_C);
    printf("ASM: %.9f cycles \n", total_cpu_time_ASM);

    printf("\nTotal Time:\n");
    printf("C: %.9f seconds \n", execution_time_seconds_c);
    printf("ASM: %.9f seconds \n", execution_time_seconds_ASM);


    // free allocated memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);

    return 0;

}