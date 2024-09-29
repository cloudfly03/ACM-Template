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

int fa[N], sz[N], dep[N], son[N];

void dfs1(int u, int father) {
    fa[u] = father;
    dep[u] = dep[father] + 1;
    sz[u] = 1;
    for (auto v : e[u]) {
        if (v == father) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

int top[N];

void dfs2(int u, int t) {
    top[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (auto v : e[u]) {
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i < n;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    dfs1(s, 0);
    dfs2(s, s);

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