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

//预处理 O(nlogn)
//查询 O(1)

const int N = 2001;
int f[N], g[N];
int q;

int qpow(int base, int p) {
    int ans = 1;
    while (p) {
        if (p & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        p >>= 1;
    }
    return ans;
}

int inv(int x) {
    return qpow(x, MOD - 2);
}

void init() {
    f[0] = g[0] = 1;
    for (int i = 1;i < N;++i) {
        f[i] = i * f[i - 1] % MOD;
        g[i] = inv(i) * g[i - 1] % MOD;
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