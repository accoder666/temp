#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

const long double pi = acosl((long double)-1);
const long double r = 2e7 / pi;

int main() {
    freopen("return.in", "r", stdin);
    freopen("return.out", "w", stdout);
    long double a, b, d;
    cin >> a >> b >> d;
    cout << setprecision(16);
    if (a == b) {
        long double r1 = r * cosl((a + d) / r), r2 = r * cosl(a / r);
        cout << d * (r2 / r1 - 1) << endl;
        return 0;
    }
    long double c = cosl(d / r), s = sinl(d / r);
    auto tmp = [](const long double& v) -> long double { return logl(cosl(v)); };
    auto f = [=](const long double& x, const long double& y) -> long double {
        return d * (c - 1) + d * r / (y - x) * s * (tmp((x + d) / r) - tmp((y + d) / r));
    };
    auto g = [=](const long double& x, const long double& y) -> long double {
        return d * (c - 1) + d * r / (y - x) * s * (tmp((y - d) / r) - tmp((x - d) / r));
    };
    auto h = [=](const long double& x, const long double& y) -> long double {
        return d * (c - 1) + d * r / (y - x) * s * (2 * tmp(d / r) - tmp((x - d) / r) - tmp((y + d) / r));
    };
    if (a >= 0)
        cout << absl(f(a, b)) << endl;
    else if (b <= 0)
        cout << absl(g(a, b)) << endl;
    else
        cout << absl(h(a, b)) << endl;
    return 0;
}
