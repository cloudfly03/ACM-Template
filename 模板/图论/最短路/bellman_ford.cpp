#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF ((1<<31) - 1)
#define lc (p<<1)
#define rc (p<<1|1)

const int N = 1e5 + 1;
vector<pii> e[N];
int n, m, s;
int dis[N];

//是否有负环
bool bellman_ford(int s) {
    fill(dis + 1, dis + n + 1, INF);
    dis[s] = 0;
    bool flag;

    for (int i = 1;i <= n;++i) {
        flag = false;
        for (int u = 1;u <= n;++u) {
            if (dis[u] == INF) continue;
            for (auto [v, w] : e[u])
                if (dis[v] > dis[u] + w) {
                    flag = true;
                    dis[v] = dis[u] + w;
                }
        }
        if (!flag) return flag;
    }

    return flag;
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i <= m;++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }

    bellman_ford(s);

    for (int i = 1;i <= n;++i) {
        cout << dis[i] << ' ';
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
