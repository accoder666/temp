#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010;
int size;
bool flag;
struct query {
    int l, r, ord;
    long long p, ans;
    inline bool operator<(const query& rhs) const {
        if (flag)
            return ord < rhs.ord;
        if (l / size != rhs.l / size)
            return l < rhs.l;
        if ((l / size) & 1)
            return r < rhs.r;
        return r > rhs.r;
    }
};
query Q[maxn];
long long a[maxn];
int pre[maxn], nxt[maxn];
long long P[2][maxn];
inline long long power(const int&, const long long&);
inline void modify(const int&, const int&);
long long sum[maxn];
int cnt[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    size = ceil(sqrt(n));
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    for (int i = 1; i <= m; i++) scanf("%d %d %lld", &Q[i].l, &Q[i].r, &Q[i].p), Q[i].ord = i;
    sort(Q + 1, Q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        P[0][0] = P[1][0] = 1;
        for (int j = 1; j <= size; j++) P[0][j] = (P[0][j - 1] << 1ll) % Q[i].p;
        for (int j = 1; j <= size; j++) P[1][j] = (P[1][j - 1] * P[0][size]) % Q[i].p;
        while (l > Q[i].l) modify(--l, 1);
        while (l < Q[i].l) modify(l++, -1);
        while (r > Q[i].r) modify(r--, -1);
        while (r < Q[i].r) modify(++r, 1);
        for (int j = nxt[0]; j; j = nxt[j])
            Q[i].ans =
                (Q[i].ans + ((power(r - l + 1, Q[i].p) - power(r - l + 1 - j, Q[i].p)) * sum[j] % Q[i].p)) %
                Q[i].p;
    }
    flag = true;
    sort(Q + 1, Q + m + 1);
    for (int i = 1; i <= m; i++) printf("%lld\n", (Q[i].ans + Q[i].p) % Q[i].p);
    return 0;
}

inline long long power(const int& e, const long long& mod) { return P[0][e % size] * P[1][e / size] % mod; }

int last;
inline void modify(const int& p, const int& val) {
    sum[cnt[a[p]]] -= a[p];
    if (!sum[cnt[a[p]]]) {
        if (last != cnt[a[p]])
            nxt[pre[cnt[a[p]]]] = nxt[cnt[a[p]]], pre[nxt[cnt[a[p]]]] = pre[cnt[a[p]]];
        else
            last = pre[cnt[a[p]]];
        pre[cnt[a[p]]] = nxt[cnt[a[p]]] = 0;
    }
    cnt[a[p]] += val;
    if (!sum[cnt[a[p]]])
        nxt[last] = cnt[a[p]], pre[cnt[a[p]]] = last, last = cnt[a[p]];
    sum[cnt[a[p]]] += a[p];
    return;
}
