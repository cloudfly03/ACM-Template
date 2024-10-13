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

map<int, int> mp;

void solve() {
    int x;cin >> x;
    for (int i = 2;i * i <= x;++i)
        while (x % i == 0) x /= i, mp[i]++;
    if (x != 1) mp[x]++;

    for (auto [v, t] : mp)
        cout << v << ' ' << t << endl;
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