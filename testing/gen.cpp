#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
#define all(x) x.begin(),x.end()
const int INF = 1e14;
const int MOD = 1e9 + 7;

set<int> exist;

void solve() {
    cout << 1000 << endl;
    for (int i = 1;i <= 1000;++i) {
        for (int j = 1;j <= 1000;++j) {
            cout << i << ' ' << j << endl;
        }
    }
}

signed main() {
    //cin.tie(nullptr)->sync_with_stdio(false);

    // freopen("test.in", "r", stdin);
    freopen("test.in", "w", stdout);
    
    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}