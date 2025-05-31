#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n;) {
        if (s[i] == s[j]) {
            pi[i] = ++j;
            i++;
        } else if (!j) {
            i++;
        } else {
            j = pi[j - 1];
        }
    }
    return pi;
}

int kmp(string &s, string &p) {
    int n = s.size(), m = p.size(), cnt = 0;
    if (m > n) return 0;
    vector<int> pi = prefix_function(p);
    for (int i = 0, j = 0; i < n;) {
        if (s[i] == p[j]) {
            i++, j++;
            if (j == m) {
                cnt++;
                j = pi[j - 1];
            }
        } else if (!j) {
            i++;
        } else {
            j = pi[j - 1];
        }
    }
    return cnt;
}