#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

/*
EXAMPLE: 
 | 1  2 -1 | -1 | x0 = 1;
 |-2  3  1 |  0 | x1 = 0;
 | 4 -1 -3 | -2 | x2 = 2;
Dupa pivotare:
 | 1  2 -1   | -1   |   2/7 = 0.2857
 | 0  7 -1   | -2   |   4/7 = 0.5714
 | 0  0 -2/7 | -4/7 |

 */
class Gauss1 {
private:
    int N;
    std::vector<std::vector<float>> Matrix;
    std::vector<float> Arr;
    std::vector<float> X;

public:

    // The first constructor uses an initializer list to initialize the member variables
    Gauss1(int n, std::vector<std::vector<float>> matrix, std::vector<float> arr) : N(n), Matrix(matrix), Arr(arr) {
        X.resize(N); // Allocate space for the vector X
    }

    // The second constructor uses assignment within the constructor body to initialize the member variables
    // Gauss1(int n, std::vector<std::vector<float>> matrix, std::vector<float> arr) {
    //     N = n; 
    //     Matrix = matrix; 
    //     Arr = arr;
    //     X.resize(N); // Allocate space for the vector X
    // }

    void printMatrix() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%10.4lf ", Matrix[i][j]);
            }
            printf("\n");
        }
    }

    void printArray() {
        for (int i = 0; i < N; i++) {
            printf("b[%d] = %10.4lf \n", i, Arr[i]);
        }
    }

    // Function to perform pivoting
    void pivot() {
        for (int k = 0; k < N - 1; k++) {
            double p = 0;
            int l = k;
            for (int i = k; i < N; i++) {
                if (fabs(Matrix[i][k]) > p) {
                    l = i; 
                    p = fabs(Matrix[i][k]);
                }
            }
            if (p == 0) {
                printf("The problem is mathematically ill-posed\n");
                exit(1);
            } else {
                for (int j = k; j < N; j++) {
                    double temp = Matrix[k][j];
                    Matrix[k][j] = Matrix[l][j];
                    Matrix[l][j] = temp; 
                }
                double temp = Arr[k]; 
                Arr[k] = Arr[l]; 
                Arr[l] = temp; 
            }
            for (int i = k + 1; i < N; i++) {
                double p = -Matrix[i][k] / Matrix[k][k];
                for (int j = k; j < N; j++) {
                    Matrix[i][j] = Matrix[i][j] + p * Matrix[k][j];
                }
                Arr[i] = Arr[i] + p * Arr[k];
            }
        }
    }

    void backSubstitution() {
        X[N - 1] = Arr[N - 1] / Matrix[N - 1][N - 1];
        std::cout << "x[" << N - 1 << "]=" << X[N - 1] << std::endl;

        for (int i = N - 2; i >= 0; i--) {
            double s = 0;
            for (int j = i + 1; j < N; j++) {
                s += Matrix[i][j] * X[j];
            }
            X[i] = (Arr[i] - s) / Matrix[i][i];
            printf("x[%d] = %lf \n", i, X[i]);
        }

        printf("The solution to the system of equations is:\n");
        for (int k = 0; k < N; k++) {
            printf("x[%d] = %lf \n", k, X[k]);
        }
    }
};

// main function
int main() {
    int n = 3;
    std::vector<std::vector<float>> a = {
        {1, 2, -1},
        {-2, 3, 1},
        {4, -1, -3}
    };


    // FOR: The problem mathematically ill-posed
    // std::vector<std::vector<float>> a = {
    //     { 2, -1, 1 },
    //     { -4, 2, -2 },
    //     { 4, -2, 4 }
    // };


    std::vector<float> b = {-1, 0, -2};
    // FOR: The problem mathematically ill-posed
    // std::vector<float> b = { 1, -2, 4 };

    Gauss1 gauss1(n, a, b);
    gauss1.printMatrix();
    gauss1.printArray();
    gauss1.pivot();
    printf("After pivoting:\n");
    gauss1.printMatrix();
    gauss1.printArray();
    gauss1.backSubstitution();

    return 0;
}
