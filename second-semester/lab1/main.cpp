#include <iostream>
#include <matrix.h>
#include <cmath>

//Demention of matrix
#define N 4

//Sample matrix 3x3
/*
4x4:
8
-1
-2
0
0
10
-2
2
-1
0
6
2
3
-1
2
12
-2.3
0.5
1.2
-3.7
-----------------------
Answer: x1=
x2=
x3=
x4=
*/

// Instert matrix
void insert_matrix(Matrix& A, Matrix& A_t, Matrix& B, Matrix& X);

// Normalization ||x||(infinity) = max(|xi|) by i
double norm_inf(Matrix vector_plus, Matrix vector);

int main() {
    // Source matrix
    Matrix A(N, N);
    // Transpose matrix
    Matrix A_t(N, N);
    // Vector of A*A(transpose)*R
    Matrix AAr(N, N);
    // Matrix for iteration x(i) = b - x1 - x2 - ... - x(i-1) - x(i+1) - ... - x(n)
    Matrix Ar(N, 1);
    //Matrix A_iteration(N, N);
    // Vector B(of free member)
    Matrix B(N, 1);
    // Now iteration
    Matrix X(N, 1);
    // Next iteration
    Matrix X_next(N, 1);
    // Iteration parametr
    //double tetta = 1.4;
    Matrix R(N,1);
    // Alpha
    double alpha_numerator;
    double alpha_denominator;
    double alpha;
    // Zero or one vectors when K=0
    bool init;
    // Epsilon :)
    double epsilon;
    // Number of iteration
    int iteration = 0;

    // Insert matrix
    insert_matrix(A, A_t, B, X);

//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N + 1; j++) {
//
//        }
//    }

    //Input epsilon
    std::cout << "Input Epsilon: ";
    std::cin >> epsilon;

    // K=0 vectors
    std::cout << "Input initial approximation(1 if (1,1,...,1), 0 if (0,0,...,0)): ";
    std::cin >> init;
    if (init == 0) {
        for (int i = 0; i < N; i++) {
            X(i, 0) = 0;
            X_next(i, 0) = 0;
        }
    } else {
        for (int i = 0; i < N; i++) {
            X(i, 0) = 1;
            X_next(i, 0) = 0;
        }
    }

    //first iteration
    //B = B.transpose();
    R = B - (A*X);
    // R -= B;
    Ar = A*R;
    // AAr = A*A_t*R;
    for(int i = 0; i < N; i++){
        alpha_numerator += R(i,0)*R(i,0);
        alpha_denominator += Ar(i,0)*R(i, 0);
    }
    alpha = alpha_numerator/alpha_denominator;
    X_next = X + alpha*R;

//    for(int l = 0; l < N; l++){
//        for(int m = 0; m < N; m++) {
//            K_plus(l, 0) += (A_k_iter(l, m) * K(m, 0));
//        }
//        K_plus(l, 0) += A_k_iter(l, N);
//    }

    std::cout << "Basic matrix:" << std::endl;
    std::cout << A;
    std::cout << "Basic vector B:" << std::endl;
    std::cout << B;
    std::cout << "Basic vector R:" << std::endl;
    std::cout << R;
    std::cout << "Basic vector Ar:" << std::endl;
    std::cout << Ar;
    std::cout << "Basic vector AAr:" << std::endl;
    std::cout << AAr;
    std::cout << "Alpha:" << std::endl;
    std::cout << alpha;
    std::cout << "===================================\n";
    std::cout << "N = " << iteration << std::endl;
    std::cout << "X(0):\n" << X << std::endl;
    std::cout << "X(1):\n"<< X_next << std::endl;
    iteration++;
    // while ||x^(K+1) - x^(k)||(inf) > epsilon do:
    while(norm_inf(X_next, X) > epsilon){
        X = X_next;
        R = B - (A*X);
        // R -= B;
        Ar = A*R;
        // AAr = A*A_t*R;
        for(int i = 0; i < N; i++){
            alpha_numerator += R(i,0)*R(i,0);
            alpha_denominator += Ar(i,0)*R(i, 0);
        }
        alpha = alpha_numerator/alpha_denominator;
        X_next = X + alpha*R;
        alpha = 0.5*(alpha_numerator/alpha_denominator);
        iteration++;
        std::cout << "===================================\n";
        std::cout << "N = " << iteration << std::endl;
        std::cout << "X(" << iteration - 1 << "):\n" << X << std::endl;
        std::cout << "X(" << iteration << ")\n"<< X_next << std::endl;
    }
    std::cout << "\nVector x(in " << iteration << " iteration) is:\n" << X_next << "\ndifference(in normal):\n" << norm_inf(X_next, X);
    return 0;
}

void insert_matrix(Matrix& A, Matrix& A_t, Matrix& B, Matrix& X){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> A(i, j);
        }
    }
    for(int i = 0; i < N; i++){
        std::cout << "B[" << i + 1 << "]: ";
        std::cin >> B(i,0);
    }
//    for(int i = 0; i < N; i++){
//        std::cout << "X[" << i + 1 << "]: ";
//        std::cin >> X(i,0);
//    }
    //X(0,0) = 0.3;
    //X(1,0) = -0.05;
    //X(2,0) = -0.2;
    //X(3, 0) = 0.3;
    A_t = A.transpose();
}

double norm_inf(Matrix vector_plus, Matrix vector){
    double max = 0;
    Matrix difference(N,1);
    // Find x^(k+1) - x^(k) (k-s iteration)
    for(int i = 0; i < N; i++){
        difference(i,0) = std::abs(vector_plus(i, 0)) - std::abs(vector(i, 0));
    }
    std::cout << "difference:\n" << difference;

    //find max element of normal
    max = std::abs(difference(0,0));
    for(int i = 0; i < N; i++){
        if(max < std::abs(difference(i, 0))){
            max = std::abs(difference(i, 0));
        }
    }
    return max;
}

