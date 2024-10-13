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

const int N = 2e6 + 1;

int n, m;
vector<int> e[N];
int dfn[N], low[N], tot;
int stk[N], instk[N], top;
int scc[N], cnt;

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u, instk[u] = true;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instk[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        ++cnt;
        int v;
        do {
            v = stk[top--];
            instk[v] = false;
            scc[v] = cnt;
        } while (v != u);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int x, a, y, b;
        cin >> x >> a >> y >> b;
        e[x + !a * n].emplace_back(y + b * n);
        e[y + !b * n].emplace_back(x + a * n);
    }

    for (int i = 1;i <= (n << 1);++i)
        if (!dfn[i]) tarjan(i);

    for (int i = 1;i <= n;++i)
        if (scc[i] == scc[i + n]) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    cout << "POSSIBLE" << endl;
    for (int i = 1;i <= n;++i) {
        if (scc[i] < scc[i + n]) cout << 0 << ' ';
        else cout << 1 << ' ';
    }
    cout << endl;
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