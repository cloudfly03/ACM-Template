#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int M = 50001;
int n, m;
int f[M];

void solve() {
    cin >> n >> m;
    fill(f + 1, f + m + 1, INF);
    for (int i = 1;i <= n;++i) {
        int p, c;cin >> p >> c;
        for (int j = m;j >= 0;--j) {
            if (f[j] == INF) continue;
            if (j + p >= m)
                f[m] = min(f[m], f[j] + c);
            else
                f[j + p] = min(f[j + p], f[j] + c);
        }
    }

    cout << f[m] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}