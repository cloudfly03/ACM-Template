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
#define INF (int)(1e8)
#define MOD (int)(1e8)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)

#define fa(x) tr[x].p
#define lc(x) tr[x].s[0]
#define rc(x) tr[x].s[1] 
#define notroot(x) lc(fa(x)) == x||rc(fa(x)) == x

const int N = 2e5 + 1;

int n, m;

typedef struct {
    int s[2], p;
    int v, sum;
    bool lag;
}SplayTree;
SplayTree tr[N];

void pushup(int x) {
    tr[x].sum = tr[lc(x)].sum ^ tr[x].v ^ tr[rc(x)].sum;
}

void pushdown(int x) {
    if (!tr[x].lag) return;
    swap(lc(x), rc(x));
    tr[lc(x)].lag ^= 1;
    tr[rc(x)].lag ^= 1;
    tr[x].lag = 0;
}

//x在当前Splay的根向下更新到x节点(扭转)
void pushall(int x) {
    if (notroot(x)) pushall(fa(x));
    pushdown(x);
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p, k = rc(y) == x;
    if (notroot(y)) tr[z].s[rc(z) == y] = x; tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

//将x转到当前splay的根
void splay(int x) {
    pushall(x);
    while (notroot(x)) {
        int y = fa(x), z = fa(y);
        if (notroot(y)) (lc(z) == y) ^ (lc(y) == x) ? rotate(x) : rotate(y);
        rotate(x);
    }
}

//打通x到原树根的路径
void access(int x) {
    for (int y = 0;x;) {
        splay(x);
        rc(x) = y;
        pushup(x);
        y = x, x = fa(x);
    }
}

//将x节点变为（原树）根节点（深度最小）
void beroot(int x) {
    access(x);
    splay(x);
    tr[x].lag ^= 1;//需要反转维护中序遍历深度最小
}

//将 x<->y 路径从LCT中分离出来
void split(int x, int y) {
    beroot(x);//保证x,y联通，若两次access可能不连通，但如果先换到原树的根则打通y->原树根的路径必定能够联通x-y
    access(y);
    splay(y);
}

int getv(int x, int y) {
    split(x, y);
    return tr[y].sum;
}

//找到打通x后原树的根并将其转到LCT根
int findroot(int x) {
    access(x);
    splay(x);
    while (lc(x)) pushdown(x), x = lc(x);
    splay(x);
    return x;
}

void link(int x, int y) {
    beroot(x);
    if (findroot(y) != x) fa(x) = y;
}

void cut(int x, int y) {
    beroot(x);
    if (findroot(y) == x && fa(y) == x && !lc(y)) {
        rc(x) = fa(y) = 0;
        pushup(x);
    }
}

void update(int x, int y) {
    splay(x);
    tr[x].v = y;
    pushup(x);
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;++i) cin >> tr[i].v;
    for (int i = 1;i <= m;++i) {
        int op, x, y;cin >> op >> x >> y;
        if (op == 0) cout << getv(x, y) << endl;
        else if (op == 1) link(x, y);
        else if (op == 2) cut(x, y);
        else update(x, y);
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