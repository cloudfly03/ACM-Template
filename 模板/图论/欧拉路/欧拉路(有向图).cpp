#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
#define all(x) x.begin(),x.end()
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 1e5 + 1;
int n, m;
vector<int> e[N];
vector<int> ans;
int ideg[N], odeg[N];

void dfs(int u) {
    while (!e[u].empty()) {
        int v = e[u][e[u].size() - 1];
        e[u].pop_back();
        dfs(v);
    }
    ans.emplace_back(u);
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        odeg[u]++;
        ideg[v]++;
    }
    int s = INF;
    int a = 0, b = 0;
    for (int i = 1;i <= n;++i) {
        if (ideg[i] == odeg[i]) continue;
        if (ideg[i] + 1 == odeg[i]) {
            s = min(s, i);
            a++;
        }
        else if (ideg[i] == odeg[i] + 1)
            b++;
        else {
            cout << "No" << endl;
            return;
        }
    }

    if ((!a && !b))
        s = 1;
    else if (a != 1 || b != 1) {
        cout << "No" << endl;
        return;
    }

    for (int i = 1;i <= n;++i) {
        sort(all(e[i]));
        reverse(all(e[i]));
    }

    dfs(s);
    reverse(all(ans));
    for (auto u : ans)
        cout << u << ' ';
    cout << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}