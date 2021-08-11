#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

map<int, int> M;

int main() {
    int t;
    scanf("%d", &t);
    int n, q;
    long long w;
    int ans1, ans2, ansv;
    int a, v, tmp, c;
    while (t--) {
        scanf("%d", &n);
        ansv = 0;
        M.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            v = 1, tmp = a;
            for (int j = 2; j * j <= tmp; j++)
                if (!(a % j)) {
                    c = 0;
                    while (!(a % j)) c++, a /= j;
                    if (c & 1)
                        v *= j;
                }
            if (a > 1)
                v *= a;
            if (v == 1) {
                ansv++;
                continue;
            }
            M[v]++;
        }
        ans1 = ansv;
        for (auto& it : M) {
            ans1 = max(ans1, it.second);
            if (!(it.second & 1) || it.first == 1)
                ansv += it.second;
        }
        ans2 = max(ans1, ansv);
        scanf("%d", &q);
        while (q--) {
            scanf("%lld", &w);
            printf("%d\n", w ? ans2 : ans1);
        }
    }
    return 0;
}
