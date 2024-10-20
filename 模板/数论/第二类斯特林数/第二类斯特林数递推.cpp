#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define rand mt19937_64
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e8+1)
#define MOD (int)(998244353)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
rand rnd(clock());

const int N = 5e3 + 1;
int S2[N][N];

void init() {
    S2[0][0] = 1;
    for (int i = 1;i < N;++i)
        for (int j = 1;j <= i;++j)
            S2[i][j] = (S2[i - 1][j - 1] + j * S2[i - 1][j]) % MOD;
}

void solve() {
    init();
    for (int i = 0;i < N;++i) {
        for (int j = 0;j <= i;++j)
            cout << S2[i][j] << ' ';
        cout << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    // freopen("test.err", "w", stderr);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}