#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl '\n'
#define MOD 998244353
#define INF ((1<<31) - 1)
// #define lc (p<<1)
// #define rc (p<<1|1)

const int N = 1e5 + 1;
string Pre, Mid;
int idx[N], mp[N];

typedef struct {
    char val;
    int lc, rc;
}Tnode;
Tnode tr[N];
int cnt;


void build(int l, int r) {
    int p = ++cnt;
    tr[cnt] = { Pre[cnt],0,0 };
    if (l >= r) return;
    if (mp[tr[p].val] <= r && mp[tr[p].val] >= l) {
        if (mp[tr[p].val] > l) {
            tr[p].lc = cnt + 1;
            build(l, mp[tr[p].val] - 1);
        }
        if (mp[tr[p].val] < r) {
            tr[p].rc = cnt + 1;
            build(mp[tr[p].val] + 1, r);
        }
    }
}

void dfs(int p) {
    if (tr[p].lc) dfs(tr[p].lc);
    if (tr[p].rc) dfs(tr[p].rc);
    cout << tr[p].val;
}

void solve() {
    cin >> Pre >> Mid;
    Pre = ' ' + Pre;
    Mid = ' ' + Mid;

    for (int i = 1;i < Mid.size();++i)
        idx[Mid[i]] = i;

    for (int i = 1;i < Pre.size();++i)
        mp[Pre[i]] = idx[Pre[i]];

    build(1, Pre.size() - 1);

    dfs(1);
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
