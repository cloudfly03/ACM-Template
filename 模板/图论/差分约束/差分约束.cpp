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

const int N = 5e3 + 1;

int n, m;
vector<pii> e[N];
int dis[N], cnt[N];

bool spfa(int s) {
    queue<int> q;
    bool inque[N];
    fill(dis + 1, dis + n + 1, INF);
    fill(inque + 1, inque + n + 1, false);
    inque[s] = true;
    q.push(s);

    while (q.size()) {
        int u = q.front();q.pop();
        inque[u] = false;
        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n) return true;
                if (!inque[v]) {
                    inque[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return false;
}


void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e[v].emplace_back(u, w);
    }
    for (int i = 1;i <= n;++i)
        e[0].emplace_back(i, 0);

    if (spfa(0))
        cout << "NO" << endl;
    else {
        for (int i = 1;i <= n;++i)
            cout << dis[i] << ' ';
        cout << endl;
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