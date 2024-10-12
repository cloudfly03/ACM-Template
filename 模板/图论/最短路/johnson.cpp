#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1000000000
// #define lc (p<<1)
// #define rc (p<<1|1)


const int N = 3e3 + 10;
vector<pii> e[N];
int n, m;
int h[N];

class cmp {
public:
    bool operator()(const pii& x, const pii& y)const {
        return x.second > y.second;
    }
};

bool spfa(int s) {
    queue<int> q;
    bool inque[N]{};
    int cnt[N];
    fill(h + 1, h + n + 1, INF);

    q.push(0);
    while (q.size()) {
        int u = q.front();
        q.pop();
        inque[u] = false;

        for (auto [v, w] : e[u]) {
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1) return true;
                if (!inque[v]) { q.push(v);inque[v] = true; }
            }
        }
    }
    return false;
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }

    for (int i = 1;i <= n;++i)
        e[0].emplace_back(i, 0);

    if (spfa(0)) {
        cout << -1 << endl;
        return;
    }

    for (int u = 1;u <= n;++u)
        for (auto& [v, w] : e[u])
            w += h[u] - h[v];

    // n * heap-dijkstra
    for (int i = 1;i <= n;++i) {
        int ans = 0;
        bool vis[N]{};
        priority_queue<pii, vector<pii>, cmp> q;
        q.push({ i,0 });
        int last = n * (n + 1) / 2;
        while (q.size()) {
            auto [u, dis] = q.top();
            q.pop();
            if (vis[u])continue;
            vis[u] = true;
            last -= u;
            ans += u * (dis + h[u] - h[i]);
            for (auto [v, w] : e[u]) {
                if (vis[v]) continue;
                q.push({ v,dis + w });
            }
        }

        cout << ans + last * INF << endl;
    }
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