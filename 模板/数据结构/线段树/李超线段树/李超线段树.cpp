#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define mpair(x,y) make_pair(x,y)
#define complex complex<ld>
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)
#define endl '\n'
#define PI (ld)(3.141592653589793)
#define INF (int)(1e14)
#define MOD (int)(1e9)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define lc p<<1
#define rc p<<1|1
// #define lc(x) tr[x].lc
// #define rc(x) tr[x].rc
// #define lc(name,x) name[x].lc
// #define rc(name,x) name[x].rc

const int N = 1e5 + 1;
const int M = 39989;

typedef struct {
    ld k, b;
}Line;
Line line[N];
int cnt;
ld f(int id, int x) {
    return line[id].k * x + line[id].b;
}

typedef struct {
    int id;
}SegTree;
SegTree tr[M << 2];

int n;

void update(int p, int l, int r, int L, int R, int id) {
    int m = l + r >> 1;
    if (L <= l && r <= R) {
        if (f(tr[p].id, m) < f(id, m)) swap(tr[p].id, id);
        if (f(tr[p].id, l) <= f(id, l)) update(lc, l, m, L, R, id);
        if (f(tr[p].id, r) <= f(id, r)) update(rc, m + 1, r, L, R, id);
        return;
    }
    if (L <= m) update(lc, l, m, L, R, id);
    if (R > m) update(rc, m + 1, r, L, R, id);
}


pair<int, ld> pmax(const pair<int, ld>& a, const pair<int, ld>&& b) {
    if (fabs(a.second - b.second) >= eps) return (a.second < b.second) ? b : a;
    return (a.first < b.first) ? a : b;
}

pair<int, ld> query(int p, int l, int r, int x) {
    if (l == r) return mpair(tr[p].id, f(tr[p].id, x));
    int m = l + r >> 1;
    pair<int, ld> ans = mpair(tr[p].id, f(tr[p].id, x));
    if (x <= m) return pmax(ans, query(lc, l, m, x));
    else return pmax(ans, query(rc, m + 1, r, x));
}

void solve() {
    cin >> n;
    int lastans = 0;
    for (int i = 1;i <= n;++i) {
        int op;cin >> op;
        if (!op) {
            int k;cin >> k;
            ((k += lastans - 1) %= M) += 1;
            lastans = query(1, 1, M, k).first;
            cout << lastans << endl;
        }
        else {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            ((x1 += lastans - 1) %= M) += 1;
            ((y1 += lastans - 1) %= MOD) += 1;
            ((x2 += lastans - 1) %= M) += 1;
            ((y2 += lastans - 1) %= MOD) += 1;
            ld k, b;
            if (x1 == x2) { k = 0, b = max(y1,y2); }
            else {
                k = 1.0 * (y2 - y1) / (x2 - x1);
                b = -x1 * k + y1;
            }
            line[++cnt].k = k;
            line[cnt].b = b;
            if (x1 > x2) swap(x1, x2);
            update(1, 1, M, x1, x2, cnt);
        }
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