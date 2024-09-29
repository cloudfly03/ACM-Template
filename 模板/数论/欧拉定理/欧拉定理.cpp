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

// 欧拉定理 gcd(a, m) = 1
// ans = a ^ ( b % phi(m) ) ( mod m )

int a, m, b;
int x, phi;


int qpow(int base, int p) {
    int ans = 1;
    while (p) {
        if (p & 1) ans = ans * base % m;
        base = base * base % m;
        p >>= 1;
    }
    return ans;
}

void solve() {
    cin >> a >> m;
    x = phi = m;
    //计算欧拉函数
    for (int i = 2;i * i <= x;++i)
        if (x % i == 0) {
            while (x % i == 0)
                x /= i;
            phi = phi * (i - 1) / i;
        }
    if (x > 1) phi = phi * (x - 1) / x;

    char ch;
    while (cin >> ch) {
        b *= 10;
        b += ch - '0';
        b %= phi;
    }

    cout << qpow(a, b) << endl;
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