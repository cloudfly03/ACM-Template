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
ld a[N][N << 1];
int n;

bool gauss_jordan() {
    for (int i = 1;i <= n;++i) {
        int posx = i;
        for (int k = i;k <= n;++k)
            if (fabs(a[k][i]) > eps) { posx = k;break; }
        if (posx != i) swap(a[i], a[posx]);
        if (fabs(a[i][i]) < eps) return false; /*无解*/
        for (int k = 1;k <= n;++k) {
            if (k == i || fabs(a[k][i]) < eps)continue;
            ld f = a[k][i] / a[i][i];
            for (int j = i;j <= (n << 1);++j)
                a[k][j] -= a[i][j] * f;
        }
        for (int j = (n << 1);j >= i;--j)
            a[i][j] /= a[i][i];
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