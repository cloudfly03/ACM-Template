#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 5e5 + 1;

int n, m, s;
vector<int> e[N];
int fa[N][20];//log2(N) 上取整 + 1
int dep[N];

void dfs(int u, int father) {
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    for (auto v : e[u]) {
        if (v == father) continue;
        dfs(v, u);
    }
}

void dp() {
    for (int i = 1;i <= 19;++i)
        for (int u = 1;u <= n;++u)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19;i >= 0;--i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = 19;i >= 0;--i)
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i < n;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    dfs(s, 0);
    dp();

    for (int i = 1;i <= m;++i) {
        int u, v;cin >> u >> v;
        cout << lca(u, v) << endl;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}