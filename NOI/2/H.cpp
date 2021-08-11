#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const long long mod = 1000000007;
const int maxn = 1000010;
int z[maxn], val[maxn];
char S[maxn];

int main() {
    int n;
    scanf("%d", &n);
    int l, r, len;
    long long ans;
    while (n--) {
        scanf("%s", S);
        l = r = -1, len = strlen(S);
        memset(z, 0, sizeof(z));
        for (int i = 1; i < len; i++) {
            z[i] = (i <= r ? min(z[i - l], r - i) : 0);
            while (i + z[i] < len && S[z[i]] == S[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
        ans = 1;
        memset(val, 0, sizeof(val));
        for (int i = 1; i < len; i++)
            if (z[i])
                val[i]++, val[min(min(i << 1, len), i + z[i])]--;
        for (int i = 1; i < len; i++) val[i] += val[i - 1], ans = (ans * (val[i] + 1)) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
