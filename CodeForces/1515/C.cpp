#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 100010;
priority_queue<pair<int, int>> Q;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
int h[maxn], ans[maxn], sum[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, m, x;
    int u, mi, ma;
    while (t--) {
        scanf("%d %d %d", &n, &m, &x);
        while (!Q.empty()) Q.pop();
        while (!q.empty()) q.pop();
        for (int i = 1; i <= n; i++) scanf("%d", h + i), Q.push(make_pair(h[i], i));
        for (int i = 1; i <= m; i++) q.push(make_pair(0, i)), sum[i] = 0;
        while (!Q.empty()) {
            u = q.top().second;
            ans[Q.top().second] = q.top().second;
            sum[q.top().second] += Q.top().first;
            Q.pop(), q.pop();
            q.push(make_pair(sum[u], u));
        }
        mi = ma = sum[1];
        for (int i = 2; i <= m; i++) {
            if (mi > sum[i])
                mi = sum[i];
            if (ma < sum[i])
                ma = sum[i];
        }
        if (ma - mi > x)
            printf("NO\n");
        else {
            printf("YES\n");
            for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
            printf("\n");
        }
    }
    return 0;
}
