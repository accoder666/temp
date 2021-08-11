#include <cstdio>
using namespace std;

const long long ans[27] = { 1,       1,        1,        1,         2,         3,        6,
                            11,      23,       47,       106,       235,       551,      1301,
                            3159,    7741,     19320,    48629,     123867,    317955,   823065,
                            5623756, 14828074, 39299897, 104636890, 279793450, 751065460 };

int main() {
    int t;
    scanf("%d", &t);
    int n;
    long long m;
    while (t--) {
        scanf("%d %lld", &n, &m);
        printf("%lld\n", ans[n] % m);
    }
    return 0;
}
