#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9+9)
#define eps (ld)(1e-12)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1

const int N = 1001;
int a[N], b[N];
int n, k;

bool judge(int x) {
    int c[N], dp[N];
    for (int i = 1;i <= n;++i) c[i] = b[i] * 1000 - x * a[i];
    fill(dp + 1, dp + k + 1, -INF);

    for (int i = 1;i <= n;++i) {
        for (int j = k;j >= 0;--j) {
            if (dp[j] == -INF) continue;
            int f = min(k, j + a[i]);
            dp[f] = max(dp[f], dp[j] + c[i]);
        }
    }

    if (dp[k] >= 0) return true;
    else return false;
}

void solve() {
    cin >> n >> k;
    for (int i = 1;i <= n;++i)
        cin >> a[i] >> b[i];

    int l = 0, r = 1e8;
    int ans = -1;
    while (l <= r) {
        int m = l + r >> 1;
        if (judge(m)) {
            ans = m;
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    cout << ans << endl;
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