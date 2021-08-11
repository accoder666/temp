#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

const int maxn = 500010;
map<pair<int, int>, int> M;
char s[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    int tmp;
    pair<int, int> p, r;
    while (t--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        p = make_pair(0, 0);
        M.clear();
        for (int i = 1; i <= n; i++) {
            (s[i] == 'D' ? p.first : p.second)++;
            r = p;
            if (!r.first)
                r.second = 1;
            else if (!r.second)
                r.first = 1;
            else {
                tmp = __gcd(r.first, r.second);
                r.first /= tmp, r.second /= tmp;
            }
            printf("%d ", ++M[r]);
        }
        printf("\n");
    }
    return 0;
}
