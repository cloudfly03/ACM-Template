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

const int N = 1e5 + 1;

int n, m, q;
int v[N], w[N], c[N];
vector<int> e[N];
int seg;

typedef struct {
    int l, r;
    int id;
    int t;
    int lca;
}Query;
typedef struct {
    int id, v;
}Update;

bool cmp(Query a, Query b) {
    if (a.l / seg != b.l / seg) return a.l < b.l;
    if (a.r / seg != b.r / seg) return a.r < b.r;
    return a.t < b.t;
}

Query ql[N];
Update ul[N];
int mq, mu;

int sz[N], fa[N], top[N], son[N], dep[N];
int in[N], out[N], id[N << 1], tot;
bool occ[N];
int cnt[N], res;
int ans[N];

void update(int idx) {
    occ[id[idx]] ^= 1;
    if (occ[id[idx]]) {
        cnt[c[id[idx]]]++;
        res += w[cnt[c[id[idx]]]] * v[c[id[idx]]];
    }
    else {
        res -= w[cnt[c[id[idx]]]] * v[c[id[idx]]];
        cnt[c[id[idx]]]--;
    }
}

void add(int x) {
    cnt[x]++;
    res += w[cnt[x]] * v[x];
}

void del(int x) {
    res -= w[cnt[x]] * v[x];
    cnt[x]--;
}

void dfs1(int u, int father) {
    fa[u] = father;
    dep[u] = dep[father] + 1;
    sz[u] = 1;
    for (int v : e[u]) {
        if (v == father) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    in[u] = ++tot;
    id[tot] = u;
    top[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (auto v : e[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    out[u] = ++tot;
    id[tot] = u;
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void solve() {
    cin >> n >> m >> q;
    seg = pow(n, 0.666666);
    for (int i = 1;i <= m;++i)
        cin >> v[i];
    for (int i = 1;i <= n;++i)
        cin >> w[i];
    for (int i = 1;i < n;++i) {
        int u, v;cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    for (int i = 1;i <= n;++i)
        cin >> c[i];

    for (int i = 1;i <= q;++i) {
        int tp, l, r;cin >> tp >> l >> r;
        if (tp) {
            if (in[l] > in[r]) swap(l, r);
            int LCA = lca(l, r);
            if (LCA == l) ql[++mq] = { in[l],in[r],mq,mu,0 };
            else ql[++mq] = { out[l],in[r],mq,mu,LCA };
        }
        else ul[++mu] = { l,r };
    }

    sort(ql + 1, ql + mq + 1, cmp);

    for (int i = 1, l = 1, r = 0, t = 0;i <= mq;++i) {
        while (l > ql[i].l) update(--l);
        while (r < ql[i].r) update(++r);
        while (l < ql[i].l) update(l++);
        while (r > ql[i].r) update(r--);
        while (t < ql[i].t) {
            int idx = ul[++t].id;
            if (occ[idx]) { del(c[idx]); add(ul[t].v); }
            swap(ul[t].v, c[idx]);
        }
        while (t > ql[i].t) {
            int idx = ul[t].id;
            if (occ[idx]) { del(c[idx]); add(ul[t].v); }
            swap(ul[t--].v, c[idx]);
        }
        ans[ql[i].id] = res + ((ql[i].lca) ? w[cnt[c[ql[i].lca]] + 1] * v[c[ql[i].lca]] : 0);
    }

    for (int i = 1;i <= mq;++i)
        cout << ans[i] << endl;
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