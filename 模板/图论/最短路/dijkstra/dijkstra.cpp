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

const int N = 1e4 + 1;

int n, m, s;
vector<pii> e[N];
int dis[N];
bool vis[N];

void dijkstra(int s) {
    dis[s] = 0;
    vis[s] = 1;
    for (int i = 1;i < n;++i) {
        for (auto [v, w] : e[s]) {
            dis[v] = min(dis[v], dis[s] + w);
        }
        int mn = INF;
        for (int i = 1;i <= n;++i) {
            if (!vis[i] && dis[i] < mn) {
                s = i;
                mn = dis[i];
            }
        }

        if (mn == INF) break;

        vis[s] = true;
    }
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i <= m;++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }

    fill(dis, dis + n + 1, INF);
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
