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

const int N = 1e5 + 1;
int n, m, s;
vector<pii> e[N];
int dis[N], cnt[N];
bool inque[N];

// true 存在负环
// SLF（Small Label First） 优化 
bool spfa(int s) {
    deque<int> q;
    fill(dis + 1, dis + n + 1, INF);
    q.push_back(s);
    inque[s] = true;
    dis[s] = 0;

    while (q.size()) {
        int u = q.front();q.pop_front();
        inque[u] = false;
        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return true;
                if (!inque[v]) {
                    inque[v] = true;
                    if (q.size() && dis[v] > dis[q.front()]) q.push_back(v);
                    else q.push_front(v);
                }
            }
        }
    }
    return false;
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1;i <= m;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
    }

    spfa(s);

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