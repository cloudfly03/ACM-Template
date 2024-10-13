#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int V = 2001;

int n, m;
int f[V];
vector<pii> t;

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        int v, w, s;
        cin >> v >> w >> s;
        int j = 0;
        while (s >= (1 << j)) {
            t.emplace_back(v * (1 << j), w * (1 << j));
            s -= 1 << j;
            ++j;
        }
        if (s) t.emplace_back(v * s, w * s);
    }

    for (auto [v, w] : t) {
        for (int j = m;j >= v;--j) {
            f[j] = max(f[j], f[j - v] + w);
        }
    }

    cout << f[m] << endl;
}

signed main() {
    //cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}