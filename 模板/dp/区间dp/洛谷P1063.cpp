#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define mpair(x,y) make_pair(x,y)
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 201;
int n;
int a[N];
int dp[N][N];

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int len = 2;len <= n;++len) {
        for (int l = 1;l + len - 1 <= n * 2;++l) {
            int r = l + len - 1;
            for (int k = l;k < r;++k)
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r] + a[l] * a[k + 1] * a[r % (2 * n) + 1]);
        }
    }

    int ans = 0;
    for (int i = 1;i <= n;++i)
        ans = max(ans, dp[i][i + n - 1]);
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