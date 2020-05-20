#include <iostream>
#include <matrix.h>
#include <cmath>
#include <sys/time.h>
#include <time.h>

#define NS_IN_S  1E9
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
Answer:
-0.201885
0.160131
0.262423
-0.288252
*/

// Instert matrix
void insert_matrix(Matrix& A, Matrix& B);

// Normalization ||x||(infinity) = max(|xi|) by i
double norm_inf(Matrix);

int main() {
    // Time
    struct timespec start, stop, duration;
    // Source matrix
    Matrix A(N, N);
    // Matrix A * vector R
    Matrix Ar(N, 1);
    // Vector B(of free member)
    Matrix B(N, 1);
    // Now iteration
    Matrix X(N, 1);
    // Residual vector
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
    insert_matrix(A, B);

    //Input epsilon
    std::cout << "Input Epsilon: ";
    std::cin >> epsilon;

    // K=0 vectors
    std::cout << "Input initial approximation(1 if (1,1,...,1), 0 if (0,0,...,0)): ";
    std::cin >> init;
    if (init == 0) {
        for (int i = 0; i < N; i++) {
            X(i, 0) = 0;
        }
    } else {
        for (int i = 0; i < N; i++) {
            X(i, 0) = 1;
        }
    }

    std::cout << "Basic matrix:" << std::endl;
    std::cout << A;
    std::cout << "Basic vector B:" << std::endl;
    std::cout << B;
    std::cout << "===================================\n";
    // while ||R||(inf) > epsilon do:
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    R = B - (A * X);
    while(norm_inf(R) > epsilon){
        Ar = A*R;
        for(int i = 0; i < N; i++){
            alpha_numerator += R(i,0)*R(i,0);
            alpha_denominator += Ar(i,0)*R(i, 0);
        }
        alpha = alpha_numerator/alpha_denominator;
        X = X + alpha*R;
        R = B - (A*X);
        iteration++;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
    if ((stop.tv_nsec - start.tv_nsec) < 0)
    {
        duration.tv_sec = stop.tv_sec - start.tv_sec - 1;
        duration.tv_nsec = NS_IN_S + stop.tv_nsec - start.tv_nsec;
    }
    else
    {
        duration.tv_sec = stop.tv_sec - start.tv_sec;
        duration.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }
    double result = duration.tv_sec + duration.tv_nsec / NS_IN_S;
    std::cout << "\nVector x(in " << iteration << " iteration) is:\n" << X;
    std::cout << "TIME: " << result;
    return 0;
}

void insert_matrix(Matrix& A, Matrix& B){
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
}

double norm_inf(Matrix vector){
    double max = 0;
    max = std::abs(vector(0,0));
    for(int i = 0; i < N; i++){
        if(max < std::abs(vector(i, 0))){
            max = std::abs(vector(i, 0));
        }
    }
    return max;
}

