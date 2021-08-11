#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 250010;
int num[maxn], tmp[maxn], val[maxn], ret[maxn];
int ans[maxn];

int main() {
    //    freopen("js.in", "r", stdin);
    //    freopen("js.out", "w", stdout);
    int l;
    unsigned int s;
    scanf("%d %u", &l, &s);
    static const unsigned int k = 747796405, b = -1403630843;
    num[0] = l;
    for (int i = 1; i <= l; i++) num[l - i + 1] = (int)((s >> 10) % 10), s = k * s + b;
    val[0] = val[1] = 1;
    while (val[0] < l) {
        val[++val[0]] = 1;
        memcpy(tmp, num, sizeof(tmp));
        memset(ret, 0, sizeof(ret));
        div(tmp, val, ret);
        add(ans, ret);
    }
    print(ans);
    printf("\n");
    return 0;
}

inline int compare(const int* a, const int* b) {
    if (a[0] > b[0])
        return 1;
    if (a[0] < b[0])
        return -1;
    for (int i = a[0]; i; i--) {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
    }
    return 0;
}

inline void add(int* a, const int* b) {
    if (b[0] > a[0])
        a[0] = b[0];
    for (int i = 1; i <= a[0]; i++) {
        a[i] += b[i];
        if (a[i] >= 10)
            a[i + 1]++, a[i] -= 10;
    }
    while (a[a[0] + 1]) a[0]++;
    return;
}

inline void sub(int* a, const int* b) {
    int flag = compare(a, b);
    if (!flag) {
        a[0] = 0;
        return;
    }
    if (flag == 1) {
        for (int i = 1; i <= a[0]; i++) {
            if (a[i] < b[i])
                a[i + 1]--, a[i] = a[i] + 10;
            a[i] = a[i] - b[i];
        }
        while (a[0] && !a[a[0]]) a[0]--;
        return;
    }
    return;
}

inline void div(int* a, const int* b, int* c) {
    static int tmp[maxn];
    c[0] = a[0] - b[0] + 1;
    for (int i = c[0]; i; i--) {
        memset(tmp, 0, sizeof(tmp));
        tmp[0] = b[0] + i - 1;
        for (int j = 1; j <= b[0]; j++) tmp[j + i - 1] = b[j];
        while (compare(a, tmp) >= 0) c[i]++, sub(a, tmp);
    }
    while (c[0] && !c[c[0]]) c[0]--;
    return;
}

inline void print(const int* a) {
    if (!a[0]) {
        printf("0");
        return;
    }
    for (int i = a[0]; i; i--) printf("%d", a[i]);
    return;
}
