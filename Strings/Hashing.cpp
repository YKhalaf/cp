#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9, p1 = 137, p2 = 277;

long long fp(long long b, long long p, int mod) {
    long long res = 1;
    while (p) {
        if (p & 1) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        p >>= 1;
    }
    return res;
}

int arrMod[] = {
    1000000097, 1000000321, 1000000453, 1000000711, 1000000931, 1000001203,
    1000001351, 1000001539, 1000001773, 1000003373
};

int MOD1, MOD2, ip1, ip2;
pair<int, int> pw[N], ipw[N];

void preCalc() {
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        pw[i].first = 1LL * pw[i - 1].first * p1 % MOD1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % MOD2;
    }
    ip1 = fp(p1, MOD1 - 2, MOD1);
    ip2 = fp(p2, MOD2 - 2, MOD2);
    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        ipw[i].first = 1LL * ipw[i - 1].first * ip1 % MOD1;
        ipw[i].second = 1LL * ipw[i - 1].second * ip2 % MOD2;
    }
}

struct Hashing {
    int n;
    string s; // 0 - indexed
    vector<pair<int, int> > hs, hr; // 1 - indexed
    Hashing() {
    }

    Hashing(string _s) {
        n = _s.size();
        s = _s;
        hs.emplace_back(0, 0);
        hr.emplace_back(0, 0);
        for (int i = 0; i < n; i++) {
            pair<int, int> p;
            p.first = (hs[i].first + 1LL * pw[i].first * s[i] % MOD1) % MOD1;
            p.second = (hs[i].second + 1LL * pw[i].second * s[i] % MOD2) % MOD2;
            hs.push_back(p);
        }

        for (int i = 0; i < n; i++) {
            pair<int, int> p;
            p.first = (hr[i].first + 1LL * pw[i].first * s[n - i - 1] % MOD1) % MOD1;
            p.second = (hr[i].second + 1LL * pw[i].second * s[n - i - 1] % MOD2) % MOD2;
            hr.push_back(p);
        }
    }

    pair<int, int> get_hash(int l, int r) {
        // 1 - indexed
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> ans;
        ans.first = (hs[r].first - hs[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
        ans.second = (hs[r].second - hs[l - 1].second + MOD2) * 1LL * ipw[l - 1].second % MOD2;
        return ans;
    }

    pair<int, int> get_hash() {
        return get_hash(1, n);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(time(0));
    int r = rand() % 10, r2 = rand() % 10;
    while (r2 == r) r2 = rand() % 10;
    MOD1 = arrMod[r], MOD2 = arrMod[r2];

    preCalc();

    string s, p;
    cin >> p >> s;

    Hashing h(s);
    auto hs = Hashing(p).get_hash();

    return 0;
}
