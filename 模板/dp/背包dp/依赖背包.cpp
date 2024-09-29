#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 101;
vector<int> e[N];
int x[N], w[N];
int f[N][N];
int n, m, root;

void dfs(int u) {
    for (int i = x[u];i <= m;++i) f[u][i] = w[u];
    for (auto v : e[u]) {
        dfs(v);
        for (int i = m;i;--i)
            for (int j = i - 1;j >= x[u];--j)
                f[u][i] = max(f[u][i], f[v][i - j] + f[u][j]);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        int p;
        cin >> x[i] >> w[i] >> p;
        if (p == -1) root = i;
        else e[p].push_back(i);
    }

    dfs(root);

    cout << f[root][m] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}