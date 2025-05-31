#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

T areaPolygon(vector<pt> p) {
    T area = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n-1
    }
    return abs(area);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;

    vector<pt> p(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        p[i] = pt(a, b);
    }

    T area = areaPolygon(p), B = 0;

    // Pick Theorem -> area = I + (B / 2) - 1
    for (int i = 0; i < n; i++) {
        pt p1 = p[i], p2 = p[(i + 1) % n];
        B += gcd(abs(p1.x - p2.x), abs(p1.y - p2.y));
    }

    T two_I = area - B + 2;
    cout << two_I / 2 << ' ' << B << '\n';

    return 0;
}
