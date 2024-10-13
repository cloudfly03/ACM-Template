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

const int N = 201;
const int M = 5000 + 5;
typedef struct {
    int to;
    int c;
    int nxt;
}edge;
edge e[M << 1];
int h[N];
int cnt = 1;
void add(int u, int v, int c) {
    e[++cnt].to = v;
    e[cnt].c = c;
    e[cnt].nxt = h[u];
    h[u] = cnt;
}

int n, m, S, T;
int pre[N], mf[N];

bool bfs() {
    fill(mf + 1, mf + n + 1, 0);
    mf[S] = INF;
    queue<int> q;
    q.push(S);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int ed = h[u];ed;ed = e[ed].nxt) {
            auto [v, c, nxt] = e[ed];
            if (!mf[v] && c) {
                mf[v] = min(mf[u], c);
                pre[v] = ed;
                q.push(v);
            }
        }
    }
    return mf[T];
}

int EK() {
    int flow = 0;
    while (bfs()) {
        flow += mf[T];
        int s = T;
        do {
            e[pre[s] ^ 1].c += mf[T];
            e[pre[s]].c -= mf[T];
            s = e[pre[s]].to;
        } while (s != S);
    }
    return flow;
}

void solve() {
    cin >> n >> m >> S >> T;
    for (int i = 1;i <= m;++i) {
        int u, v, c;cin >> u >> v >> c;
        add(u, v, c);
        add(v, u, 0);
    }

    cout << EK() << endl;
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