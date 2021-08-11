#include <cstdio>
#include <set>
using namespace std;

const int maxn = 1000010;
set<pair<int, int>> S;
int a[maxn];

int main() {
    int T, t = 0;
    scanf("%d", &T);
    pair<int, int> tmp;
    set<pair<int, int>>::iterator it;
    int n, k, x, y, ans, val;
    while (++t <= T) {
        scanf("%d", &k);
        if (t == 1) {
            n = k;
            for (int i = 1; i <= n; i++) scanf("%d", a + i);
        } else
            while (k--) scanf("%d %d", &x, &y), a[x] = y;
        S.clear();
        for (int i = 1; i <= n; i++) S.insert(make_pair(a[i], i));
        for (int i = 1; i < n; i++) {
            it = --S.end();
            tmp = make_pair(it->first - S.begin()->first, it->second);
            if (tmp < *(++S.begin()))
                break;
            S.erase(S.begin()), S.erase(it), S.insert(tmp);
        }
        ans = S.size(), val = 0;
        while (S.size() > 2) {
            val ^= 1;
            it = --S.end();
            tmp = make_pair(it->first - S.begin()->first, it->second);
            if (tmp >= *(++S.begin()))
                break;
            S.erase(S.begin()), S.erase(it), S.insert(tmp);
        }
        if (S.size() == 2)
            val ^= 1;
        printf("%d\n", ans - val);
    }
    return 0;
}
