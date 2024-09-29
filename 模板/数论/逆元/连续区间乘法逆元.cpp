#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF (int)(1e14)
#define MOD (int)(1e9+7)
#define eps (ld)(1e-6)
#define lc p<<1
#define rc p<<1|1

const int N = 1e6 + 1;
int n;
int inv[N];

void solve() {
    cin >> n;
    inv[1] = 1;
    for (int i = 2;i <= n;++i)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;

    cout << "inv(x) (mod " << MOD << ")" << endl;
    for (int i = 1;i <= n;++i)
        cout << "inv(" << i << ") = " << inv[i] << endl;
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