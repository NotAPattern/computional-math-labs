#include <iostream>
#include "matrix-master/dist/matrix.h"
#include "matrix-master/dist/matrix.cpp"

#define N 4

int main() {
    Matrix A(N, N);
    Matrix Aiter(N, N);
    Matrix B(N, 1);
    double tetta = 1.4;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){ // n=m
            std::cin >> A(i, j);
        }
    }
    std::cout << std::endl;
    std::cout << "Input vector b: ";
    for(int j = 0; j < N; j++){ // n=m
        std::cin >> B(j, 1);
    }
    std::cout << "Input tetta(iter parametr): ";
    std::cin >> tetta;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            Aiter(i, j) = (A(i, j) / A(i, i)) * tetta;
            if(i == j) {
                Aiter(i, j) = 1 - tetta;
            }
        }

    }

    std::cout << Aiter;
    std::cout << B;
    // fuck off cycles
//    for(int i = 0; i < N; i++){
//        for(int j = 0; j < N; j++){ // n=m
//            std::cout << A(i, j) << " ";
//        }
//        std::cout << std::endl;
//    }
    // std::cout << A;
}
