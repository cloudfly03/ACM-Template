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

const int N = 5e5 + 1;
int n, m, s;

vector<int> e[N];
int f[N];
bool vis[N];
vector<pii> q[N];
int ans[N];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void tarjan(int u, int fa) {
    vis[u] = true;
    for (auto v : e[u]) {
        if (v == fa) continue;
        tarjan(v, u);
        f[v] = u;
    }

    for (auto [v, idx] : q[u])
        if (vis[v]) ans[idx] = find(v);
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i <= n;++i)
        f[i] = i;
    for (int i = 1;i < n;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    for (int i = 1;i <= m;++i) {
        int u, v;cin >> u >> v;
        q[u].emplace_back(v, i);
        q[v].emplace_back(u, i);
    }

    tarjan(s, 0);

    for (int i = 1;i <= m;++i)
        cout << ans[i] << endl;
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