#include <cstdio>
#include <set>
using namespace std;

const int maxn = 200010;
set<int> S;
int b[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    bool ans;
    set<int>::iterator cur;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", b + i);
        ans = true;
        S.clear();
        S.insert(b[1]);
        for (int i = 2; i <= n; i++) {
            if (S.count(b[i]))
                cur = S.find(b[i]);
            else
                cur = S.insert(b[i]).first;
            if ((cur == S.begin() || *prev(cur) != b[i - 1]) && *cur != b[i - 1] &&
                (next(cur) == S.end() || *next(cur) != b[i - 1])) {
                ans = false;
                break;
            }
        }
        printf(ans ? "YES\n" : "NO\n");
    }
    return 0;
}
