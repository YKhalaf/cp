#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(const pt &p) {
    return p.x * p.x + p.y * p.y;
}

pt perp(const pt &p) {
    return {-p.y, p.x};
}

T dot(const pt &v, const pt &w) {
    return v.x * w.x + v.y * w.y;
}

T cross(const pt &v, const pt &w) {
    return v.x * w.y - v.y * w.x;
}

struct line {
    pt v;  // direction vector
    T c;   // cross(v, p) = c for any p on the line

    // From direction vector v and offset c
    line(const pt &v, T c) : v(v), c(c) {}

    // From equation a*x + b*y - c = 0
    line(T a, T b, T c) : v({b, -a}), c(-c) {}

    // From points P and Q
    line(const pt &p, const pt &q) : v(q - p), c(cross(v, p)) {}

    // Which side of the line p is on (>0 left, <0 right)
    T side(const pt &p) const {
        return cross(v, p) - c;
    }

    // Distance from p to this line
    T dist(const pt &p) const {
        return fabsl(side(p)) / abs(v);
    }

    // Line perpendicular through point p
    line perpThrough(const pt &p) const {
        return {p, p + perp(v)};
    }

    // Translate the line by vector t
    line translate(const pt &t) const {
        return {v, c + cross(v, t)};
    }

    // Shift the line to the left by distance dist
    line shiftLeft(T dist) const {
        return {v, c + dist * abs(v)};
    }

    // Project p onto this line
    pt proj(const pt &p) const {
        return p - perp(v) * side(p) / sq(v);
    }

    // Reflect p across this line
    pt refl(const pt &p) const {
        return p - perp(v) * (T)2.0 * side(p) / sq(v);
    }

    // Compare projections of p and q onto this line
    bool cmpProj(const pt &p, const pt &q) const {
        return dot(v, p) < dot(v, q);
    }
};

// Intersection point between two lines l1 and l2
bool inter(const line &l1, const line &l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (fabsl(d) < 1e-18) return false;  // parallel or coincident
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

// Angle between two lines (in radians, in [0, pi])
T angleBetween(const line &l1, const line &l2) {
    // Use direction vectors
    T cr = cross(l1.v, l2.v);
    T dt = dot(l1.v, l2.v);
    return atan2(fabsl(cr), dt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long double a1, b1, c1, a2, b2, c2;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;

    line l1(a1, b1, c1);
    line l2(a2, b2, c2);

    pt out;
    bool ok = inter(l1, l2, out);
    if (!ok) {
        // Lines are parallel or coincident; no single intersection
        cout << "No unique intersection";
        return 0;
    }

    // Compute angle in radians
    T ang = angleBetween(l1, l2);

    cout << fixed << setprecision(15)
         << out.x << " " << out.y << " " << ang << '\n';

    return 0;
}
