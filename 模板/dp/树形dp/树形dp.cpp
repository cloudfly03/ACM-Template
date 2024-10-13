#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1e14
#define lc (p<<1)
#define rc (p<<1|1)

const int N = 6e3 + 1;
int r[N];
int n;

vector<int> e[N];
int dp[N][2];


void dfs(int u) {
    dp[u][1] = r[u];
    for (auto v : e[u]) {
        dfs(v);
        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        cin >> r[i];
    }
    int root = n * (n + 1) / 2;
    for (int i = 1;i < n;++i) {
        int u, v;
        cin >> u >> v;
        e[v].emplace_back(u);
        root -= u;
    }

    dfs(root);

    cout << max(dp[root][0], dp[root][1]) << endl;
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
