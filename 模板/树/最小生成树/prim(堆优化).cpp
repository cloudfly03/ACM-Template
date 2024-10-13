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
bool vis[N];
int ans;

class cmp {
public:
    bool operator()(const pii& x, const pii& y) {
        return x.second > y.second;
    }
};

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }

    int cnt = 0;
    priority_queue<pii, vector<pii>, cmp> q;
    q.push({ 1,0 });

    while (q.size()) {
        auto [u, cost] = q.top();q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        ans += cost;
        ++cnt;
        for (auto [v, w] : e[u])
            if (!vis[v]) q.push({ v,w });
    }

    cout << ((cnt == n) ? to_string(ans) : "orz") << endl;
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