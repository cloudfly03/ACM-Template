#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF 1e14
#define lc (p<<1)
#define rc (p<<1|1)

const int N = 101;
int n;
vector<int> e[N];
vector<int> ans;
int c[N];


int dfs(int u) {
    c[u] = -1;

    for (auto v : e[u]) {
        if (c[v] == 1) continue;
        if (c[v] == -1 || dfs(v) == false) return false;
    }

    c[u] = 1;

    ans.push_back(u);
    return true;
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        int t;
        while (true) {
            cin >> t;
            if (t == 0) break;
            e[i].push_back(t);
        }
    }

    for (int i = 1;i <= n;++i)
        if (c[i] == 0 && !dfs(i)) return;

    reverse(all(ans));
    for (auto u : ans) {
        cout << u << ' ';
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
