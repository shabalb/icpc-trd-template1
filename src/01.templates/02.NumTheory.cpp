#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

// ========== НОД ==========
int64 gcd(int64 a, int64 b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

// ========== НОК ==========
int64 lcm(int64 a, int64 b) {
    return a / gcd(a, b) * b; // избегаем переполнения
}

// ========== Расширенный алгоритм Евклида ==========
// Возвращает {g, x, y}, где g = gcd(a,b), a*x + b*y = g
tuple<int64, int64, int64> ext_gcd(int64 a, int64 b) {
    if (b == 0) return { a, 1, 0 };
    auto [g, x1, y1] = ext_gcd(b, a % b);
    return { g, y1, x1 - (a / b) * y1 };
}

// ========== Обратный элемент по модулю ==========
// Способ 1: через расширенный Евклид (работает, если gcd(a, mod) == 1)
int64 mod_inv_euclid(int64 a, int64 mod) {
    auto [g, x, y] = ext_gcd(a, mod);
    if (g != 1) return -1; // не существует
    x %= mod;
    if (x < 0) x += mod;
    return x;
}


// Способ 2: через малую теорему Ферма (только если mod — простое!)
int64 mod_inv_fermat(int64 a, int64 mod) {
    // предполагается, что mod — простое и a % mod != 0
    return binpow(a, mod - 2, mod);
}

// ========== Быстрое возведение в степень ==========
int64 binpow(int64 a, int64 n, int64 mod = 0) {
    int64 res = 1;
    while (n > 0) {
        if (n & 1) {
            if (mod) res = (__int128)res * a % mod;
            else res *= a;
        }
        if (mod) a = (__int128)a * a % mod;
        else a *= a;
        n >>= 1;
    }
    return res;
}

// ========== Быстрое умножение по модулю (защита от переполнения) ==========
int64 mul_mod(int64 a, int64 b, int64 mod) {
    return (__int128)a * b % mod;
}

// ========== Проверка на простоту (детерминированная для 64-бит) ==========
bool is_prime(int64 n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    // Тест на основе базиса для 2^64
    int64 d = n - 1, s = 0;
    while (d % 2 == 0) { d /= 2; ++s; }
    // Набор баз: достаточен для n < 2^64
    vector<int64> bases;
    if (n < 4'759'123'141LL) bases = { 2, 7, 61 };
    else bases = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
    for (int64 a : bases) {
        if (a % n == 0) continue;
        int64 x = binpow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

// ========== Факторизация числа (простая, O(sqrt(n))) ==========
vector<int64> factorize(int64 n) {
    vector<int64> factors;
    for (int64 i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

// ========== Функция Эйлера φ(n) ==========
int64 phi(int64 n) {
    int64 result = n;
    for (int64 p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// ========== Китайская теорема об остатках (CRT) ==========
// Решает систему: x ≡ a[i] (mod m[i]), все m[i] — взаимно просты
// Возвращает {x, M}, где x — решение по модулю M = lcm(m[i])
// Если решения нет — возвращает {-1, -1}
pair<int64, int64> crt(const vector<int64>& a, const vector<int64>& m) {
    int n = a.size();
    int64 x = 0, M = 1;
    for (int i = 0; i < n; ++i) M = lcm(M, m[i]);
    for (int i = 0; i < n; ++i) {
        int64 Mi = M / m[i];
        int64 inv = mod_inv_euclid(Mi, m[i]);
        if (inv == -1) return { -1, -1 };
        x = (x + (__int128)a[i] * Mi % M * inv) % M;
    }
    if (x < 0) x += M;
    return { x, M };
}

// ========== Решето Эратосфена ( возврат простых) ==========
vector<int> sieve_primes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
    vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i]) primes.push_back(i);
    return primes;
}

// ========== Пример использования ==========
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // НОД / НОК
    cout << "gcd(48,18) = " << gcd(48, 18) << "\n";
    cout << "lcm(12,18) = " << lcm(12, 18) << "\n";

    // Обратный элемент
    cout << "inv(3) mod 11 = " << mod_inv_euclid(3, 11) << "\n"; // 4

    // Возведение и умножение по модулю
    cout << "2^10 mod 1000 = " << binpow(2, 10, 1000) << "\n";
    cout << "1e18 % 97 = " << mul_mod(1000000000000000000LL, 1, 97) << "\n";

    // Простота
    cout << "Is 97 prime? " << is_prime(97) << "\n";
    cout << "Is 100 prime? " << is_prime(100) << "\n";

    // Факторизация и φ
    auto fac = factorize(60);
    cout << "Factors of 60: "; for (auto x : fac) cout << x << ' '; cout << "\n";
    cout << "phi(60) = " << phi(60) << "\n"; // 16

    // CRT: x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7) → x = 23
    vector<int64> a = { 2, 3, 2 }, m = { 3, 5, 7 };
    auto [x, M] = crt(a, m);
    cout << "CRT solution: x = " << x << " (mod " << M << ")\n";

    // Простые до 20
    auto primes = sieve_primes(20);
    cout << "Primes up to 20: "; for (int p : primes) cout << p << ' '; cout << "\n";

    return 0;
}
