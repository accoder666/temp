#include <cstdio>
using namespace std;

const int maxn = 100010;
bool check(const int&, const int&);
char S[maxn];

int main() {
    freopen("random.in", "r", stdin);
    freopen("random.out", "w", stdout);
    int n, q;
    scanf("%d %d", &n, &q);
    scanf("%s", S + 1);
    int stat = 3;
    for (int i = 1; i <= n; i++) stat &= ((S[i] == 'a') << 1) | (S[i] == 'b');
    int l1, r1, l2, r2;
    if (stat) {
        int l = (stat != 1) ? 2 : 3;
        int len1, len2, tmp;
        while (q--) {
            scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
            len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
            len1 %= l;
            tmp = (len2 - len1) / l;
            printf("%lld\n", ((long long)tmp + 1) * (len2 - len1 + 1) -
                                 ((long long)tmp * (tmp + 1) >> 1) * l - (len1 == 0) * (len2 + 1));
        }
        return 0;
    }
}
