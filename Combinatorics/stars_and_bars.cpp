#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5, mod = 1e9 + 7;
vector<int> fact(N + 5), inv(N + 5);

int fp(int b, int p) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res = (1LL * res * b) % mod;
        }
        b = (1LL * b * b) % mod;
        p >>= 1;
    }
    return res;
}

void preCalc() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (1LL * i * fact[i - 1]) % mod;
        inv[i] = fp(fact[i], mod - 2);
    }
}

int nCr(int n, int r) {
    if (r > n) return 0;
    return (1LL * ((1LL * fact[n] * inv[r]) % mod) * inv[n - r]) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preCalc();

    int n, m;
    cin >> n >> m;
    int stars = n - 1;
    int bars = m;

    // x1 + x2 + x3 + ... + xn = m
    cout << nCr(stars + bars, bars) % mod << '\n';

    return 0;
}
