#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7, matrix_size = 2;

struct matrix {
    int mat[matrix_size][matrix_size] = {
        {1, 0},
        {0, 1}
    };

    matrix friend operator *(const matrix &a, const matrix &b) {
        matrix c;
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                c.mat[i][j] = 0;
                for (int u = 0; u < matrix_size; u++) {
                    c.mat[i][j] += (1LL * a.mat[i][u] * b.mat[u][j]) % mod;
                    c.mat[i][j] %= mod;
                }
            }
        }
        return c;
    }
};

matrix fp(matrix b, long long p) {
    matrix r;
    for (int i = 0; i < matrix_size; i++) {
        r.mat[i][i] = 1;
    }

    while (p) {
        if (p & 1) r = r * b;
        b = b * b;
        p >>= 1;
    }

    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    return 0;
}
