#include <iostream>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int main()
{
    long long a, b, n;
    cin >> a >> b >> n;
    long long p, q;
    long long d = gcd(a, b, p, q);
    if (n % d != 0) {
        cout << -1 << endl;
        return 0;
    }
    unsigned long long minsum = LLONG_MAX, tmp;

    for (int i = -1000000; i < 1000000; ++i) {
        tmp = abs((n / d) * p + i * b / d) + abs((n / d) * q - i * a / d) * 3;
        if (tmp < minsum) {
            minsum = tmp;
        }
    }
    cout << minsum << endl;
}
