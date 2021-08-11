#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 2010;
inline int solve(bool);
int p[maxn], x[maxn];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n << 1; i++) scanf("%d", p + i);
    memcpy(x, p, sizeof(x));
    int v1 = solve(true);
    memcpy(x, p, sizeof(x));
    int v2 = solve(false);
    if (v1 == -1 && v2 == -1)
        printf("-1\n");
    else if (v1 == -1)
        printf("%d\n", v2);
    else if (v2 == -1)
        printf("%d\n", v1);
    else
        printf("%d\n", v1 < v2 ? v1 : v2);
    return 0;
}

inline bool check(void) {
    for (int i = 1; i <= n << 1; i++)
        if (x[i] != i)
            return false;
    return true;
}

inline int solve(bool opt) {
    int ret = 0;
    while (!check() && ret <= n << 1) {
        ret++;
        if (opt)
            for (int i = 1; i <= n; i++) x[i] ^= x[i + n] ^= x[i] ^= x[i + n];
        else
            for (int i = 1; i <= n << 1; i += 2) x[i] ^= x[i + 1] ^= x[i] ^= x[i + 1];
        opt ^= 1;
    }
    if (!check())
        return -1;
    return ret;
}
