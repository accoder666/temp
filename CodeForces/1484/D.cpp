#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 100010;
int gcd(const int&, const int&);
int a[maxn], pre[maxn], nxt[maxn];
bool f[maxn];
queue<pair<int, int>> Q;
int ans[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, cnt;
    pair<int, int> P;
    while (t--) {
        scanf("%d", &n);
        cnt = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i), pre[i] = (i == 1 ? n : i - 1), nxt[i] = (i == n ? 1 : i + 1), f[i] = true;
        for (int i = 1; i <= n; i++)
            if (gcd(a[i], a[nxt[i]]) == 1)
                Q.push(make_pair(i, nxt[i]));
        while (!Q.empty()) {
            P = Q.front(), Q.pop();
            if (!f[P.first] || !f[P.second])
                continue;
            ans[++cnt] = P.second;
            f[P.second] = false, nxt[pre[P.second]] = nxt[P.second], pre[nxt[P.second]] = pre[P.second];
            if (gcd(a[P.first], a[nxt[P.first]]) == 1)
                Q.push(make_pair(P.first, nxt[P.first]));
        }
        printf("%d", cnt);
        for (int i = 1; i <= cnt; i++) printf(" %d", ans[i]);
        printf("\n");
    }
    return 0;
}

int gcd(const int& x, const int& y) {
    if (!y)
        return x;
    return gcd(y, x % y);
}
