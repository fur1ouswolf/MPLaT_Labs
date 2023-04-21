#include "funcsolver.h"

extern "C" {
    void calculate(double* x, int x_size, double* y) {
        for (int i = 0; i < x_size; i++) {
            y[i] = x[i] * x[i];
        }
    }
}



