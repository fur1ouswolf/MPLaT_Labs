#include <cmath>

extern "C" {
    double* calculate(double* x, int x_size, double* y) {
        for (int i = 0; i < x_size; i++) {
            y[i] = sin(x[i]);
        }
        return y;
    }
}
