#include <iostream>
using namespace std;
int binfind(int* mas, int n, int find) {
    int l = -1, r = n, m;
    while (l < r - 1) {
        m = (l + r) / 2;
        if (mas[m] < find) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return r;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int* mas = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> mas[i];
    }
    int k, t;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> t;
        int pos = binfind(mas, n, t);
        if (mas[pos] == t) {
            cout << pos + 1 << ' ';
        }
        else {
            cout << -1 << ' ';
        }
    }
}