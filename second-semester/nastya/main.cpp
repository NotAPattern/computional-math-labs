#include <iostream>
#include "matrix-master/dist/matrix.h"
#include "matrix-master/dist/matrix.cpp"
#include <cmath>
#define N 3
/*
9.2
2.5
-3.7
-17.5
0.9
9.0
0.2
4.4
4.5
-1.6
-10.3
-22.1
 */

double norm_inf(Matrix vector_plus, Matrix vector);

int main() {
    Matrix A(N, N + 1);
    Matrix A_k_iter(N, N + 1);
    Matrix K(N, 1);
    Matrix K_plus(N, 1);
    double tetta = 1.4;
    bool init;
    double epsilon;
    int iteration = 0;
    //A size is 4x5(5 is vector b)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            std::cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> A(i, j);
        }
    }

    std::cout << "Input tetta(iter parametr): ";
    std::cin >> tetta;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            A_k_iter(i, j) = (A(i, j) / A(i, i)) * tetta;
            if (i == j) {
                A_k_iter(i, j) = 1 - tetta;
            }
        }
    }

    std::cout << "Input Epsilon: ";
    std::cin >> epsilon;

    std::cout << "Input initial approximation(1 if (1,1,...,1), 0 if (0,0,...,0)): ";
    std::cin >> init;
    if (init == 0) {
        for (int i = 0; i < N; i++) {
            K(i, 0) = 0;
            K_plus(i, 0) = 0;
        }
    } else {
        for (int i = 0; i < N; i++) {
            K(i, 0) = 1;
            K_plus(i, 0) = 0;
        }
    }

    /*K_plus(0,0) += (A_k_iter(0,0) * K(0,0));
    K_plus(0,0) += A_k_iter(0,1) * K(1,0);
    K_plus(0,0) += A_k_iter(0,2) * K(2,0);
    K_plus(0,0) += A_k_iter(0,3);*/


    //first iteration
    for(int l = 0; l < N; l++){
        for(int m = 0; m < N; m++) {
            K_plus(l, 0) -= (A_k_iter(l, m) * K(m, 0));
        }
        K_plus(l, 0) += A_k_iter(l, N);
//        std::cout << K_plus(i,0);
//        std::cout << "================" << std::endl;
//        std::cout << A_k_iter(i, N + 1) * K(i, 0);
    }

    std::cout << A_k_iter;

    while(norm_inf(K_plus, K) > epsilon){
        K = K_plus;
        for(int l = 0; l < N; l++){
            for(int m = 0; m < N; m++) {
                K_plus(l, 0) += (A_k_iter(l, m) * K(m, 0));
            }
            K_plus(l, 0) += A_k_iter(l, N);
        }
        iteration++;
        std::cout << "N = " << iteration << std::endl;
        std::cout << "k:\n" << K << std::endl;
        std::cout << "k+1:\n"<<K_plus << std::endl;
    }
    return 0;
}

double norm_inf(Matrix vector_plus, Matrix vector){
    double min = 0;
    Matrix difference(N,1);
    difference = (vector_plus - vector);
    std::cout << "difference:\n" << difference;
    /*for(int i = 0; i < N; i++){
        difference = (vector_plus - vector);

        //difference(i, 0) = B_k_iter();
    }*/
    min = std::abs(difference(0,0));
    for(int i = 0; i < N; i++){
        if(min > std::abs(difference(i, 0))){
            min = std::abs(difference(i, 0));
        }
    }
    return min;
}