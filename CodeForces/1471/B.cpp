#include <cstdio>
#include <queue>
using namespace std;

queue<pair<long long, long long>> Q;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    long long x, ans;
    long long a, cnt;
    while (t--) {
        scanf("%d %lld", &n, &x);
        while (n--) scanf("%lld", &a), Q.push(make_pair(a, 1));
        ans = 0;
        while (!Q.empty()) {
            a = Q.front().first, cnt = Q.front().second;
            if (a % x)
                break;
            ans += a * cnt;
            Q.pop(), Q.push(make_pair(a / x, cnt * x));
        }
        while (!Q.empty()) ans += Q.front().first * Q.front().second, Q.pop();
        printf("%lld\n", ans);
    }
    return 0;
}
