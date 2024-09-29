#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 1001;
const int V = 101;

int n, a, b;
int f[V][V];

void solve() {
    cin >> n >> a >> b;
    for (int i = 1;i <= n;++i) {
        int x, y, w;
        cin >> x >> y >> w;
        for (int j = a;j >= x;--j)
            for (int k = b;k >= y;--k)
                f[j][k] = max(f[j][k], f[j - x][k - y] + w);
    }
    cout << f[a][b] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}