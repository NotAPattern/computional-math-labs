#include <iostream>
#include "matrix-master/dist/matrix.h"
#include "matrix-master/dist/matrix.cpp"

#define N 4

int main() {
    Matrix A(N, N);
    Matrix At(N, N);
    Matrix Acomposion(N, N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){ // n=m
            std::cin >> A(i, j);
        }
    }
    // fuck off cycles
//    for(int i = 0; i < N; i++){
//        for(int j = 0; j < N; j++){ // n=m
//            std::cout << A(i, j) << " ";
//        }
//        std::cout << std::endl;
//    }
    std::cout << A;
    At = A.transpose();
    Acomposion = At*A;
}
