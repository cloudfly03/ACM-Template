#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 1001;
const int M = 1001;

int f[M];
int n, m;
bitset<N> status[M];

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        int w, p;cin >> w >> p;
        for (int j = m;j >= w;--j) {
            if (f[j - w] + p > f[j]) {
                status[j] = status[j - w];
                status[j][i] = 1;
                f[j] = f[j - w] + p;
            }
            else if (f[j - w] + p == f[j]) {
                status[j - w][i] = 1;
                for (int i = 1;i <= n;++i) {
                    if (status[j - w][i] == status[j][i]) continue;
                    if (status[j - w][i] > status[j][i])
                        status[j] = status[j - w];
                    break;
                }
                status[j - w][i] = 0;
            }
        }
    }
    for (int i = 1;i <= n;++i)
        if (status[m][i]) cout << i << ' ';
    cout << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}