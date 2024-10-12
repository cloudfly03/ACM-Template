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

const int N = 1e5 + 10;
int a[N], b[N];
int n;

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
    int res = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i)
        cin >> a[i] >> b[i];
    int m1 = a[1], r1 = b[1], x, y;
    for (int i = 2;i <= n;++i) {
        int m2 = a[i], r2 = b[i];
        int GCD = exgcd(m1, m2, x, y);
        if ((r2 - r1) % GCD) return;//无解
        int mod = m2 / GCD;
        x = x * (r2 - r1) / GCD;
        x = (x % mod + mod) % mod;
        r1 = m1 * x + r1;
        m1 = m1 * m2 / GCD;
    }
    cout << (r1 % m1 + m1) % m1 << endl;
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