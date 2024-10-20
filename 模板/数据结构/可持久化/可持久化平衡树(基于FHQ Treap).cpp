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
#define INF (int)(2147483647)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

#define lc(x) tr[x].lc
#define rc(x) tr[x].rc

const int N = 5e5 + 1;

typedef struct {
    int lc, rc;
    int k, v;
    int sz;
}FHQTreap;
FHQTreap tr[N * 50];
rand rnd(clock());
int root[N], cnt;

int initnode(int v) {
    tr[++cnt].v = v;
    tr[cnt].k = rnd();
    tr[cnt].sz = 1;
    return cnt;
}

void pushup(int p) {
    tr[p].sz = tr[lc(p)].sz + tr[rc(p)].sz + 1;
}

void split(int p, int v, int& x, int& y) {
    if (!p) { x = y = 0; return; }
    if (tr[p].v <= v) {
        x = ++cnt;tr[x] = tr[p];
        split(rc(x), v, rc(x), y);
        pushup(x);
    }
    else {
        y = ++cnt;tr[y] = tr[p];
        split(lc(y), v, x, lc(y));
        pushup(y);
    }
}

// 动态开点merge
// int merge(int x, int y) {
//     if (!x || !y) return x + y;
//     int p = ++cnt;
//     if (tr[x].k < tr[y].k) {
//         tr[p] = tr[x];
//         rc(p) = merge(rc(x), y);
//     }
//     else {
//         tr[p] = tr[y];
//         lc(p) = merge(x, lc(y));
//     }
//     pushup(p);
//     return p;
// }

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (tr[x].k < tr[y].k) {
        rc(x) = merge(rc(x), y);
        pushup(x);return x;
    }
    else {
        lc(y) = merge(x, lc(y));
        pushup(y);return y;
    }
}

void insert(int& root, int v) {
    int x, y;
    split(root, v, x, y);
    x = merge(x, initnode(v));
    root = merge(x, y);
}

void del(int& root, int v) {
    int x, y, z;
    split(root, v, x, y);
    split(x, v - 1, x, z);
    z = merge(lc(z), rc(z));
    root = merge(merge(x, z), y);
}

int getrk(int& root, int v) {
    int x, y;
    split(root, v - 1, x, y);
    int ans = tr[x].sz + 1;
    root = merge(x, y);
    return ans;
}

int getv(int root, int rk) {
    while (root) {
        if (tr[lc(root)].sz + 1 < rk) rk -= tr[lc(root)].sz + 1, root = rc(root);
        else if (tr[lc(root)].sz >= rk) root = lc(root);
        else return tr[root].v;
    }
}

int getpre(int& root, int v) {
    int x, y, ans = -INF;
    split(root, v - 1, x, y);
    if (x) ans = getv(x, tr[x].sz);
    root = merge(x, y);
    return ans;
}

int getsuc(int& root, int v) {
    int x, y, ans = INF;
    split(root, v, x, y);
    if (y) ans = getv(y, 1);
    root = merge(x, y);
    return ans;
}

int n;

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        int t, op, x;cin >> t >> op >> x;
        root[i] = root[t];
        if (op == 1) insert(root[i], x);
        else if (op == 2) del(root[i], x);
        else if (op == 3) cout << getrk(root[i], x) << endl;
        else if (op == 4) cout << getv(root[i], x) << endl;
        else if (op == 5) cout << getpre(root[i], x) << endl;
        else cout << getsuc(root[i], x) << endl;
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