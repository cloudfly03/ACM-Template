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
#define eps 1e-6
#define lc p<<1
#define rc p<<1|1

const int N = 101;
int a[N][N + 1];
int n;

int qpow(int base, int p) {
    int ans = 1;
    while (p) {
        if (p) ans = ans * base % MOD;
        base = base * base % MOD;
        p >>= 1;
    }
    return ans;
}

int inv(int x) {
    return qpow(x, MOD - 2);
}

bool gauss() {
    for (int i = 1;i <= n;++i) {
        int posx = i;
        for (int k = i;k <= n;++k)
            if (a[k][i]) { posx = k;break; }
        if (posx != i) swap(a[i], a[posx]);
        if (!a[i][i]) return false; /*不存在唯一解或无解*/
        int rev = inv(a[i][i]);
        for (int j = i + 1;j <= n + 1;++j)
            a[i][j] = a[i][j] * rev % MOD;
        for (int k = i + 1;k <= n;++k)
            for (int j = n + 1;j >= i;--j)
                a[k][j] = ((a[k][j] - a[k][i] * a[i][j]) % MOD + MOD) % MOD;
    }
    for (int i = n;i > 0;--i)
        for (int j = n;j > i;--j)
            a[i][n + 1] = ((a[i][n + 1] - a[i][j] * a[j][n + 1]) % MOD + MOD) % MOD;
    return true;
}

void solve() {
    cout << fixed << setprecision(2);
    cin >> n;
    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= n + 1;++j)
            cin >> a[i][j];

    if (!gauss()) cout << "No Solution" << endl;
    else {
        for (int i = 1;i <= n;++i)
            cout << a[i][n + 1] << endl;
    }
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