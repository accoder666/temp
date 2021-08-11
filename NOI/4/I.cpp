#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 500010, sigma_size = 26;
int len[maxn << 1], fa[maxn << 1];
int nxt[maxn << 1][sigma_size];
int cnt = 1, last = 1;
char S[maxn];
int tmp[maxn << 1], id[maxn << 1];
int siz[maxn << 1];

int main() {
    scanf("%s", S);
    int n = strlen(S);
    int d, cur, u, v, c;
    len[1] = fa[1] = 0;
    for (int i = 0; i < n; i++) {
        d = S[i] - 'a';
        len[cur = ++cnt] = len[last] + 1;
        siz[cur] = 1;
        u = last;
        while (u && !nxt[u][d]) nxt[u][d] = cur, u = fa[u];
        if (!u)
            fa[cur] = 1;
        else {
            v = nxt[u][d];
            if (len[u] + 1 == len[v])
                fa[cur] = v;
            else {
                c = ++cnt;
                len[c] = len[u] + 1;
                fa[c] = fa[v];
                memcpy(nxt[c], nxt[v], sizeof(nxt[c]));
                while (u && nxt[u][d] == v) nxt[u][d] = c, u = fa[u];
                fa[v] = fa[cur] = c;
            }
        }
        last = cur;
    }
    for (int i = 1; i <= cnt; i++) tmp[len[i]]++;
    for (int i = 1; i <= cnt; i++) tmp[i] += tmp[i - 1];
    for (int i = 1; i <= cnt; i++) id[tmp[len[i]]--] = i;
    long long ans = 0;
    for (int i = cnt; i; i--) {
        u = id[i];
        siz[fa[u]] += siz[u];
        ans += (long long)(len[u] - len[fa[u]]) * siz[u] * (n - siz[u]);
    }
    printf("%lld\n", ans);
    return 0;
}
