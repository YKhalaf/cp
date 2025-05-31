#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

const long double EPS = 1e-9;

int sgn(T val) {
    if (val > EPS) return 1;
    if (val < -EPS) return -1;
    return 0;
}

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

pt translate(pt v, pt p) {
    return p + v;
}

pt scale(pt c, T factor, pt p) {
    return c + (p - c) * factor;
}

pt rot(pt p, T a) {
    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

pt perp(pt p) {
    return {-p.y, p.x};
}

pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
    return fp + (r - p) * (fq - fp) / (q - p);
}

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

bool isPerp(pt v, pt w) {
    return dot(v, w) == 0;
}

double angle(pt v, pt w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a,b,c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {
    return (orient(a, b, c) >= 0 ? angle(b - a, c - a) : 2 * M_PI - angle(b - a, c - a));
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

struct line {
    pt v;
    T c;

    // From direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {
    }

    // From equation ax + by = c
    line(T a, T b, T c) : v({b, -a}), c(c) {
    }

    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {
    }

    T side(pt p) {
        return cross(v, p) - c;
    }

    T dist(pt p) {
        return abs(side(p)) / abs(v);
    }

    T sqDist(pt p) {
        return side(p) * side(p) / (double) sq(v);
    }

    line perpThrough(pt p) {
        return {p, p + perp(v)};
    }

    //  Sorting along a line
    bool cmpProj(pt p, pt q) {
        return dot(v, p) < dot(v, q);
    }

    //  translate a line l by vector t
    line translate(pt t) {
        return {v, c + cross(v, t)};
    }

    // s shifting line l to the left by a certain distance
    line shiftLeft(T dist) {
        return {v, c + dist * abs(v)};
    }

    pt proj(pt p) {
        return p - perp(v) * side(p) / sq(v);
    }

    pt refl(pt p) {
        return p - perp(v) * (T) 2.0 * side(p) / sq(v);
    }
};

//  intersection point between two lines l1 and l2
bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

//  An angle bisector of two (non-parallel) lines l1 and l2 is a line that forms equal angles with l1 and l2.
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0);
    T sign = interior ? 1 : -1;
    return {
        l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
        l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign
    };
}

//  checks if a point P lies on the disk of diameter [AB].
bool inDisk(pt a, pt b, pt p) {
    return dot(a - p, b - p) <= 0;
}

// check if a point P lies on segment [AB].
bool onSegment(pt a, pt b, pt p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

//  intersection between two segments
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    // Proper intersection exists if opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

// To create sets of points we need a comparison function
struct cmpX {
    bool operator()(pt a, pt b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};

set<pt, cmpX> inters(pt a, pt b, pt c, pt d) {
    pt out;
    if (properInter(a, b, c, d, out)) return {out};
    set<pt, cmpX> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return s;
}

double areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

double areaPolygon(vector<pt> p) {
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n-1
    }
    return abs(area) / 2.0;
}

// true if P at least as high as A (blue part)
bool above(pt a, pt p) {
    return p.y >= a.y;
}

// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1;
}

// amplitude travelled around point A, from P to Q
double angleTravelled(pt a, pt p, pt q) {
    T ampli = angle(p - a, q - a);
    if (orient(a, p, q) > 0) return ampli;
    else return -ampli;
}

int windingNumber(vector<pt> p, pt a) {
    T ampli = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        ampli += angleTravelled(a, p[i], p[(i + 1) % n]);
    }
    return round(ampli / (2 * M_PI));
}

struct anglle {
    pt d;
    int t = 0; // direction and number of full turns

    // Turn 180 degrees counter-clockwise
    anglle t180() {
        return {d * (-1), t + half(d)};
    }

    // Turn 360 degrees counter-clockwise (full turn)
    anglle t360() {
        return {d, t + 1};
    }
};

bool operator<(anglle a, anglle b) {
    return make_tuple(a.t, half(a.d), 0) < make_tuple(b.t, half(b.d), cross(a.d, b.d));
}

anglle moveTo(anglle a, pt newD) {
    // check that segment [DD’] doesn’t go through the origin
    assert(!onSegment(a.d, newD, {0,0}));
    anglle b{newD, a.t};
    if (a.t180() < b) // if b more than half a turn bigger
        b.t--; //decrease b by a full turn
    if (b.t180() < a) // if b more than half a turn smaller
        b.t++; //  increase b by a full turn
    return b;
}

int windingNumber2(vector<pt> p, pt a) {
    anglle a{p.back()}; // start at last vertex
    for (pt d: p) {
        a = moveTo(a, d); // move to first vertex, second, etc.
    }
    return a.t;
}

// The center of the circle passing through three points
pt circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a; // consider coordinates relative to A
    assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2.0;
}

// Points of intersection of a line with a circle in the plane and return type of intersection
int circleLine(pt o, double r, line l, pair<pt, pt> &out) {
    T h2 = r * r - l.sqDist(o);
    if (h2 >= 0) {
        // the line touches the circle
        pt p = l.proj(o); // point P
        pt h = l.v * sqrt(h2) / abs(l.v); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}


int main() {
    return 0;
}
