// fixme

#include <cstdio>
#include <unordered_map>
using namespace std;

const int maxn = 200010;
struct edge {
    int to, nxt;
};
edge G[maxn << 2];
int head[maxn << 1], cnt;
int deg[maxn << 1], vis[maxn << 1];
void dfs(const int&);
unordered_map<int, int> M;
bool flag[maxn << 1];

int main() {
    int T;
    scanf("%d", &T);
    int n, x, y;
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i <= M.size(); i++) deg[i] = vis[i] = head[i] = 0;
        cnt = 1;
        M.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &x, &y);
            y += maxn;
            if (!M.count(x))
                M[x] = M.size() + 1;
            if (!M.count(y))
                M[y] = M.size() + 1;
            x = M[x], y = M[y];
            flag[x] = true, flag[y] = false;
            G[++cnt] = { y, head[x] }, head[x] = cnt;
            G[++cnt] = { x, head[y] }, head[y] = cnt;
            deg[x]++, deg[y]++;
        }
        for (int i = 1; i < maxn << 1; i++)
            if (deg[i] & 1) {
                G[++cnt] = { 0, head[i] }, head[i] = cnt;
                G[++cnt] = { i, head[0] }, head[0] = cnt;
            }
        for (int i = 1; i < maxn; i++)
            if (!vis[i])
                dfs(i);
        for (int i = 1; i <= n; i++) putchar(vis[i] == 1 ? 'b' : 'r');
        putchar(10);
    }
    return 0;
}

void dfs(const int& u) {
    for (int& i = head[u]; i; i = G[i].nxt)
        if (!vis[i >> 1])
            vis[i >> 1] = flag[u] + 1, dfs(G[i].to);
    return;
}
