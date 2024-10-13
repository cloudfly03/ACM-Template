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
// #define lc p<<1
// #define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 9 + 1;
const int A = 81 + 1; //单元格数
const int B = 324 + 1; //列数
const int C = 324 * 9 + B; //单元数
const int D = 81 * 9 + 1;

int cnt;
int u[C], d[C], l[C], r[C];//指针
int row[C], col[C];//行/列号
int h[D];//行头指针
int s[B];//列1个数
int ans, ret;
int a[N][N], sc[N][N];

void init() {
    for (cnt = 0;cnt < B;++cnt) {
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

bool dance() {
    if (!r[0]) {
        ans = max(ans, ret);
        return true;
    }
    int y = r[0];
    for (int i = r[0];i;i = r[i])
        if (s[i] < s[y]) y = i;

    int flag = false;
    remove(y);
    for (int i = d[y];i != y;i = d[i]) {
        int x = (row[i] - 1) / 81 + 1;
        int y = (row[i] - 1) % 81 / 9 + 1;
        int v = (row[i] - 1) % 9 + 1;
        ret += v * sc[x][y];
        for (int j = r[i];j != i;j = r[j]) remove(col[j]);
        flag |= dance();
        for (int j = l[i];j != i;j = l[j]) resume(col[j]);
        ret -= v * sc[x][y];
    }
    resume(y);
    return flag;
}

void solve() {
    init();
    int t = 0;
    for (int i = 1;i <= 9;++i) {
        for (int j = 1;j <= 9;++j) {
            for (int v = 1;v <= 9;++v) {
                ++t;
                link(t, (i - 1) * 9 + j);
                link(t, 81 + (i - 1) * 9 + v);
                link(t, 81 * 2 + (j - 1) * 9 + v);
                link(t, 81 * 3 + ((i - 1) / 3 * 3 + (j - 1) / 3) * 9 + v);
            }
        }
    }

    for (int i = 1;i <= 9;++i) {
        for (int j = 1;j <= 9;++j) {
            if (i == 1 || i == 9 || j == 1 || j == 9) sc[i][j] = 6;
            else if (i == 2 || i == 8 || j == 2 || j == 8) sc[i][j] = 7;
            else if (i == 3 || i == 7 || j == 3 || j == 7) sc[i][j] = 8;
            else if (i == 4 || i == 6 || j == 4 || j == 6) sc[i][j] = 9;
            else if (i == 5 && j == 5) sc[i][j] = 10;
        }
    }

    for (int i = 1;i <= 9;++i)
        for (int j = 1;j <= 9;++j) {
            cin >> a[i][j];
            if (a[i][j]) {
                ret += a[i][j] * sc[i][j];
                remove((i - 1) * 9 + j);
                remove(81 + (i - 1) * 9 + a[i][j]);
                remove(81 * 2 + (j - 1) * 9 + a[i][j]);
                remove(81 * 3 + ((i - 1) / 3 * 3 + (j - 1) / 3) * 9 + a[i][j]);
            }
        }

    ans = ret;

    if (dance())
        cout << ans << endl;
    else cout << -1 << endl;
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