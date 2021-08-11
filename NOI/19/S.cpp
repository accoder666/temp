#include <cstdio>
using namespace std;

const int maxn = 10010;
const long double eps = 1e-13;
long double s[maxn], k[maxn], v[maxn];
long double V[maxn];

int main() {
    int n;
    long double EU;
    scanf("%d %Lf", &n, &EU);
    for (int i = 1; i <= n; i++) scanf("%Lf %Lf %Lf", s + i, k + i, v + i);
    long double l = 0, r = 1e5, mid, val;
    long double L, R, Mid;
    while (l + eps < r) {
        mid = (l + r) / 2.0, val = 0;
        for (int i = 1; i <= n; i++) {
            L = 0, R = 1e5;
            if (L < v[i])
                L = v[i];
            while (L + eps < R) {
                Mid = (L + R) / 2.0;
                if (Mid * Mid * (Mid - v[i]) * (2 * k[i] * mid) <= 1)
                    L = Mid;
                else
                    R = Mid;
            }
            V[i] = Mid, val += k[i] * (V[i] - v[i]) * (V[i] - v[i]) * s[i];
        }
        if (val < EU)
            r = mid;
        else
            l = mid;
    }
    long double ans = 0;
    for (int i = 1; i <= n; i++) ans += s[i] / V[i];
    printf("%.8Lf\n", ans);
    return 0;
}
