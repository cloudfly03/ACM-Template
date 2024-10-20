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


const int N = 301;
int dp[N][N], ps[N];
int n;

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        int t;cin >> t;
        ps[i] = ps[i - 1] + t;
    }

    for (int len = 2;len <= n;++len) {
        for (int l = 1;l + len - 1 <= n;++l) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int k = l;k < r;++k)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + ps[r] - ps[l - 1]);
        }
    }

    cout << dp[1][n] << endl;
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