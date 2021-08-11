#include <cstdio>
#include <ctime>
#include <random>
using namespace std;

const long double t0 = 1e5, d = 0.97, tk = 1e-3;
const int maxn = 10010;
struct node {
    int x, y, w;
};
node t[maxn];
inline long double cal(const long double&, const long double&);
inline long double Rand(void);
int n;

int main() {
    scanf("%d", &n);
    long double ax = 0, ay = 0;
    for (int i = 1; i <= n; i++) scanf("%d %d %d", &t[i].x, &t[i].y, &t[i].w), ax += t[i].x, ay += t[i].y;
    ax /= n, ay /= n;
    long double x = ax, y = ay, tx, ty, ans = cal(ax, ay), tmp;
    for (long double T = t0; T > tk; T *= d) {
        tx = x + T * (Rand() * 2 - 1), ty = y + T * (Rand() * 2 - 1);
        tmp = cal(tx, ty);
        if (exp((cal(x, y) - tmp) / T) > Rand())
            x = tx, y = ty;
        if (tmp < ans)
            ans = tmp, ax = x = tx, ay = y = ty;
    }
    for (int i = 0; i < 1000; i++) {
        tx = ax + tk * (Rand() * 2 - 1), ty = ay + tk * (Rand() * 2 - 1);
        tmp = cal(tx, ty);
        if (tmp < ans)
            ans = tmp, ax = tx, ay = ty;
    }
    printf("%.3Lf %.3Lf\n", ax, ay);
    return 0;
}

inline long double cal(const long double& x, const long double& y) {
    long double dx, dy, ret = 0;
    for (int i = 1; i <= n; i++) dx = x - t[i].x, dy = y - t[i].y, ret += sqrtl(dx * dx + dy * dy) * t[i].w;
    return ret;
}

const int maxv = 1000000000;
mt19937 r(time(nullptr));
uniform_int_distribution<int> R(0, maxv);
inline long double Rand(void) { return (long double)(R(r)) / maxv; }
