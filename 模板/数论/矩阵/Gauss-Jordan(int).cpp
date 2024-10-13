#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define INF (int)(1e14)
#define MOD (int)(1e9+7)
#define eps (ld)(1e-6)
#define lc p<<1
#define rc p<<1|1

const int N = 401;
int a[N][N << 1];
int n;

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

bool gauss_jordan() {
    for (int i = 1;i <= n;++i) {
        int posx = i;
        for (int k = i;k <= n;++k)
            if (a[k][i]) { posx = k;break; }
        if (posx != i) swap(a[i], a[posx]);
        if (!a[i][i]) return false; /*无解*/
        int rev = inv(a[i][i]);
        for (int k = 1;k <= n;++k) {
            if (k == i || !a[k][i])continue;
            int f = a[k][i] * rev % MOD;
            for (int j = i;j <= (n << 1);++j)
                a[k][j] = ((a[k][j] - a[i][j] * f) % MOD + MOD) % MOD;
        }
        for (int j = i;j <= (n << 1);++j)
            a[i][j] = a[i][j] * rev % MOD;
    }
    return true;
}

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= n;++j)
            cin >> a[i][j];
    for (int i = 1;i <= n;++i) a[i][i + n] = 1;
    if (gauss_jordan()) {
        for (int i = 1;i <= n;++i) {
            for (int j = n + 1;j <= (n << 1);++j)
                cout << a[i][j] << ' ';
            cout << endl;
        }
    }
    else cout << "No Solution" << endl;
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