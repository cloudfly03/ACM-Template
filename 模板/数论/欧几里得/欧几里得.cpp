#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

void solve() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}