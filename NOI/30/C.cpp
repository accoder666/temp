#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 1010, maxl = 60;
struct stone {
    unsigned long long number;
    int magic;
    inline bool operator<(const stone& rhs) const { return magic > rhs.magic; }
};
stone t[maxn];
unsigned long long val[maxl];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%llu %d", &t[i].number, &t[i].magic);
    sort(t + 1, t + n + 1);
    int ans = 0;
    unsigned long long v;
    for (int i = 1; i <= n; i++) {
        v = t[i].number;
        for (int j = maxl - 1; j >= 0; j--)
            if (v >> j) {
                if (!val[j]) {
                    val[j] = v;
                    ans += t[i].magic;
                    break;
                }
                v ^= val[j];
            }
    }
    printf("%d\n", ans);
    return 0;
}
