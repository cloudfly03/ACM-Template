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
#define lc p<<1
#define rc p<<1|1

const int N = 1001;

int n, m;
vector<pii> e[N], re[N];
int s, t, k;
int g[N]; // 估价函数

void dijkstra(int s) {
    fill(g + 1, g + n + 1, INF);
    priority_queue < pii, vector<pii>, greater<pii>> q;
    q.push(make_pair(0, s));

    while (q.size()) {
        auto [cost, u] = q.top();q.pop();
        if (g[s] != INF) continue;
        g[s] = cost;
        for (auto [v, w] : re[u])
            if (!g[v]) q.push(make_pair(cost + w, v));
    }
}

void Astar() {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push(make_pair(0 + g[s], s));

    while (q.size()) {
        auto [cost, u] = q.top();q.pop();
        if (u == t)k--;
        if (!k) { cout << cost << endl;return; }
        for (auto [v, w] : e[u])
            q.push(make_pair(cost + w + g[v] - g[u], v));
    }
    if (k) cout << -1 << endl;
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        re[v].emplace_back(u, w);
    }
    cin >> s >> t >> k;

    dijkstra(t);

    Astar();
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