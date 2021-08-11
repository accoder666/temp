#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 20010, maxc = 1024, maxl = 16;
inline int encode(const int&, const int&, const int&);
inline void decode(int, int&, int&, int&);
inline void insert(const int&, const int&);
int L[maxn], R[maxn], U[maxn], D[maxn];
int f[maxn], s[maxn];
int r[maxn], c[maxn];
int cnt;
bool dfs(const int&);
int ans[maxn], len;
char map[maxl + 10][maxl + 10];

int main() {
    int k;
    scanf("%d", &k);
    int val, x, y, z;
    while (k--) {
        for (int i = 0; i < maxl; i++) scanf("%s", map[i]);
        for (int i = 0; i <= maxc; i++) L[i] = i - 1, R[i] = i + 1, U[i] = D[i] = i;
        L[0] = maxc, R[maxc] = 0, cnt = maxc;
        memset(f, 0, sizeof(f));
        memset(s, 0, sizeof(s));
        for (int i = 0; i < maxl; i++)
            for (int j = 0; j < maxl; j++)
                for (int v = 0; v < maxl; v++)
                    if (map[i][j] == '-' || map[i][j] - 'A' == v) {
                        val = encode(i, j, v);
                        insert(val, encode(0, i, j));
                        insert(val, encode(1, i, v));
                        insert(val, encode(2, j, v));
                        insert(val, encode(3, (i / 4) * 4 + j / 4, v));
                    }
        assert(dfs(0));
        for (int i = 1; i <= len; i++) {
            decode(ans[i], x, y, z);
            map[x][y] = (char)('A' + z);
        }
        for (int i = 0; i < maxl; i++) printf("%s\n", map[i]);
        if (k)
            printf("\n");
    }
    return 0;
}

inline int encode(const int& x, const int& y, const int& z) { return (x << 8) + (y << 4) + z + 1; }

inline void decode(int val, int& x, int& y, int& z) {
    val--;
    z = val & 15, val >>= 4;
    y = val & 15, val >>= 4;
    x = val;
    return;
}

inline void insert(const int& x, const int& y) {
    cnt++;
    r[cnt] = x, c[cnt] = y, s[y]++;
    D[cnt] = D[y], U[D[y]] = cnt, U[cnt] = y, D[y] = cnt;
    if (!f[x])
        f[x] = L[cnt] = R[cnt] = cnt;
    else {
        R[cnt] = R[f[x]], L[R[f[x]]] = cnt;
        L[cnt] = f[x], R[f[x]] = cnt;
    }
}

inline void remove(const int& p) {
    L[R[p]] = L[p], R[L[p]] = R[p];
    for (int i = D[p]; i != p; i = D[i])
        for (int j = R[i]; j != i; j = R[j]) U[D[j]] = U[j], D[U[j]] = D[j], s[c[j]]--;
    return;
}

inline void restore(const int& p) {
    for (int i = U[p]; i != p; i = U[i])
        for (int j = L[i]; j != i; j = L[j]) U[D[j]] = D[U[j]] = j, s[c[j]]++;
    L[R[p]] = R[L[p]] = p;
    return;
}

bool dfs(const int& dep) {
    if (!R[0]) {
        len = dep - 1;
        return true;
    }
    int p = R[0];
    for (int i = p; i; i = R[i])
        if (s[i] < s[p])
            p = i;
    remove(p);
    for (int i = D[p]; i != p; i = D[i]) {
        ans[dep] = r[i];
        for (int j = R[i]; j != i; j = R[j]) remove(c[j]);
        if (dfs(dep + 1))
            return true;
        for (int j = L[i]; j != i; j = L[j]) restore(c[j]);
    }
    restore(p);
    return false;
}
