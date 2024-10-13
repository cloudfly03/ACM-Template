#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF 1e14
#define MOD 998244353
#define lc p<<1
#define rc p<<1|1

int qpow(int base, int p) {
    int ans = 1;
    while (p) {
        if (p & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        p >>= 1;
    }
    return ans;
}

int inv(int x) {
    return qpow(x, MOD - 2);
}

void solve() {
    int a;cin >> a;
    cout << inv(a) << endl;
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