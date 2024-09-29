#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1e14
// #define lc (p<<1)
// #define rc (p<<1|1)

const int N = 5001;
vector<pii> e[N];
int n, m;
int dis[N];
bool vis[N];
int ans;

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }

    fill(dis + 1, dis + n + 1, INF);
    int u = 1;
    dis[u] = 0, vis[u] = true;
    for (int i = 1;i < n;++i) {
        for (auto [v, w] : e[u])
            dis[v] = min(dis[v], w);

        int mn = INF;
        for (int j = 1;j <= n;++j)
            if (!vis[j] && mn > dis[j]) {
                u = j;
                mn = dis[j];
            }

        if (mn == INF) {
            cout << "orz" << endl;
            return;
        }
        vis[u] = true;
        ans += mn;
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