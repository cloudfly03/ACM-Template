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

//预处理 o(n)
//查询 o(1)

const int N = 2001;
int q;
int f[N], g[N];
int inv[N];

void init() {
    inv[1] = 1;
    for (int i = 2;i < N;++i)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    f[0] = g[0] = 1;
    for (int i = 1;i < N;++i) {
        f[i] = f[i - 1] * i % MOD;
        g[i] = g[i - 1] * inv[i] % MOD;
    }
}

int C(int n, int m) {
    return f[n] * g[m] % MOD * g[n - m] % MOD;
}

void solve() {
    init();
    cin >> q;
    for (int i = 1;i <= q;++i) {
        int n, m;cin >> n >> m;
        cout << C(n, m) << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}