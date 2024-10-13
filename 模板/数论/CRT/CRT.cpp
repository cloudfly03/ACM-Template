#include<bits/stdc++.h>
using namespace std;
#define int __int128
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF 1e14
#define MOD 998244353
#define lc p<<1
#define rc p<<1|1

const int N = 11;
int n, M = 1;
int r[N], m[N];

ostream& operator<<(ostream& cout, __int128 val) {
    char stk[129], top = 0;
    while (val) {
        stk[++top] = val % 10 + '0';
        val /= 10;
    }
    while (top) cout << stk[top--];
    return cout;
}

istream& operator>>(istream& cin, __int128& val) {
    string s;cin >> s;
    for (auto ch : s) {
        val *= 10;
        val += ch - '0';
    }
    return cin;
}

int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int ret = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;
    return ret;
}

int inv(int a, int mod) {
    int l, r;
    exgcd(a, mod, l, r);
    return (l % mod + mod) % mod;
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        cin >> m[i] >> r[i];
        M *= m[i];
    }
    int x = 0;
    for (int i = 1;i <= n;++i) {
        int c = M / m[i];
        x = ((x + r[i] * c * inv(c, m[i])) % M + M) % M;
    }
    cout << x << endl;
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