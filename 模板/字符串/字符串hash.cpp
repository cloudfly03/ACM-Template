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

const int N = 1e4 + 1;
const int M = 1e3 + 1;
const int P = 131;
string s[N];
int n;
set<int> st;

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        cin >> s[i];
    }

    for (int i = 1;i <= n;++i) {
        int hashval = 0;
        for (int j = 0;j < s[i].size();++j) {
            hashval = hashval * P % MOD;
            hashval = (hashval + s[i][j]) % MOD;
        }
        st.insert(hashval);
    }

    cout << st.size() << endl;
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
