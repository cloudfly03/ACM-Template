/*
链接：https://ac.nowcoder.com/acm/contest/91279/H
*/

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
#define lowbit(x) (x&-x)

const int N = 1e6 + 1;

int n;
vector<pii> e[N];
int wei[N];
int d1[N], d2[N];
int son1[N], son2[N];
int tp[N];

int ans[N];

void dfs1(int u, int fa) {
    bool flag = false;
    for (auto [v, w] : e[u]) {
        if (v == fa) continue;
        flag = true;
        dfs1(v, u);
        if (d1[v] + w > d1[u]) {
            if (v != son1[u]) {
                d2[u] = d1[u];
                son2[u] = son1[u];
            }
            d1[u] = d1[v] + w;
            son1[u] = v;
        }
        else if (d1[v] + w > d2[u]) {
            d2[u] = d1[v] + w;
            son2[u] = v;
        }

        if (wei[v] + w > d1[u]) {
            if (v != son1[u]) {
                d2[u] = d1[u];
                son2[u] = son1[u];
            }
            d1[u] = wei[v] + w;
            son1[u] = v;
        }
        else if (wei[v] + w > d2[u] && d2[u] != 0) {
            d2[u] = wei[v] + w;
            son2[u] = v;
        }
    }
    if (!flag) {
        son1[u] = son2[u] = u;
    }
}

void dfs2(int u, int fa) {
    for (auto [v, w] : e[u]) {
        if (v == fa) continue;
        if (son1[u] == v) {
            tp[v] = max({ d2[u] + w, tp[u] + w ,w + wei[u] });
        }
        else {
            tp[v] = max({ d1[u] + w, tp[u] + w ,w + wei[u] });
        }
        dfs2(v, u);
    }
}

void dfs3(int u, int fa) {
    for (auto [v, w] : e[u]) {
        if (v == fa) continue;
        ans[v] = max(d1[v], tp[v]);
        dfs3(v, u);
    }
}

void solve() {
    cin >> n;
    for (int i = 1;i < n;++i) {
        int u, v, w;cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    for (int i = 1;i <= n;++i) {
        cin >> wei[i];
    }

    dfs1(1, 0);
    dfs2(1, 0);
    ans[1] = d1[1];
    dfs3(1, 0);

    for (int i = 1;i <= n;++i)
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