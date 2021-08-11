#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 100010;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int ans;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        sort(a + 1, a + n + 1);
        while (!Q.empty()) Q.pop();
        for (int i = 2; i <= n; i++) Q.push(make_pair(a[i] - a[i - 1], i));
        ans = 1;
        for (int i = n; i >= 1; i--) {
            while (!Q.empty() && Q.top().second > i) Q.pop();
            if (Q.empty())
                break;
            if (Q.top().first >= a[i]) {
                ans = i;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
