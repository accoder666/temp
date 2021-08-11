#include <cstdio>
using namespace std;

const int maxn = 500010;
int a[maxn], cnt[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++;

    return 0;
}
