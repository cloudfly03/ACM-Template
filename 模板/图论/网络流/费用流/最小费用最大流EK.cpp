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

const int N = 5e3 + 1;
const int M = 5e4 + 1;

int n, m, S, T;

typedef struct {
    int to, c, f, nxt;
}edge;
edge e[M << 1];
int h[N];
int cnt = 1;
void add(int u, int v, int c, int f) {
    e[++cnt].to = v;
    e[cnt].c = c;
    e[cnt].f = f;
    e[cnt].nxt = h[u];
    h[u] = cnt;
}


int pre[N];
int dis[N], mxflow[N];
bool inque[N];

bool SPFA() {
    fill(dis + 1, dis + n + 1, INF);
    fill(mxflow + 1, mxflow + n + 1, 0);
    fill(inque + 1, inque + n + 1, false);
    queue<int> q;
    q.push(S);
    inque[S] = true;
    dis[S] = 0;
    mxflow[S] = INF;
    while (q.size()) {
        auto u = q.front();q.pop();
        inque[u] = false;
        for (int ed = h[u];ed;ed = e[ed].nxt) {
            auto [v, c, fee, nxt] = e[ed];
            if (dis[v] > dis[u] + fee && c) {
                dis[v] = dis[u] + fee;
                mxflow[v] = min(mxflow[u], c);
                pre[v] = ed;
                if (!inque[v]) {
                    q.push(v);
                    inque[v] = true;
                }
            }
        }
    }

    return dis[T] != INF;
}

void EK() {
    int flow = 0;
    int fee = 0;
    while (SPFA()) {
        flow += mxflow[T];
        int u = T;
        while (u != S) {
            e[pre[u]].c -= mxflow[T];
            e[pre[u] ^ 1].c += mxflow[T];
            fee += mxflow[T] * e[pre[u]].f;
            u = e[pre[u] ^ 1].to;
        }
    }

    cout << flow << ' ' << fee << endl;
}

void solve() {
    cin >> n >> m >> S >> T;
    for (int i = 1;i <= m;++i) {
        int u, v, c, f;
        cin >> u >> v >> c >> f;
        add(u, v, c, f);
        add(v, u, 0, -f);
    }

    EK();
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