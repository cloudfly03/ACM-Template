#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define INF 1e14
#define MOD 998244353
#define endl '\n'


const int N = 1e6 + 10;

int trie[N][26], tot, cnt[N];
int nxt[N];
int vis[N];
int n;

void solve() {
    cin >> n;
    for (int i = 1;i <= n;++i) {
        string s;cin >> s;
        int p = 0;
        for (auto ch : s) {
            if (!trie[p][ch - 'a']) trie[p][ch - 'a'] = ++tot;
            p = trie[p][ch - 'a'];
        }
        cnt[p]++;
    }

    queue<int> q;
    for (int i = 0;i < 26;++i) {
        if (trie[0][i]) q.push(trie[0][i]);
    }

    while (q.size()) {
        int u = q.front();q.pop();
        for (int i = 0;i < 26;++i) {
            int v = trie[u][i];
            if (v) { nxt[v] = trie[nxt[u]][i];q.push(v); }
            else trie[u][i] = trie[nxt[u]][i];
        }
    }

    string t;cin >> t;

    int ans = 0;
    for (int i = 0, j = 0;i < t.size();++i) {
        j = trie[j][t[i] - 'a'];
        for (int k = j;k && ~cnt[k];k = nxt[k]) {
            ans += cnt[k];
            cnt[k] = -1;
        }
    }
    cout << ans << endl;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}