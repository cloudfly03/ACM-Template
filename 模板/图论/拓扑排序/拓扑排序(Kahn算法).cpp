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
vector<int> e[N];
int indeg[N];
int n;
vector<int> ans;

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        int t;
        while (true) {
            cin >> t;
            if (t == 0) break;
            e[i].emplace_back(t);
            indeg[t]++;
        }
    }
    queue<int> q;

    for (int i = 1;i <= n;++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (q.size()) {
        int u = q.front();q.pop();
        ans.push_back(u);
        n--;
        for (auto v : e[u]) {
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }


    if (!n) return;
    for (auto u : ans) {
        cout << u << endl;
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
