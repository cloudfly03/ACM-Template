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

//欧拉函数 1~n 中与 n 互质的数的个数
//o(sqrt(n))
int x;

bool isprime(int x) {
    if (x == 1) return false;
    for (int i = 2;i * i <= x;++i)
        if (x % i == 0) return false;
    return true;
}

void solve() {
    cin >> x;
    int phi = x;
    if (isprime(x)) phi--;
    else {
        for (int i = 2;i * i <= x;++i)
            if (x % i == 0) {
                while (x % i == 0) x /= i;
                phi = phi * (i - 1) / i;
            }
        if (x > 1) phi = phi * (x - 1) / x;
    }

    cout << "phi(" << x << ") = " << phi << endl;
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