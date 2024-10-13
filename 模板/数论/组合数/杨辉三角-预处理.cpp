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

//预处理 O(nm)
//查询 O(1)

const int N = 2001;
int C[N][N];
int q;

void init() {
    for (int i = 0;i < N;++i)
        for (int j = 0;j <= i;++j) {
            if (j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
}

void solve() {
    init();
    cin >> q;
    for (int i = 1;i <= q;++i) {
        int n, m;cin >> n >> m;
        cout << C[n][m] << endl;
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