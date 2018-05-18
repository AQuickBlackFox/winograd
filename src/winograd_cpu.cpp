#include <iostream>
#include <vector>
#include <array>

/**
 * Do winograd
 * 
 * G = 
 * {1, 0, 0, \
 * 0.5, 0.5, 0.5, \
 * 0.5, -0.5, 0.5, \
 * 0, 0, 1};
 * 
 * BT = 
 */

constexpr std::array<std::array<float, 3>, 4> G = \
{{
    {1, 0, 0},
    {0.5, 0.5, 0.5},
    {0.5, -0.5, 0.5},
    {0, 0, 1}
}};

constexpr std::array<std::array<float, 4>, 3> GT = \
{{
    {1, 0.5, 0.5, 0},
    {0, 0.5, -0.5, 0},
    {0, 0.5, 0.5, 1}
}};

constexpr std::array<std::array<float, 4>, 4> BT = \
{{
    {1, 0, -1, 0},
    {0, 1, 1, 0},
    {0, -1, 1, 0},
    {0, 1, 0, -1}
}};

constexpr std::array<std::array<float, 4>, 4> B = \
{{
    {1, 0, 0, 0},
    {0, 1, -1, 1},
    {-1, 1, 1, 0},
    {0, 0, 0, -1}
}};

constexpr std::array<std::array<float, 4>, 2> AT = \
{{
    {1, 1, 1, 0},
    {0, 1, -1, -1}
}};

constexpr std::array<std::array<float, 2>, 4> A = \
{{
    {1, 0},
    {1, 1},
    {1, -1},
    {0, 1}
}};


std::array<std::array<float, 4>, 4> doGgGT(std::array<std::array<float, 3>, 3> &g) {
    std::array<std::array<float, 3>, 4> tmp;
    size_t K = 3, M = 4, N = 3;
    for(size_t m = 0; m < M; m++) {
        for(size_t n = 0; n < N; n++) {
            float val = 0.0f;
            for(size_t k = 0; k < K; k++) {
                val += G[m][k] * g[k][n];
            }
            tmp[m][n] = val;
        }
    }


    std::array<std::array<float, 4>, 4> ret;
    K = 3, M = 4, N = 4;
    for(size_t m = 0; m < M; m++) {
        for(size_t n = 0; n < N; n++) {
            float val = 0.0f;
            for(size_t k = 0; k < K; k++) {
                val += tmp[m][k] * GT[k][n];
            }
            ret[m][n] = val;
        }
    }
    return ret;
}

std::array<std::array<float, 4>, 4> doBTdB(std::array<std::array<float, 4>, 4> &d) {
    std::array<std::array<float, 4>, 4> tmp;
    size_t K = 4, M = 4, N = 4;
    for(size_t m = 0; m < M; m++) {
        for(size_t n = 0; n < N; n++) {
            float val = 0.0f;
            for(size_t k = 0; k < K; k++) {
                val += BT[m][k] * d[k][n];
            }
            tmp[m][n] = val;
        }
    }
    
    std::array<std::array<float, 4>, 4> ret;
    for(size_t m = 0; m < M; m++) {
        for(size_t n = 0; n < N; n++) {
            float val = 0.0f;
            for(size_t k = 0; k < K; k++) {
                val += tmp[m][k] * B[k][n];
            }
            ret[m][n] = val;
        }
    }
    return ret;
}

std::array<std::array<float, 4>, 4> doElementMul(std::array<std::array<float, 4>, 4> &g, std::array<std::array<float, 4>, 4> &d) {
    std::array<std::array<float, 4>, 4> ret;
    size_t M = 4, N = 4;
    for(size_t m = 0; m < M; m++) {
        for(size_t n = 0; n < N; n++) {
            ret[m][n] = g[m][n] * d[m][n];
        }
    }
    return ret;
}

std::array<std::array<float, 2>, 2> doATaA(std::array<std::array<float, 4>, 4> &a) {
    std::array<std::array<float, 4>, 2> tmp;
    size_t K = 4, M = 2, N = 4;
    for(size_t m = 0; m < M; m++) {
        for(size_t n = 0; n < N; n++) {
            float val = 0.0f;
            for(size_t k = 0; k < K; k++) {
                val += AT[m][k] * a[k][n];
            }
            tmp[m][n] = val;
        }
    }

    std::array<std::array<float, 2>, 2> ret;
    K = 4, M = 2, N = 2;
    for(size_t m = 0; m < M; m++) {
        for(size_t n = 0; n < N; n++) {
            float val = 0.0f;
            for(size_t k = 0; k < K; k++) {
                val += tmp[m][k] * A[k][n];
            }
            ret[m][n] = val;
        }
    }
    return ret;
}

int main() {

}
