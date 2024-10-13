#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9+9)
#define eps (ld)(1e-12)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1

const int N = 5505;
int n, m, cnt;
int u[N], d[N], l[N], r[N];//指针
int row[N], col[N];//行/列号
int h[N];//行头指针
int s[N];//列1个数
int ans[N];

void init() {
    for (cnt = 0;cnt <= m;++cnt) {
        u[cnt] = d[cnt] = cnt;
        l[cnt] = cnt - 1, r[cnt] = cnt + 1;
    }
    cnt--;
    l[0] = cnt, r[cnt] = 0;
}

void link(int x, int y) {
    row[++cnt] = x, col[cnt] = y, s[y]++;
    u[cnt] = u[y];
    d[u[y]] = cnt;
    d[cnt] = y;
    u[y] = cnt;
    if (!h[x])
        h[x] = r[cnt] = l[cnt] = cnt;
    else {
        l[cnt] = l[h[x]];
        r[l[h[x]]] = cnt;
        r[cnt] = h[x];
        l[h[x]] = cnt;
    }
}

void remove(int y) {
    l[r[y]] = l[y], r[l[y]] = r[y];
    for (int i = d[y];i != y;i = d[i])
        for (int j = r[i];j != i;j = r[j])
            u[d[j]] = u[j], d[u[j]] = d[j], s[col[j]]--;
}

void resume(int y) {
    l[r[y]] = y, r[l[y]] = y;
    for (int i = u[y];i != y;i = u[i])
        for (int j = l[i];j != i;j = l[j])
            u[d[j]] = j, d[u[j]] = j, s[col[j]]++;
}

bool dance(int dep) {
    if (!r[0]) {
        for (int i = 1;i < dep;++i)
            cout << ans[i] << ' ';
        cout << endl;
        return true;
    }

    int y = r[0];
    for (int i = r[0];i;i = r[i])
        if (s[i] < s[y]) y = i;

    remove(y);
    for (int i = d[y];i != y;i = d[i]) {
        ans[dep] = row[i];
        for (int j = r[i];j != i;j = r[j]) remove(col[j]);
        if (dance(dep + 1)) return true;
        for (int j = l[i];j != i;j = l[j]) resume(col[j]);
    }
    resume(y);
    return false;
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= m;++j) {
            int t;cin >> t;
            if (t) link(i, j);
        }

    if (!dance(1)) cout << "No Solution!" << endl;
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