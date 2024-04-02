#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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
            printf("%f |", Z[i]);
        }
        else {
            printf("%f \n", Z[i]);
        }
	}
}
int main() {

    int n = 2 << 20; // size of vector n (2^n)

    // Initialize variables
    double A = 2.0;
    double* X = (double*)malloc(n * sizeof(double));
    double* Y = (double*)malloc(n * sizeof(double));
    double* Z_c = (double*)malloc(n * sizeof(double));
    double* Z_asm = (double*)malloc(n * sizeof(double));

    // Initialize X and Y for random values
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        X[i] = (double)rand() / RAND_MAX;
        Y[i] = (double)rand() / RAND_MAX;
    }

    // Perform C Kernel
    unsigned __int64 start_time_c, end_time_c;
    double total_cpu_time_C;

    // start clock cycle
    start_time_c = __rdtsc();

    for (int i = 0; i < 30; ++i) {
        daxpy_c(n, A, X, Y, Z_c);
    }

    // end clock cycle
    end_time_c = __rdtsc();

    // compute for total clock cycle and convert to seconds
    total_cpu_time_C = (double)(end_time_c - start_time_c) / 30.0;
    double cpu_frequency = 2.9e9; // change to your CPU base speed
    double execution_time_seconds_c = total_cpu_time_C / cpu_frequency;

    printf("C Kernel Outputs: \n");
    print_outputs(n, Z_c);

    printf("C Total Cycles: %.9f cycles \n", total_cpu_time_C);
    printf("C Execution time: %.9f seconds\n\n", execution_time_seconds_c);

    // Perform x86-64 Kernel
    unsigned __int64 start_time_asm, end_time_asm;
    double total_cpu_time_ASM;

    start_time_asm = __rdtsc();

    for (int i = 0; i < 30; ++i) {
        daxpy_asm(n, A, X, Y, Z_asm);
    }

    end_time_asm = __rdtsc();
    total_cpu_time_ASM = (double)(end_time_asm - start_time_asm) / 30.0;
    double execution_time_seconds_asm = total_cpu_time_ASM / cpu_frequency;

    printf("ASM Kernel Outputs: \n");
    print_outputs(n, Z_asm);

    printf("ASM Total Cycles: %.9f cycles\n", total_cpu_time_ASM);
    printf("ASM Execution time: %.9f seconds\n", execution_time_seconds_asm);;
    
    // Validate the results 
    printf("\n\nValidating the results...\n");
    bool is_correct = true;
    for (int i = 0; i < 10; ++i) {
		if (Z_c[i] != Z_asm[i]) {
			is_correct = false;
			break;
		}
	}
    if (is_correct) {
        printf("Results are correct\n");
    }
    else {
        printf("Results are incorrect\n");
    }

    // free allocated memory
    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);

    return 0;

}