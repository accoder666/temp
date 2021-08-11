#include <bits/stdc++.h>
using namespace std;

const int maxn = 610;
vector<pair<int, long long>> G[maxn];
long long ans[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a, b;
    long long c;
    while (m--) {
        scanf("%d %d %lld", &a, &b, &c);
        G[a].emplace_back(b, c);
    }
    for (int i = 1; i <= n; i++) {
        memset(ans, 0x3f, sizeof(ans));
        ans[i] = 0;
        for (int j = 1; j <= n; j++)
            if (j != i) {
                for () }
    }
}
