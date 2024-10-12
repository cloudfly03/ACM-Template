#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(998244353)
#define eps (ld)(1e-12)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1

const int N = 21;
int n;
int d[N];

void solve() {
    cin >> n;
    d[1] = d[0] = 0;
    d[2] = 1;
    for (int i = 3;i <= n;++i)
        d[i] = (i - 1) * (d[i - 1] + d[i - 2]);
    cout << d[n];
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