#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define pii pair<int,int>
#define INF 1e14
#define MOD 998244353
#define endl '\n'


const int N = 2e5 + 10;

int trie[N][26], cnt[N], tot;
int nxt[N];
map<int, vector<int>> mp;
int indeg[N];
int occ[N];

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
        mp[p].push_back(i);
    }

    queue<int> q;
    for (int i = 0;i < 26;++i) {
        if (trie[0][i]) q.push(trie[0][i]);
    }
    while (q.size()) {
        int u = q.front();q.pop();
        for (int i = 0;i < 26;++i) {
            int v = trie[u][i];
            if (v) {
                nxt[v] = trie[nxt[u]][i];
                indeg[nxt[v]]++;
                q.push(v);
            }
            else trie[u][i] = trie[nxt[u]][i];
        }
    }

    int ans[N]{};
    int mx = 0;
    string t;cin >> t;
    for (int i = 0, j = 0;i < t.size();++i) {
        j = trie[j][t[i] - 'a'];
        occ[j]++;
    }

    for (int i = 1;i <= tot;++i)
        if (indeg[i] == 0)
            q.push(i);

    //cout << q.size() << endl;

    while (q.size()) {
        int t = q.front();
        //cout << "t:" << t << endl;
        q.pop();
        for (auto elem : mp[t]) {
            ans[elem] += occ[t];
            //cout << "occ[t]:" << occ[t] << endl;
        }
        occ[nxt[t]] += occ[t];
        occ[t] = 0;
        indeg[nxt[t]]--;
        if (indeg[nxt[t]] == 0) {
            q.push(nxt[t]);
        }
    }

    for (int i = 1;i <= n;++i) {
        cout << ans[i] << endl;
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