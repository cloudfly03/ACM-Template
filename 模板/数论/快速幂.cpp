#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

int qpow(int base, int p, int mod) {
    int ans = 1;
    while (p > 0) {
        if (p & 1) ans = ans * base % mod;
        base = base * base % mod;
        p >>= 1;
    }
    return ans;
}

void solve() {
    int a, b, p;
    cin >> a >> b >> p;
    cout << a << '^' << b << " mod " << p << '=' << qpow(a, b, p) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}