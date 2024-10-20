#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9+9)
#define eps (ld)(1e-12)
#define P (int)(998244353)
#define G (int)(3)
// #define lc p<<1
// #define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

// 差分约束
// tarjan scc
// toposort

const int N = 1e6 + 1;

int n, k;
int dfn[N], low[N], tot;
int stk[N], top;
bool instk[N];
int scc[N], cnt;
int scccnt[N];
vector<pii> e[N], ne[N];
int indeg[N];
int res[N];
int ans;

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u, instk[u] = true;

    for (auto [v, w] : e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instk[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        int v;
        ++cnt;
        do {
            v = stk[top--];
            instk[v] = false;
            scc[v] = cnt;
            scccnt[cnt]++;
        } while (v != u);
    }
}

void solve() {
    cin >> n >> k;
    for (int i = 1;i <= k;++i) {
        int x;cin >> x;
        int u, v;cin >> u >> v;
        if (x == 1) {
            e[u].emplace_back(v, 0);
            e[v].emplace_back(u, 0);
        }
        else if (x == 2)
            e[u].emplace_back(v, 1);
        else if (x == 3)
            e[v].emplace_back(u, 0);
        else if (x == 4)
            e[v].emplace_back(u, 1);
        else
            e[u].emplace_back(v, 0);
    }

    for (int i = 1;i <= n;++i)
        if (!dfn[i]) tarjan(i);

    for (int u = 1;u <= n;++u) {
        for (auto [v, w] : e[u]) {
            if (scc[u] == scc[v] && w) { cout << -1 << endl; return; }
            if (scc[u] == scc[v]) continue;
            ne[scc[u]].emplace_back(scc[v], w);
            indeg[scc[v]]++;
        }
    }

    queue<int> q;
    for (int i = 1;i <= cnt;++i)
        if (!indeg[i]) { q.push(i);res[i] = 1; }

    while (q.size()) {
        int u = q.front();q.pop();
        ans += scccnt[u] * res[u];
        for (auto [v, w] : ne[u]) {
            res[v] = max(res[v], res[u] + w);
            indeg[v]--;
            if (!indeg[v]) q.push(v);
        }
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