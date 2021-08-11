#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int mod = 31011;
const int maxn = 1010;
struct edge {
    int from, to, val;
    inline bool operator<(const edge& rhs) const { return val < rhs.val; }
};
edge G[maxn], T[maxn];
int find(int);
int fa[maxn];
int val[maxn];
int id[maxn];
int A[maxn][maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d %d %d", &G[i].from, &G[i].to, &G[i].val);
    sort(G + 1, G + m + 1);
    int fu, fv;
    int cnt = 0, c = 0;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        fu = find(G[i].from), fv = find(G[i].to);
        if (fu != fv) {
            fa[fu] = fv;
            T[++cnt] = G[i];
            if (G[i].val != val[c])
                val[++c] = G[i].val;
            if (cnt == n - 1)
                break;
        }
    }
    if (cnt != n - 1) {
        printf("0\n");
        return 0;
    }
    int u, v, C;
    int ans = 1, tmp;
    for (int i = 1; i <= c; i++) {
        for (int j = 1; j <= n; j++) fa[j] = j;
        for (int j = 1; j <= cnt; j++)
            if (T[j].val != val[i])
                fa[find(T[j].from)] = find(T[j].to);
        C = 0;
        for (int j = 1; j <= n; j++)
            if (fa[j] == j)
                id[j] = ++C;
        memset(A, 0, sizeof(A));
        for (int j = 1; j <= m; j++)
            if (G[j].val == val[i]) {
                u = id[find(G[j].from)], v = id[find(G[j].to)];
                A[u][u]++, A[v][v]++, A[u][v]--, A[v][u]--;
            }
        for (int j = 1; j < C; j++) {
            for (int k = j + 1; k < C; k++)
                while (A[k][j]) {
                    tmp = A[j][j] / A[k][j];
                    for (int l = j; l < C; l++) A[j][l] = (A[j][l] - tmp * A[k][l]) % mod;
                    for (int l = j; l < C; l++) A[j][l] ^= A[k][l] ^= A[j][l] ^= A[k][l];
                    ans = -ans;
                }
            ans = ans * A[j][j] % mod;
        }
    }
    printf("%d\n", (ans + mod) % mod);
    return 0;
}

int find(const int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
