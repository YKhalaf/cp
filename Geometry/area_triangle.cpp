#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

T areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    double x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    cout << fixed << setprecision(9) << areaTriangle({x1, y1}, {x2, y2}, {x3, y3}) << '\n';

    return 0;
}
