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

    int n = 2 << 25; // size of vector n (2^n)

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

    // Initialize Time Variables
    clock_t start_time, end_time;
    double total_cpu_time_C;
    double total_cpu_time_ASM;


    // Perform C Kernel
    start_time = clock();

    // To Do : Create a function to call the C kernel function 30x and Change N values
    for (int i = 0; i < 30; ++i) {
        daxpy_c(n, A, X, Y, Z_c);
    }

    end_time = clock();
    total_cpu_time_C = ((double)(end_time - start_time)) / CLOCKS_PER_SEC / 30.0;

    printf("C Execution time: %.9f seconds\n", total_cpu_time_C);

    printf("C Kernel Outputs: \n");
    print_outputs(n, Z_c);

    // Perform x86-64 Kernel
    start_time = clock();

    // To Do : Create a function to call the x86-64 kernel function 30x and Change N values
    for (int i = 0; i < 30; ++i) {
        daxpy_asm(n, A, X, Y, Z_asm);
    }

    end_time = clock();
    total_cpu_time_ASM = ((double)(end_time - start_time)) / CLOCKS_PER_SEC / 30.0;

    printf("\n\nASM Execution time: %9f seconds\n", total_cpu_time_ASM);

    printf("ASM Kernel Outputs: \n");
    print_outputs(n, Z_asm);
    
    // Validate the results 
    printf("\n\nValidating the results...\n")
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