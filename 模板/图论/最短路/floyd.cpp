#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF ((1<<31) - 1)
// #define lc (p<<1)
// #define rc (p<<1|1)

const int N = 101;
int dp[N][N];
int n, m;

void solve() {
    cin >> n >> m;

    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= n;++j) {
            if (i == j)continue;
            dp[i][j] = INF;
        }

    for (int i = 1;i <= m;++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dp[v][u] = dp[u][v] = min(dp[u][v], w);
    }

    for (int k = 1;k <= n;++k)
        for (int i = 1;i <= n;++i)
            for (int j = 1;j <= n;++j)
                dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);

    for (int i = 1;i <= n;++i) {
        for (int j = 1;j <= n;++j) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
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