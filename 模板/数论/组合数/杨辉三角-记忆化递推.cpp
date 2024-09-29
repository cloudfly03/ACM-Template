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

const int N = 2001;
int res[N][N];
int q;

int C(int n, int m) {
    if (m == 0 || m == n) return 1;
    if (m > (n >> 1)) m = n - m;
    if (res[n][m]) return res[n][m];
    return res[n][m] = (C(n - 1, m) + C(n - 1, m - 1)) % MOD;
}

void solve() {
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