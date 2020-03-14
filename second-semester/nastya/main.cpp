#include <iostream>
#include "dmatrix.h"
#include "dmatrix.cpp"

int main() {
    DMatrix A,At, Iteration;
    A.Ini(4, 4, 4, 4);
    At.Ini(4, 4, 4, 4);
    Iteration.Ini(4, 4, 4, 4);
    for(int i = 0; i < A.n; i++){
        for(int j = 0; j < A.m; j++){ // n=m
            std::cin >> A.data[i][j];
        }
    }
    for(int i = 0; i < A.n; i++){
        for(int j = 0; j < A.m; j++){ // n=m
            std::cout << A.data[i][j];
        }
    }
    At = A.T();
}
