#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

bool half(pt p) {
    // true if in blue half
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

// around origin
void polarSort(vector<pt> &v) {
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w));
    });
}

// around point o
void polarSortAround(pt o, vector<pt> &v) {
    sort(v.begin(), v.end(), [o](pt v, pt w) {
        return make_tuple(half(v - o), 0) < make_tuple(half(w - o), cross(v - o, w - o));
    });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    return 0;
}
