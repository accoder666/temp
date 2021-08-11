#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxp = 30;
struct edge {
    int to, nxt, val;
};
edge G[maxp << 1];
int head[maxp], cnt = 1;
bool flag[maxp];
inline int check(const int&, const int&);

int main() {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
    int n, m, d;
    scanf("%d %d %d", &n, &m, &d);
    if (m > 20) {
        printf("-1\n");
        return 0;
    }
    int u, v, w;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        G[++cnt] = { v, head[u], w }, head[u] = cnt;
        G[++cnt] = { u, head[v], w }, head[v] = cnt;
    }
    bool f;
    int ans = INT_MAX, tmpans;
    for (int i = 1; i < 1 << m; i++) {
        tmpans = 0;
        for (int j = 1; j <= m; j++) {
            flag[j] = i & (1 << (j - 1));
            if (flag[j])
                tmpans += G[j << 1].val;
        }
        if (tmpans > ans)
            continue;
        f = true;
        for (int j = 1; j <= d; j++)
            if (!check(j, n + 1 - j)) {
                f = false;
                break;
            }
        if (f)
            ans = tmpans;
    }
    if (ans == INT_MAX)
        printf("-1\n");
    else
        printf("%d\n", ans);
    return 0;
}

bool f[maxp];
queue<int> Q;
inline int check(const int& u, const int& v) {
    memset(f, false, sizeof(f));
    f[u] = true;
    while (!Q.empty()) Q.pop();
    Q.push(u);
    int t;
    while (!Q.empty()) {
        t = Q.front(), Q.pop();
        for (int i = head[t]; i; i = G[i].nxt)
            if (flag[i >> 1] && !f[G[i].to]) {
                if (G[i].to == v)
                    return true;
                f[G[i].to] = true;
                Q.push(G[i].to);
            }
    }
    return false;
}
