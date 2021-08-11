#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 5010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int dis[maxn][maxn];
queue<int> Q;
inline long double solve(int, int, int);
int val[maxn];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int a, b;
    while (m--) {
        scanf("%d %d", &a, &b);
        G[++cnt] = { b, head[a] }, head[a] = cnt;
        G[++cnt] = { a, head[b] }, head[b] = cnt;
    }
    memset(dis, 0x3f, sizeof(dis));
    int u;
    for (int i = 1; i <= n; i++) {
        dis[i][i] = 0, Q.push(i);
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int j = head[u]; j; j = G[j].nxt)
                if (dis[i][G[j].to] > dis[i][u] + 1)
                    dis[i][G[j].to] = dis[i][u] + 1, Q.push(G[j].to);
        }
    }
    int s1, t1, s2, t2;
    scanf("%d %d %d %d", &s1, &t1, &s2, &t2);
    memset(val, 0x3f, sizeof(val));
    val[0] = dis[s1][t1] + dis[s2][t2];
    int d1, d2;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            d1 = min(dis[s1][i] + dis[j][t1], dis[s1][j] + dis[i][t1]);
            d2 = min(dis[s2][i] + dis[j][t2], dis[s2][j] + dis[i][t2]);
            if (d1 >= dis[0][0] || d2 >= dis[0][0] || dis[i][j] == dis[0][0])
                break;
            if (val[dis[i][j]] > d1 + d2)
                val[dis[i][j]] = d1 + d2;
        }
    long double ans = LDBL_MAX, tmp;
    for (int i = 0; i <= n; i++)
        if (val[i] != val[n + 1]) {
            tmp = solve(val[i], i, k);
            if (tmp < ans)
                ans = tmp;
        }
    printf("%.12Lf\n", ans);
    return 0;
}

inline long double solve(const int x, const int y, int k) {
    if (!x && !y)
        return 0;
    int v;
    if (!x) {
        v = k / y;
        return (long double)2 / (v + 1) * (y - k % y) + (long double)2 / (v + 2) * (k % y);
    }
    if (!y) {
        v = k / x;
        return (long double)1 / (v + 1) * (x - k % x) + (long double)1 / (v + 2) * (k % x);
    }
    long double ret = LDBL_MAX, tmp;
    static const long double sqrt2 = sqrtl(2);
    int p = k / (sqrt2 + 1), Tmp;
    for (int i = max(0, p - 5); i <= min(k / x, p + 5); i++) {
        tmp = (long double)1 / (i + 1) * x;
        Tmp = k - i * x;
        v = Tmp / y;
        tmp += (long double)2 / (v + 1) * (y - Tmp % y) + (long double)2 / (v + 2) * (Tmp % y);
        if (tmp < ret)
            ret = tmp;
    }
    p = k * sqrt2 / (sqrt2 + 1);
    for (int i = max(0, p - 5); i <= min(k / y, p + 5); i++) {
        tmp = (long double)2 / (i + 1) * y;
        Tmp = k - i * y;
        v = Tmp / x;
        tmp += (long double)1 / (v + 1) * (x - Tmp % x) + (long double)1 / (v + 2) * (Tmp % x);
        if (tmp < ret)
            ret = tmp;
    }
    return ret;
}
