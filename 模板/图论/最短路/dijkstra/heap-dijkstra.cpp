#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF ((1ll<<31) - 1)
#define lc (p<<1)
#define rc (p<<1|1)

const int N = 1e5 + 1;

int n, m, s;
vector<pii> e[N];
int dis[N];

class cmp {
public:
    bool operator()(const pii& x, const pii& y) const {
        return x.second > y.second;
    }
};

void dijkstra(int s) {
    priority_queue<pii, vector<pii>, cmp> q;
    q.push({ s,0 });

    while (q.size()) {
        auto [u, cost] = q.top();q.pop();
        if (dis[u] != INF) continue;
        dis[u] = cost;
        for (auto [v, w] : e[u]) {
            if (dis[v] == INF)
                q.push({ v,w + cost });
        }
    }
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i <= m;++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }

    fill(dis + 1, dis + n + 1, INF);
    dijkstra(s);

    for (int i = 1;i <= n;++i)
        cout << dis[i] << ' ';
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
