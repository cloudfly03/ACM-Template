#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF (int)(1e14)
#define MOD (int)(1e9+7)
#define eps (ld)(1e-6)
#define lc p<<1
#define rc p<<1|1

const int N = 1e5 + 1;
int n, m, p;
int inv[N];
int f[N], g[N];

int C(int n, int m, int p) {
    if (m > n) return 0;
    return f[n] * g[m] % p * g[n - m] % p;
}

int lucas(int n, int m, int p) {
    if (m == 0) return 1;
    return lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}

void solve() {
    cin >> n >> m >> p;
    inv[1] = f[0] = g[0] = 1;
    for (int i = 2;i < p;++i)
        inv[i] = (p - p / i) * inv[p % i] % p;
    for (int i = 1;i < p;++i) {
        f[i] = f[i - 1] * i % p;
        g[i] = g[i - 1] * inv[i] % p;
    }

    cout << lucas(n + m, n, p) << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}