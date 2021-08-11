#include <cstdio>
#include <unordered_set>
using namespace std;

const int maxn = 2010;
int a[maxn], s[maxn];
unordered_set<int> S;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    bool flag;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), s[i] = s[i - 1] ^ a[i];
        flag = false;
        S.clear();
        for (int i = 1; i < n; i++) {
            S.insert(s[i]);
            if (s[i] == (s[n] ^ s[i]) || (!s[i] && S.count(s[n] ^ s[i]))) {
                flag = true;
                break;
            }
        }
        printf(flag ? "YES\n" : "NO\n");
    }
    return 0;
}
