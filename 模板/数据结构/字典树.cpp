#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define endl ('\n')
const int INF = 1e14;
const int MOD = 1e9 + 7;

const int N = 3e6 + 10;

int trie[N][63];
int cnt[N];
int n, m;
int tot;

int hashs(char a) {
    if (a >= 'a' && a <= 'z') return a - 'a';
    if (a >= 'A' && a <= 'Z') return a - 'A' + 26;
    return a - '0' + 52;
}

void solve() {
    for (int i = 0;i <= tot;++i) {
        fill(trie[i], trie[i] + 63, 0);
    }
    fill(cnt, cnt + tot + 1, 0);
    tot = 0;

    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        string s;cin >> s;
        int p = 0;
        for (int j = 0;j < s.size();++j) {
            if (trie[p][hashs(s[j])] == 0) trie[p][hashs(s[j])] = ++tot;
            p = trie[p][hashs(s[j])];
            cnt[p]++;
        }
    }

    for (int i = 1;i <= m;++i) {
        string s;cin >> s;
        int p = 0, j = 0;
        for (;j < s.size();++j) {
            if (trie[p][hashs(s[j])] == 0) break;
            p = trie[p][hashs(s[j])];
        }
        if (j == s.size()) cout << cnt[p] << endl;
        else cout << 0 << endl;
    }
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}