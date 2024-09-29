#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 1e6 + 1;
string s, t;
int nxt[N];
vector<int> ans;

void solve() {
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    s = ' ' + s;
    t = ' ' + t;
    for (int i = 2, j = 0;i <= m;++i) {
        while (j && t[i] != t[j + 1]) j = nxt[j];
        if (t[i] == t[j + 1]) j++;
        nxt[i] = j;
    }

    for (int i = 1, j = 0;i <= n;++i) {
        while (j && s[i] != t[j + 1]) j = nxt[j];
        if (s[i] == t[j + 1]) j++;
        if (j == m) cout << i - m + 1 << endl;
    }

    for (int i = 1;i <= m;++i) {
        cout << nxt[i] << ' ';
    }
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}