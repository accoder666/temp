#include <cstdio>
#include <stack>
using namespace std;

const int maxn = 100010;
int v[maxn << 1], p[maxn], cnt;
// set<pair<int, int> > S;
// inline int query(const int &);
// inline void add(const int &);
// int C[maxn];
stack<int> S;
int n;

int main() {
    scanf("%d", &n);
    char str[5];
    for (int i = 1; i <= n << 1; i++) {
        scanf("%s", str);
        if (str[0] == '-')
            scanf("%d", v + i), p[++cnt] = i;
    }
    int d;
    for (int i = 1; i <= n; i++) {
        d = p[i] - (i << 1) - 1;
        if (v[i] + d > n) {
            printf("NO\n");
            return 0;
        }
        printf("%d %d\n", p[i], v[i] + d);
        while (!S.empty() && S.top() < v[i] + d) S.pop();
        S.push(v[i] + d);
    }
    while (!S.empty()) {
        printf("%d\n", S.top());
        S.pop();
    }
    return 0;
}
