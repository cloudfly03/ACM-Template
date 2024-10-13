#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 1e5 + 1;
vector<int> e[N];
int vis[N];
int n, m;

bool dfs(int u, int c) {
    vis[u] = c;
    int flag = true;
    for (auto v : e[u]) {
        if (!vis[v]) flag &= dfs(v, 3 - c);
        else if (vis[v] != 3 - c) return false;
    }
    return flag;
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    bool ans = true;
    for (int i = 1;i <= n;++i)
        if (!vis[i]) ans &= dfs(i, 1);

    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}