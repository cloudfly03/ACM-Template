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
string Lst, Mid;
int idx[N], mp[N];

typedef struct {
    char val;
    int lc, rc;
}Tnode;
Tnode tr[N];
int cnt;


void build(int l, int r) {
    int p = ++cnt;
    tr[cnt] = { Lst[cnt],0,0 };
    if (l >= r) return;
    if (mp[tr[p].val] <= r && mp[tr[p].val] >= l) {
        if (mp[tr[p].val] < r) {
            tr[p].rc = cnt + 1;
            build(mp[tr[p].val] + 1, r);
        }
        if (mp[tr[p].val] > l) {
            tr[p].lc = cnt + 1;
            build(l, mp[tr[p].val] - 1);
        }
    }
}

void dfs(int p) {
    cout << tr[p].val;
    if (tr[p].lc) dfs(tr[p].lc);
    if (tr[p].rc) dfs(tr[p].rc);
}

void solve() {
    cin >> Lst >> Mid;
    reverse(all(Lst));
    Lst = ' ' + Lst;
    Mid = ' ' + Mid;

    for (int i = 1;i < Mid.size();++i)
        idx[Mid[i]] = i;

    for (int i = 1;i < Mid.size();++i)
        mp[Lst[i]] = idx[Lst[i]];

    build(1, Lst.size() - 1);

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
