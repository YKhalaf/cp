#include <bits/stdc++.h>
using namespace std;

// Sieve of Eratosthenes O(n log long n)

vector<bool> isPrime(N + 1, true);

void SieveEratosthenes() {
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (isPrime[i] && (long long) i * i <= N) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
}
