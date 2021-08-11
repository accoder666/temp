#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 500010, sigma_size = 26;
struct node {
    int len, link;
    int nxt[sigma_size];
};
node t[maxn << 1];
int cnt, last;
int tmp[maxn << 1], id[maxn << 1];
int d[maxn << 1], sum[maxn << 1];
void print(int, int);

int main() {
    t[0].len = 0, t[0].link = -1;
    char ch = getchar();
    while (!islower(ch)) ch = getchar();
    int cur, u, v, c;
    while (islower(ch)) {
        t[cur = ++cnt].len = t[last].len + 1;
        d[cur] = 1;
        u = last;
        while (u != -1 && !t[u].nxt[ch - 'a']) t[u].nxt[ch - 'a'] = cur, u = t[u].link;
        if (u == -1)
            t[cur].link = 0;
        else {
            v = t[u].nxt[ch - 'a'];
            if (t[u].len + 1 == t[v].len)
                t[cur].link = v;
            else {
                c = ++cnt;
                t[c].len = t[u].len + 1;
                t[c].link = t[v].link;
                memcpy(t[c].nxt, t[v].nxt, sizeof(t[c].nxt));
                while (u != -1 && t[u].nxt[ch - 'a'] == v) t[u].nxt[ch - 'a'] = c, u = t[u].link;
                t[v].link = t[cur].link = c;
            }
        }
        last = cur;
        ch = getchar();
    }
    int T, k;
    scanf("%d %d", &T, &k);
    for (int i = 0; i <= cnt; i++) tmp[t[i].len]++;
    for (int i = 0; i <= cnt; i++) tmp[i] += tmp[i - 1];
    for (int i = 0; i <= cnt; i++) id[tmp[t[i].len]--] = i;
    if (T) {
        for (int i = cnt + 1; i; i--) d[t[id[i]].link] += d[id[i]];
        for (int i = 0; i <= cnt; i++) sum[i] = d[i];
    } else
        for (int i = 0; i <= cnt; i++) d[i] = sum[i] = 1;
    d[0] = sum[0] = 0;
    for (int i = cnt; i; i--)
        for (int j : t[id[i]].nxt)
            if (j)
                sum[id[i]] += sum[j];
    if (sum[0] < k)
        printf("-1\n");
    else {
        print(0, k);
        putchar('\n');
    }
    return 0;
}

void print(const int u, int k) {
    if (k <= d[u])
        return;
    k -= d[u];
    for (int j = 0; j < sigma_size; j++)
        if (t[u].nxt[j]) {
            if (k > sum[t[u].nxt[j]])
                k -= sum[t[u].nxt[j]];
            else {
                putchar(j + 'a'), print(t[u].nxt[j], k);
                break;
            }
        }
    return;
}
