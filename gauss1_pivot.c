#include <stdio.h>
#include <stdlib.h> // Include for abs() function
#include <math.h>

// Project: Gauss Method 1
// Author: Vasile Daniel DAN 
// Start: Today, 8 June 2024

// Function to print the matrix
void printMatrix(int n, double matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to print the array
void printArray(int n, double arr[n]) {
    for (int i = 0; i < n; i++) {
        printf("b[%d] = %10.4lf \n", i, arr[i]);
    }
}

// Function to perform pivoting
void pivot(int n, double a[n][n], double b[n]) {
    for (int k = 0; k < n - 1; k++) {
        double p = 0;
        int l = k;
        for (int i = k; i < n; i++) {
            if (fabs(a[i][k]) > p) {
                l = i; 
                p = fabs(a[i][k]);
            }
        }
        if (p == 0) {
            printf("The problem is mathematically ill-posed\n");
            exit(1);
        } else {
            for (int j = k; j < n; j++) {
                double temp = a[k][j];
                a[k][j] = a[l][j];
                a[l][j] = temp; 
            }
            double temp = b[k]; 
            b[k] = b[l]; 
            b[l] = temp; 
        }
        for (int i = k + 1; i < n; i++) {
            double p = -a[i][k] / a[k][k];
            for (int j = k; j < n; j++) {
                a[i][j] = a[i][j] + p * a[k][j];
            }
            b[i] = b[i] + p * b[k];
        }
    }
}

// Function to perform back substitution
void backSubstitution(int n, double x[n], double a[n][n], double b[n]) {
    x[n - 1] = b[n - 1] / a[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        double s = 0;
        for (int j = i + 1; j < n; j++) {
            s += a[i][j] * x[j];
        }
        x[i] = (b[i] - s) / a[i][i];
    }

    printf("The solution to the system of equations is:\n");
    for (int k = 0; k < n; k++) {
        printf("x[%d] = %lf \n", k, x[k]);
    }
}

int main() {
    int n = 3;
    double x[3];

    // double a[3][3] = {
    //     { 1, 2, -1 },
    //     { -2, 3, 1 },
    //     { 4, -1, -3 }
    // };

    // FOR: The problem mathematically ill-posed
    double a[3][3] = {
        { 2, -1, 1 },
        { -4, 2, -2 },
        { 4, -2, 4 }
    };

    printf("Initial matrix:\n");
    printMatrix(n, a);

    // double b[3] = { -1, 0, -2 };

    // FOR: The problem mathematically ill-posed
    double b[3] = { 1, -2, 4 };

    printf("Initial vector b:\n");
    printArray(n, b);

    pivot(n, a, b);

    printf("After pivoting:\n");
    printMatrix(n, a);

    printf("Vector b after pivoting:\n");
    printArray(n, b);

    backSubstitution(n, x, a, b);

    return 0;
}
