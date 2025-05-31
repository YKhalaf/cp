#include <bits/stdc++.h>
using namespace std;

long long ans;

struct node {
    map<char, int> nxt;

    int &operator[](char c) {
        return nxt[c];
    }
};

struct trie {
    vector<node> t;

    int new_node() {
        t.push_back(node());
        return t.size() - 1;
    }

    trie() {
        t.clear();
        new_node();
    }

    void update(string &s, int op) {
        int u = 0;
        for (auto c: s) {
            if (!t[u][c]) {
                ans++;
                t[u][c] = new_node();
            }
            u = t[u][c];
        }
    }
};
