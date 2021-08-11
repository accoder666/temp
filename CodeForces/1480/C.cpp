#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 100010;
inline void query(const int&);
int a[maxn];
int n;

int main() {
    scanf("%d", &n);
    int l = 1, r = n, mid;
    while (true) {
        mid = (l + r) >> 1;
        query(mid - 1), query(mid), query(mid + 1);
        if ((mid == 1 || a[mid - 1] > a[mid]) && (mid == n || a[mid + 1] > a[mid])) {
            printf("! %d\n", mid);
            return 0;
        } else if (mid > 1 && a[mid - 1] < a[mid])
            r = mid - 1;
        else
            l = mid + 1;
    }
    return 0;
}

inline void query(const int& p) {
    if (a[p] || p < 1 || p > n)
        return;
    printf("? %d\n", p);
    fflush(stdout);
    scanf("%d", a + p);
    return;
}
