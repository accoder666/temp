// fixme

#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 100010, maxlg = 14;
struct query {
    int l, r, id;
};
int a[maxn];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    if (k > maxlg) {
        while (m--) printf("0\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
}
