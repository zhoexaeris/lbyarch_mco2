#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


void daxpy_c(int n, double A, double* X, double* Y, double* Z) {
    for (int i = 0; i < n; ++i) {
        Z[i] = A * X[i] + Y[i];
    }
}

int main() {
    int n = 10;
    double A = 2.0;
    double X[] = { 1.0, 2.0, 3.0 };
    double Y[] = { 11.0, 12.0, 13.0 };
    double* Z;

    Z = (double*)malloc(n * sizeof(double));
    if (Z == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    daxpy_c(n, A, X, Y, Z);

    printf("Results for C version:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%.2f \n", Z[i]);
    }
    printf("\n");

    free(Z); // Don't forget to free allocated memory

    return 0;
}
