#include <cstdio>
using namespace std;

const int maxn = 200010;
struct edge {
    int from, to;
};
edge G[maxn];
int deg[maxn], e[maxn], to[maxn];
bool ans[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d %d", &G[i].from, &G[i].to), deg[G[i].from]++, deg[G[i].to]++, ans[i] = true;
    for (int i = m; i; i--)
        if (!(deg[G[i].from] & 1) && !(deg[G[i].to] & 1))
            ans[i] = false, deg[G[i].from]--, deg[G[i].to]--;
    for (int i = m; i; i--)
        if (ans[i]) {
            if ((deg[G[i].from] & 1) && !(deg[G[i].to] & 1)) {
                if (e[G[i].from])
                    ans[i] = ans[e[G[i].from]] = false, deg[G[i].to]--, deg[to[G[i].from]]--,
                    deg[G[i].from] -= 2, e[G[i].from] = to[G[i].from] = 0;
                else
                    e[G[i].from] = i, to[G[i].from] = G[i].to;
            } else if (!(deg[G[i].from] & 1) && (deg[G[i].to] & 1)) {
                if (e[G[i].to])
                    ans[i] = ans[e[G[i].to]] = false, deg[G[i].from]--, deg[to[G[i].to]]--, deg[G[i].to] -= 2,
                    e[G[i].to] = to[G[i].to] = 0;
                else
                    e[G[i].to] = i, to[G[i].to] = G[i].from;
            }
        }
    for (int i = 1; i <= m; i++) putchar(ans[i] + '0');
    putchar('\n');
    return 0;
}
