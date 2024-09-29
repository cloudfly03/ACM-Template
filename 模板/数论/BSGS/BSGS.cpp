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

int qpow(int base, int p, int mod) {
    int ans = 1;
    while (p) {
        if (p & 1) ans = ans * base % mod;
        base = base * base % mod;
        p >>= 1;
    }
    return ans;
}

int inv(int x, int mod) {
    return qpow(x, mod - 2, mod);
}

int bsgs(int a, int b, int p) {
    unordered_map<int, int> mp;
    a %= p, b %= p;
    int seg = ceil(pow(p, 0.5));
    int x = qpow(a, seg, p);
    for (int i = 0;i < seg;++i) {
        mp[b] = i;
        b = b * a % p;
    }
    b = x;
    for (int i = 1;i <= seg;++i) {
        if (mp.find(b) != mp.end())
            return i * seg - mp[b];
        b = b * x % p;
    }
    return -1;
}

void solve() {
    int a, b, p;
    cin >> p >> a >> b;
    int ans = bsgs(a, b, p); // a ^ x = b (mod p)
    if (ans != -1) cout << ans << endl;
    else cout << "no solution" << endl;
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