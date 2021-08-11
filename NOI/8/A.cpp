#include <cmath>
#include <cstdio>
using namespace std;

struct point {
    long double x, y;
};
inline point get(const long double&, const long double&, const long double&, const long double&,
                 const long double&);
inline long double dist(const long double&, const long double&, const long double&, const long double&);
inline long double f(const long double&, const long double&);
inline long double F(const long double&);
long double ax, ay, bx, by, cx, cy, dx, dy, p, q, r;
const long double eps = 1e-7;

int main() {
    scanf("%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf", &ax, &ay, &bx, &by, &cx, &cy, &dx, &dy, &p, &q, &r);
    long double l = 0, r = 1;
    while (l + eps < r) {
        long double midl = l + (r - l) / 3, midr = r - (r - l) / 3;
        if (F(midl) <= F(midr))
            r = midr;
        else
            l = midl;
    }
    printf("%.2Lf\n", F(l));
    return 0;
}

inline point get(const long double& x1, const long double& y1, const long double& x2, const long double& y2,
                 const long double& k) {
    return (point){ (x2 - x1) * k + x1, (y2 - y1) * k + y1 };
}

inline long double dist(const long double& x1, const long double& y1, const long double& x2,
                        const long double& y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline long double f(const long double& x, const long double& y) {
    point p1 = get(ax, ay, bx, by, x);
    point p2 = get(cx, cy, dx, dy, y);
    return dist(ax, ay, p1.x, p1.y) / p + dist(p1.x, p1.y, p2.x, p2.y) / r + dist(p2.x, p2.y, dx, dy) / q;
}

inline long double F(const long double& x) {
    long double l = 0, r = 1;
    while (l + eps < r) {
        long double midl = l + (r - l) / 3, midr = r - (r - l) / 3;
        if (f(x, midl) <= f(x, midr))
            r = midr;
        else
            l = midl;
    }
    return f(x, l);
}
