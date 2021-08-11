#include <cstdio>
#include <unordered_map>
using namespace std;

const int maxn = 100010;
struct node {
    int len, link;
    unordered_map<int, int> nxt;
};
node t[maxn << 1];
int cnt, last;

int main() {
    int n;
    scanf("%d", &n);
    t[0].len = 0, t[0].link = -1;
    int x, cur, u, v, c;
    long long ans = 0;
    while (n--) {
        scanf("%d", &x);
        t[cur = ++cnt].len = t[last].len + 1;
        u = last;
        while (u != -1 && !t[u].nxt[x]) t[u].nxt[x] = cur, u = t[u].link;
        if (u == -1)
            t[cur].link = 0;
        else {
            v = t[u].nxt[x];
            if (t[u].len + 1 == t[v].len)
                t[cur].link = v;
            else {
                c = ++cnt;
                t[c] = t[v];
                t[c].len = t[u].len + 1;
                while (u != -1 && t[u].nxt[x] == v) t[u].nxt[x] = c, u = t[u].link;
                t[v].link = t[cur].link = c;
            }
        }
        last = cur;
        ans += t[cur].len - t[t[cur].link].len;
        printf("%lld\n", ans);
    }
    return 0;
}
