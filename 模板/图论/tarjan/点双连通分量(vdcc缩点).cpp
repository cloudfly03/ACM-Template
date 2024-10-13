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
int n, m;
vector<int> e[N];

int dfn[N], low[N], tot;
int stk[N], top, root;
vector<int> vdcc[N];
int id[N], idx;
bool cut[N];
vector<int> ne[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    if (e[u].empty()) {
        vdcc[++idx].emplace_back(u);
        return;
    }
    stk[++top] = u;
    int child = 0;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                child++;
                if (root != u || child > 1)
                    cut[u] = true;
                int w;++idx;
                while (true) {
                    w = stk[top--];
                    vdcc[idx].emplace_back(w);
                    if (w == v) break;
                }
                vdcc[idx].emplace_back(u);
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v;cin >> u >> v;
        if (u == v) continue;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    for (int root = 1;root <= n;++root)
        if (!dfn[root]) tarjan(root);

    cout << idx << endl;
    for (int i = 1;i <= idx;++i) {
        cout << vdcc[i].size() << ' ';
        for (auto u : vdcc[i])
            cout << u << ' ';
        cout << endl;
    }

    // for (int i = 1;i <= n;++i)
    //     if (cut[i]) id[i] = ++idx;

    // for (int i = 1;i <= idx;++i)
    //     for (auto u : vdcc[i])
    //         if (cut[u]) {
    //             ne[i].emplace_back(id[u]);
    //             ne[id[u]].emplace_back(i);
    //         }
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

