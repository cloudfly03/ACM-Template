#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF 1e14
#define MOD 998244353
#define lc p<<1
#define rc p<<1|1

const int N = 500 + 1;
int n, m, x;
vector<int> e[N];
int match[N];
bool vis[N];

bool dfs(int u) {
    for (auto v : e[u]) {
        if (vis[v]) continue;
        vis[v] = true;
        if (!match[v] || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m >> x;
    for (int i = 1;i <= x;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
    }

    int ans = 0;
    for (int i = 1;i <= n;++i) {
        fill(vis + 1, vis + n + 1, false);
        if (dfs(i)) ++ans;
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