#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000010;
class LinearBasis {
public:
    inline void set(const LinearBasis& u) {
        memcpy(val, u.val, sizeof(val));
        memcpy(dep, u.dep, sizeof(dep));
        return;
    }
    inline void insert(unsigned long long v, int d) {
        for (int i = maxl - 1; i >= 0; i--)
            if (v >> i) {
                if (!val[i]) {
                    val[i] = v, dep[i] = d;
                    break;
                }
                if (dep[i] < d) {
                    v ^= val[i] ^= v ^= val[i];
                    d ^= dep[i] ^= d ^= dep[i];
                }
                v ^= val[i];
            }
        return;
    }
    inline unsigned long long query(const int& d) const {
        unsigned long long ret = 0;
        for (int i = maxl - 1; i >= 0; i--)
            if (dep[i] >= d && (ret ^ val[i]) > ret)
                ret ^= val[i];
        return ret;
    }

private:
    static const int maxl = 64;
    unsigned long long val[maxl];
    int dep[maxl];
};
LinearBasis b[maxn];
int dep[maxn];

int main() {
    freopen("squirrel.in", "r", stdin);
    freopen("squirrel.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    int f;
    unsigned long long a;
    for (int i = 1; i <= n; i++) {
        scanf("%d %llu", &f, &a);
        b[i].set(b[f]), b[i].insert(a, dep[i] = dep[f] + 1);
    }
    int opt, u, d;
    while (m--) {
        scanf("%d %d", &opt, &u);
        switch (opt) {
            case 0:
                scanf("%d", &d);
                printf("%llu\n", b[u].query(dep[u] - d));
                break;
            case 1:
                scanf("%llu", &a);
                b[++n].set(b[u]);
                b[n].insert(a, dep[n] = dep[u] + 1);
                break;
            default:
                break;
        }
    }
    return 0;
}
