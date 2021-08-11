#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
using namespace std;

const int maxn = 200010;
struct point {
    long double x, y;
    inline bool operator<(const point& rhs) const {
        if (y == rhs.y)
            return x < rhs.x;
        return y < rhs.y;
    }
};
point t[maxn];
inline long double dist(const point&, const point&);
struct cmp {
    inline bool operator()(const point& a, const point& b) const {
        if (a.x == b.x)
            return a.y < b.y;
        return a.x < b.x;
    }
};
multiset<point> S;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%Lf %Lf", &t[i].x, &t[i].y);
    sort(t + 1, t + n + 1, cmp());
    long double ans = 1e10;
    int l = 1;
    for (int i = 1; i <= n; i++) {
        while (l < i && t[l].x <= t[i].x - ans / 2.0) S.erase(S.find(t[l++]));
        for (auto it1 = S.lower_bound({ t[i].x, t[i].y - ans / 2.0 });
             it1 != S.end() && it1->y < ans / 2.0 + t[i].y; it1++)
            for (auto it2 = S.lower_bound({ t[i].x, t[i].y - ans / 2.0 });
                 it2 != S.end() && it2->y < ans / 2.0 + t[i].y; it2++)
                if (*it1 < *it2)
                    ans = min(ans, dist(*it1, t[i]) + dist(*it2, t[i]) + dist(*it1, *it2));
        S.insert(t[i]);
    }
    printf("%.6Lf\n", ans);
    return 0;
}

inline long double dist(const point& a, const point& b) {
    return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
