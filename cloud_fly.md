# 起手式
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

// inline int read() {
//     register int x = 0, t = 1;
//     register char ch = getchar(); 
//     while (ch < '0'|| ch > '9'){
//         if (ch == '-')
//             t = -1;
//         ch = getchar();
//     }
//     while (ch >= '0' && ch <= '9'){
//         x = (x << 1) + (x << 3) + (ch ^ 48);  
//         ch = getchar();
//     }
//     return x * t;
// }

// void print128(__int128 x) {
//     if (x < 0)
//         putchar('-'), x = -x;
//     if (x > 9)
//         print128(x / 10);
//     putchar(x % 10 + '0');
// }

inline int read() {
    int c;
    cin >> c;
    return c;
}

inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }


int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

void solve() {}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T = 1;
    T = read();
    while (T--)
        solve();

    return 0;
}
```

# 基础算法

## 前缀和与差分
一维差分：
```c++
diff[i] = a[i] - a[i - 1];
a[i] = a[i - 1] + diff[i];
diff[l] += c;
diff[r + 1] -= c;
```

二维前缀和：
```c++
b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i-1][ j-1] + a[i][j]
Sum(子矩阵和) = b[x2][y2] - b[x2][y1- 1] - b[x1 - 1][y2] + b[x1 - 1][y1 - 1]
```

二维差分：
假设我们已经构建好了二维数组b[][] 的二维差分数组 a[][] ，现在要处理的是如何在a[][] 上加c,使其二维前缀和数组b[][]在指定的子矩阵内的所有元素都加上一个c 。
```c++
#include <iostream>
using namespace std;
const int N = 1e3 + 10;
int b[N][N], a[N][N];
void insert(int x1, int y1, int x2, int y2, int c)
{
    a[x1][y1] += c;
    a[x2 + 1][y1] -= c;
    a[x1][y2 + 1] -= c;
    a[x2 + 1][y2 + 1] += c;
}
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> b[i][j],
            a[i][j] = b[i][j] - b[i][j-1] - b[i-1][j] + b[i-1][j-1];//构建二维差分数组
    while (q--)
    {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1, y1, x2, y2, c); //这一步是精髓
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];  //二维前缀和
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            printf("%d ", b[i][j]);//输出操作完所有步骤后的b[][]
        }
        printf("\n");
    }
    return 0;
}
```

## 二分查找

```C++
int l = 0, r = n + 1;

while (l < r) {

  	int mid = l + r + 1 >> 1;

  	if (check(mid)) l = mid;

  	else r = mid - 1;
}


int l = 0, r = n;

while (l < r) {

  	int mid = l + r >> 1;

  	if (check(mid)) r = mid;

  	else l = mid + 1;
}
```

## 三分查找求极值

```C++
//https://codeforces.com/contest/1928/problem/D
int check(int k) {
    int res = 0;
    rep(i, 1, n) {
        if (c[i] <= k) {
            res += c[i] * (c[i] - 1) / 2;
        }
        else {
            res += c[i] * (c[i] - 1) / 2;
            int avg = c[i] / k, mod = c[i] % k;
            res -= mod * (avg + 1) * avg / 2;
            res -= (k - mod) * avg * (avg - 1) / 2;
        }
    }
    res *= b;
    res -= (k - 1) * x;
    return res;
}
void solve() {
    n = read(), b = read(), x = read();
    rep(i, 1, n) c[i] = read();

    int l = 1, r = 2e5 + 10;
    while (l < r) {
        int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
        if (check(lmid) <= check(rmid))
            l = lmid + 1;
        else
            r = rmid - 1;
    }

    cout << max(check(l), check(r)) << '\n';
}
```


## 分治法：归并排序

```C++
int a[N];
int tmp[N];
int ans = 0;//逆序对数量
void merge(int l, int r) {
    if (l == r) return ;
    int mid = l + r >> 1;
    merge(l, mid);
    merge(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (i = l; i <= r; i++) a[i] = tmp[i];
}
```


# 动态规划

## 基本线性dp

### 最长上升子序列I  O（n ^ 2）
```c++
int f[N];
int a[N];
void solve() {
	int n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	a[0] = -INF;
	for (int i = 1; i <= n; i++) f[i] = 1;
	
	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i] > a[j]) f[i] = max(f[i], f[j] + 1);
		}
		res = max(res, f[i]);
	}
	cout << res << endl;
}
```

### 最长上升子序列II O(nlogn) 贪心+二分

```C++
int a[N];
int f[N];//长度为i的上升子序列末位的最小值，随着i的增加而增加
int n;
int LIS() {
    int len = 0;
    f[0] = -inf;
    for (int i = 1; i <= n; i++) {
        if (a[i] > f[len]) f[++len] = a[i];
        else {
            int l = 1, r = len;
            while (l < r) {
                int mid = l + r >> 1;
                if (f[mid] > a[i]) r = mid;
                else l = mid + 1;
            }
            f[l] = a[i];
        }
    }
    return len;
}
```

### 最长公共子序列
1.
朴素，n <= 1e3, m <= 1e3 时间复杂度 O(n * m)
```c++
int f[N][N];//f[i][j]：a中前i个字符， b中前j个字符的最长公共子序列的最大长度
char a[N], b[N];
void solve() {
	int n = read(), m = read();
	cin >> a + 1 >> b + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
            //省略a[i] != a[j]时 f[i][j] = f[i - 1][j - 1]
            //f[i - 1][j],f[i][j - 1], f[i - 1][j - 1] 之间有重叠，但是是求最大值因此无影响
			f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			if (a[i] == b[j]) 
				f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
		}
	}
	cout << f[n][m] << endl;
}
```

2.
题面链接：https://www.luogu.com.cn/problem/P1439
给出1,2,…,n 的两个排列P1和Pn
其中 n <= 1e5，求它们的最长公共子序列
时间复杂度O(n * logn)
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

int n;
int a[N];
int f[N];
int LIS() {
    int len = 0;
    f[0] = -inf;
    for (int i = 1; i <= n; i++) {
        if (a[i] > f[len]) f[++len] = a[i];
        else {
            int l = 1, r = len;
            while (l < r) {
                int mid = l + r >> 1;
                if (f[mid] > a[i]) r = mid;
                else l = mid + 1;
            }
            f[l] = a[i];
        }
    }
    return len;
}

void solve() {
    n = read();
    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        int x = read();
        mp[x] = i;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = mp[read()];
    }

    int ans = LIS();
    print(ans);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}
```

## 背包

### 背包求组合种类
和顺序无关，先遍历物品再遍历背包
```C++
class Solution {
public:
    int change(int m, vector<int>& a) {
        int n = a.size();
        vector<int> dp(m + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = a[i]; j <= m; j++)//背包物品可重复使用
                dp[j] += dp[j - a[i]];
        }

        return dp[m];
    }
};
```

### 背包求排列种类
和顺序有关，先遍历背包再遍历物品
```C++
class Solution {
public:
    int combinationSum4(vector<int>& a, int m) {
        int n = a.size();
        vector<long long> dp(m + 1, 0);
        dp[0] = 1;
        for (int j = 1; j <= m; j++) {//背包物品可重复使用
            for (int i = 0; i < n; i++) {
                if (j >= a[i])
                    dp[j] += dp[j - a[i]];
            }
        }
        return dp[m];
    }
};
```

### 超大背包问题（折半搜索）
折半搜索
```C++

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 42;
const int INF = 1e18;
 
int n, m;
int w[N],v[N];
 
pair<int, int> a[1 << (N/2)];//体积、价值
 
void solve(){
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

    int n2 = n / 2;
    for (int i = 0;i < 1 << n2;i ++){//枚举组合
        int ww = 0,vv = 0;
        for (int j = 0;j < n2;j ++){//枚举第几个
            if (i >> j & 1){
                ww += w[j];
                vv += v[j];
            }
        }
        a[i] = {vv, ww};
    }
 
    sort(a, a + (1<<n2));//体积从小到大排序
    int p = 1;
    for (int i = 1;i < 1 << n2;i ++){//让体积增大时，价值也跟着增大
        if (a[p - 1].second < a[i].second) {
            a[p] = a[i];
            p++;
        }
    }
 
    int res = 0;
    for (int i = 0;i < 1 << (n-n2);i++){
        int ww = 0,vv = 0;
        for (int j = 0;j < n - n2;j++){
            if (i >> j & 1 ){
                ww += w[n2 + j];
                vv += v[n2 + j];
            }
        }
        if (vv <= m){
            int t = (lower_bound(a, a + p,make_pair(m - vv,INF))-1)->second;
            res = max(res,ww + t);
        }
    }
 
    cout << res << endl;
}

signed main() {
    int _ = 1;
    while (_--) solve();
    return 0;
}
```

## 区间dp
石子合并：有n堆石子排成一排，每次只能合并相邻的两堆，花费为这两堆石子的总数。求最终合为一堆的最小花费。

dp设计：dp[i][j]:合并第i堆到第j堆的最小花费
```C++

状态转移方程：dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + s[j] - s[i - 1]);
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int n; cin >> n;
	vector<int> s(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		s[i] = s[i - 1] + x;
	}

	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0x3f3f3f3f));
	for (int i = 1; i <= n; i++) dp[i][i] = 0;
	
	时间复杂度(O(n^3))
	for (int len = 1; len <= n; len++) {//从小区间向大区间合并
		for (int i = 1; i + len - 1 <= n; i++) {//枚举左端点
			int j = i + len - 1;
			for (int k = i; k < j; k++) {//枚举中间节点
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + s[j] - s[i - 1]);
			}
		}
	}

	cout << dp[1][n] << endl;
	return 0;
}
```

## 树形dp
问题：

小红拿到了一棵树，初始所有节点都是白色。

小红希望染红若干个节点，使得不存在两个白色节点相邻。

小红想知道，共有多少种不同的染色方案？

由于答案过大，请对1e9 + 7取模。

```C++

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) x.begin(),x.end()
#define PII pair<int, int>

const int N = 1e5 + 10;
int f[N][2];
//0:白色， 1：红色
vector<int> e[N];

const int mod = 1e9 + 7;

void dfs(int u, int fa) {
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        f[u][0] *= f[v][1];
        f[u][1] *= (f[v][0] + f[v][1]);
        f[u][0] %= mod;
        f[u][1] %= mod;
    }
}

void solve() {
    int n; cin >> n;
    int root;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        root = u;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++)
            f[i][j] = 1;
    }
    if (n == 1) {
        cout << 2 << '\n';
        return ;
    }
    
    dfs(root, 0);
    cout << (f[root][0] + f[root][1]) % mod << '\n';
}

signed main() {
    //freopen("../1.in", "r", stdin);
    //freopen("../1.out", "w", stdout);

    solve();
    return 0;
}
```



## 状压dp
给定一个有权无向图，包括n个点，从 0到 n - 1，以及连接n个点的边，求从起点0到终点n - 1的最短哈密顿路径。 (n <= 20)

dp设计：设S是图的一个子集，dp[S][j]:集合S的最短哈密顿路径，即表示从起点$0$出发，经过S中的所有点，到达终点j的最短路径，集合S中包含j点。

适用:（1）子集问题,元素无先后关系,有2^n个子集;（2）排列问题：对所有元素进行全排列,有n! 个全排列.

$dp[1][0] = 0;$

```C++

for (int i = 1; i < (1 << n); i++) {//从小集合扩展到大集合
	for (int j = 0; j < n; j++) //枚举点
    {
        if ((i >> j) & 1) {
            for (int k = 0; k < n; k++) {
                if ((i ^ (1 << j)) >> k & 1) {//k属于集合（S-j）
                    dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][k] + dist[k][j]);
                }
            }
        }
    }
}

int ans = dp[(1 << n) - 1][n - 1];
```

## 数位统计dp

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
int dp[20][20];
int a[10];
int cnt;
int dfs(int pos, int pre, int lead, int limit) {
    if (pos == 0) return 1;
    if (!limit && dp[pos][pre] != -1) return dp[pos][pre];
    int up;
    if (limit) up = a[pos];
    else up = 9;
    int ans = 0;
    for (int i = 0; i <= up; i++) {
        if (abs(i - pre) < 2) continue;
        if (lead && i == 0) ans += dfs(pos - 1, -2, 1, limit && i == up);
        else ans += dfs(pos - 1, i, 0, limit && i == up);
    }
    if (!limit) dp[pos][pre] = ans;
    return ans;
}

void solve() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            dp[i][j] = -1;
        }
    }
    int x; cin >> x;
    x--;
    while (x) {
        cnt++;
        a[cnt] = x % 10;
        x /= 10;
    }
    int t1 = dfs(cnt, -2, 1, 1);
    cin >> x;
    cnt = 0;
    while (x) {
        cnt++;
        a[cnt] = x % 10;
        x /= 10;
    }
    int t2 = dfs(cnt,-2, 1, 1);
    cout << t2 - t1 << '\n';
}

signed main() {
    //freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(0);
    // int T; cin >> T;
    // while (T--) 
        solve();

    return 0;
}
```

## dp的优化
### 单调队列优化
题目链接：https://codeforces.com/contest/372/problem/C
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

int g[N];
int f[N];
struct node {
    int a, b, t;
}arr[N];

void solve() {
    int n = read(), m = read(), d = read();
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        int a = read(), b = read(), t = read();
        arr[i] = {a, b, t};
        sum += b;
    }

    for (int j = 1; j <= n; j++) f[j] = abs(arr[1].a - j);
    // eprintn(f, n);

    for (int i = 2; i <= m; i++) {
        auto [a, b, _] = arr[i];
        int t = arr[i].t - arr[i - 1].t;
        for (int j = 1; j <= n; j++) {
            g[j] = f[j];
            f[j] = inf;
        }
        deque<int> q1, q2;
        for (int j = 1; j <= n; j++) {
            while (q1.size() && j - q1.front() - 1 >= t * d) q1.pop_front();
            while (q1.size() && g[j] <= g[q1.back()]) q1.pop_back();
            q1.push_back(j);
            f[j] = min(f[j], g[q1.front()] + abs(a - j));
        }
        for (int j = n; j >= 1; j--) {
            while (q2.size() && q2.front() - j - 1 >= t * d) q2.pop_front();
            while (q2.size() && g[j] <= g[q2.back()]) q2.pop_back();
            q2.push_back(j);
            f[j] = min(f[j], g[q2.front()] + abs(a - j));
        } 
        // eprintn(f, n);
    }
    int ans = inf;

    for (int i = 1; i <= n; i++) ans = min(ans, f[i]);
    print(sum - ans);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}
```

### 斜率优化
题目链接：https://www.luogu.com.cn/problem/P3195
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'
#define ld long double

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

int c[N];
int dp[N];
int s[N];
int q[N];

int n, l;
int Y(int j) {
    return dp[j] + s[j] * s[j];
}
int X(int j) {
    return s[j];
}

ld slope(int i, int j) {
    return (ld)(Y(i) - Y(j)) / (X(i) - X(j));
}

int second(deque<int> &q) {
    if (q.size() < 2) return -1;
    int x = q.front();
    q.pop_front();
    int y = q.front();
    q.push_front(x);
    return y;
}

int LastSecond(deque<int> &q) {
    if (q.size() < 2) return -1;
    int x = q.back();
    q.pop_back();
    int y = q.back();
    q.push_back(x);
    return y;
}

void solve() {
    n = read(), l = read();
    l++;
    readn(c, n);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + c[i] + 1;

    deque<int> q;
    q.push_back(0);
    for (int i = 1, j; i <= n; i++) {
        while (q.size() > 1 && slope(q.front(), second(q)) <= 2 * (s[i] - l)) q.pop_front();
        dp[i] = dp[j = q.front()] + (s[i] - s[j] - l) * (s[i] - s[j] - l);
        while (q.size() > 1 && slope(q.back(), LastSecond(q)) >= slope(LastSecond(q), i)) q.pop_back();
        q.push_back(i);
    }
    print(dp[n]);
}


signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}
```

### 四边形不等式优化
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 3e3 + 10;
const int M = N << 1;
const int mod = 998244353;

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

int a[N];
int w[3100][3100];
int dp[3100][400];
int p[3100][400];
void solve() {
    int n = read(), m = read();
    readn(a, n);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            w[i][j] = w[i][j - 1] + a[j] - a[(i + j) / 2];
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = inf;
        }
    }

    dp[0][0] = 0;
    for (int i = 1; i <= m; i++) p[n + 1][i] = n;
    for (int j = 1; j <= m; j++) {
        for (int i = n; i >= j; i--) {
            for (int k = p[i][j - 1]; k <= p[i + 1][j]; k++) {
                if (dp[i][j] > dp[k][j - 1] + w[k + 1][i]) {
                    dp[i][j] = dp[k][j - 1] + w[k + 1][i];
                    p[i][j] = k;
                }
            }
        }
    }
    print128(dp[n][m]);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}
```

### 状态设计优化
题目链接：https://codeforces.com/gym/104857/problem/G

给定一个长为n的01序列，最多把m个0变成1.对于修改后所有极长的1连续段，最大化其中第k长的长度
其中，n <= 2e5, m <= n. k <= 5
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 2e5 + 10;
const int M = N << 1;
const int mod = 998244353;

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

int n, m, k;
int pre[N];
int last[N];
int f[N][6];
int g[N][6];
bool check(int x) {
    for (int i = 1; i <= k; i++) f[0][i] = g[0][i] = inf;
    for (int i = 1; i <= n; i++) {
        f[i][0] = 0;
        for (int j = 1; j <= k; j++) {
            if (i >= x) {
                int t = last[i - x];
                f[i][j] = g[t][j - 1] + i - t - (pre[i] - pre[t]); 
            }
            else {
                f[i][j] = inf;
            }
            g[i][j] = min(g[i - 1][j], f[i - 1][j]);
        }
    }
    int ans = inf;
    for (int i = 1; i <= n; i++) ans = min(ans, f[i][k]);
    return ans <= m;
}

void solve() {
    n = read(), m = read(), k = read();
    string s; cin >> s;
    s = ' ' + s;
    for (int i = 1; i <= n; i++) {
        pre[i] += pre[i - 1];
        if (s[i] == '1') pre[i]++;
    }
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') last[i] = last[i - 1];
        else last[i] = i;
    }

    int l = 1, r = n;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    int ans = -1;
    if (check(l)) ans = l;
    print(ans);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}
```

# 字符串

## 序列自动机

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second

#define int long long
#define endl '\n'
const int inf = LONG_LONG_MAX;
using i64 = long long;

const int N = 1e6 + 10;

int nxt[N][26];
int n, k;
int cal1(int l) {
    int r = min(nxt[l]['A' - 'A'] + 1, n + 1);
    r = min(nxt[r]['C' - 'A'] + 1, n + 1);
    r = min(nxt[r]['C' - 'A'] + 1, n + 1);
    r = min(nxt[r]['E' - 'A'] + 1, n + 1);
    r = min(nxt[r]['P' - 'A'] + 1, n + 1);
    r = nxt[r]['T' - 'A'];

    return r;
}

int cal2(int l) {
    int r = min(nxt[l]['W' - 'A'] + 1, n + 1);
    r = nxt[r]['A' - 'A'];

    return r;
}

void solve() {
    cin >> n >> k;
    string s; cin >> s;
    s = ' ' + s;
    for (int j = 0; j < 26; j++) {
        nxt[n + 1][j] = n + 1;
    }

    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 26; j++) {
            if (s[i] == 'A' + j) nxt[i][j] = i;
            else nxt[i][j] = nxt[i + 1][j];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int rl = i + k - 1;
        if (rl > n) break;
        rl = max(rl, cal1(i));
        int rr = cal2(i);
        if (rr >= rl) ans += rr - rl;
    }

    cout << ans << '\n';
}

signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

## 字符串哈希
例题: https://codeforces.com/contest/1979/problem/D
### 线性哈希
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define endl '\n'

using ull = unsigned long long;

/* next is main_solve */
char out[2][10] = {"No", "Yes"};
const int N = 1e6 + 10;
int a[N];
int ans[N];

ull pre[N], suf[N];
ull base = 131;
ull pw[N];
char s1[N], s2[N];
char ss[N];
char rev(char ch) {
    return ch == '0'? '1': '0';
}
void solve(){
    int n, k; cin >> n >> k;
    string s; cin >> s;
    s = ' ' + s;
    for (int i = 1; i <= k; i++) {
        s1[i] = '1';
        s2[i] = '0';
    }
    for (int i = k + 1; i <= n; i++) {
        s1[i] = rev(s1[i - k]);
        s2[i] = rev(s2[i - k]);
    }

    ull h1 = 0, h2 = 0;
    for (int i = 1; i <= n; i++) {
        h1 = h1 * base + s1[i];
        h2 = h2 * base + s2[i];
    }

    for (int i = 1; i <= n; i++) {
        ss[i] = s[n - i + 1];
    }

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] * base + s[i];
        suf[i] = suf[i - 1] * base + ss[i];
    }


    int ans = -1;
    for (int i = 1; i <= n; i++) {
        ull t = (pre[n] - pre[i] * pw[n - i]) * pw[i] + (suf[n] - suf[n - i] * pw[i]);
        if (t == h1 || t == h2) {
            ans = i;
            break;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * base;
    }
    int t; cin >> t;
    while (t--)
        solve();
    return 0;
}
```

### 树上路径哈希
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10;
int n;
int s[N];
vector<int> e[N];
int dep[N], f[N][22];
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; i <= 20; i++) {
        f[u][i] = f[f[u][i - 1]][i - 1];
    }

    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);

    for (int i = 20; i >= 0; i--) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    }

    if (x == y) return x;
    for (int i = 20; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

const int p = 131;
const int mod = 1e9 + 7;
int basep[N];
int pre[N], suf[N];
void dfs1(int u, int fa) {
    pre[u] = (pre[fa] * p % mod + s[u]) % mod;
    suf[u] = (suf[fa] + s[u] * basep[dep[u] - 1] % mod) % mod;
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs1(v, u);
    } 
}

int qmi(int a, int b, int p) {
    int ans = 1;
    a %= p;
    while (b) {
        if (b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}

int get(int x, int y) {
    int lc = lca(x, y);
    int h = (suf[x] - suf[lc] + mod) % mod;
    int t = (pre[y] - (pre[lc] * basep[dep[y] - dep[lc]] % mod) + mod) % mod;
    int len = dep[x] + dep[y] - 2 * dep[lc] + 1;
    h = h * qmi(basep[dep[x] - 1], mod - 2, mod) % mod;
    h = ((h * basep[len - 1] % mod) + (s[lc] * basep[dep[y] - dep[lc]] % mod) + t) % mod;
    return h;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char ch; cin >> ch;
        s[i] = ch - 'a' + 1;
    }

    int root;
    for (int i = 1; i <= n; i++) {
        int father; cin >> father;
        if (!father) root = i;
        else {
            e[i].push_back(father);
            e[father].push_back(i);
        }
    }

    dfs(root, 0);

    basep[0] = 1ll;
    for (int i = 1; i < N; i++) {
        basep[i] = basep[i - 1] * p % mod;
    }
    dfs1(root, 0);

    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        int t1 = get(x, y);
        int t2 = get(y, x);
        if (t1 == t2) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    // int T; cin >> T;
    // while (T--) 
        solve();
    return 0;
}
```

## manacher
马拉车算法：求最长回文子串的算法

注意：这里的N要开三倍
```c++

char a[N];
char s[N];
int d[N];//回文半径
int manacher() {
    int n = strlen(a + 1); // cin >> a + 1;
    //改造串, 使串为奇数串
    int k = 0;
    //s[0]为哨兵
    s[0] = '$', s[++k] = '#';
    for (int i = 1; i <= n; i++) {
        s[++k] = a[i];
        s[++k] = '#';
    }
    n = k;

    d[1] = 1;
    for (int i = 2, l, r = 1; i <= n; i++) {
        if (i <= r) d[i] = min(d[r - i + l], r - i + 1);
        while (s[i- d[i]] == s[i + d[i]]) d[i]++;
        if (i + d[i] - 1 > r) {
            l = i - d[i] + 1;
            r = i + d[i] - 1;
        }
    }

    int res = 1;
    //原串的回文长度 = 新串的回文半径 - 1
    for (int i = 1; i <= n; i++) res = max(res, d[i] - 1);

    return res;
}
```

## kmp
Knuth–Morris–Pratt 算法：给定一个文本 t 和一个字符串 s，我们尝试找到并展示 s 在 t 中的所有出现位置

为了简便起见，我们用 n 表示字符串 s 的长度，用 m 表示文本 t 的长度。
```C++

vector<int> find_occurrences(string text, string pattern) {
    string cur = pattern + '#' + text;
    int sz1 = text.size(), sz2 = pattern.size();
    vector<int> v;
    vector<int> lps = prefix_function(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
      if (lps[i] == sz2) v.push_back(i - 2 * sz2);
    }
    return v;
}
```

## AC自动机
```c++
#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define endl '\n'
using ull = unsigned long long;
char out[2][10] = {"No", "Yes"};
const int N = 1e6 + 10;
/* next is main_solve */

int n, trie[N][26], fail[N], cnt, in[N], vis[N], ans1[N];
int ans2[N];
vector <int> flag[N]; //点对应的字符串
void add (string x, int id) { //建trie树
    int len = x.length (), now = 0;
    for (int i = 0; i < len; i++) {
        int c = x[i] - 'a';
        if (!trie[now][c])
            trie[now][c] = ++cnt;
        now = trie[now][c];
    }
    flag[now].push_back (id);
}

void get_fail () { //添加fail边
    queue <int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i])
            q.push (trie[0][i]);
    while (!q.empty ()) {
        int u = q.front ();
        q.pop ();
        for (int i = 0; i < 26; i++) {
            if (trie[u][i]) {
                fail[trie[u][i]] = trie[fail[u]][i];
                in[fail[trie[u][i]]]++; //fail边指向的点入度+1
                q.push (trie[u][i]);
            }
            else trie[u][i] = trie[fail[u]][i];
        }
    }
}

void query (string x) { //查询答案
    int len = x.length (), now = 0;
    for (int i = 0; i < len; i++) {
        int c = x[i] - 'a';
        now = trie[now][c];
        vis[now]++; //不需跳fail边
    }
}

void topu () { //拓扑排序
    queue <int> q;
    for (int i = 1; i <= cnt; i++)
        if (!in[i])
            q.push (i);
    while (!q.empty ()) {
        int u = q.front ();
        q.pop ();
        for (auto it = flag[u].begin (); it != flag[u].end (); it++)
            ans1[*it] = vis[u];
        int v = fail[u];
        vis[v] += vis[u];
        in[v]--;
        if (!in[v])
            q.push (v);
    }
}


void solve(){
    int n; cin >> n;
    string a, c; cin >> a >> c;
    for (int i = 0; i <= a.size(); i++) {
        for (int j = 0; j < 26; j++) {
            trie[i][j] = 0;
        }
        fail[i] = in[i] = vis[i] = 0;
        flag[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        ans1[i] = ans2[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        string s1, s2; cin >> s1 >> s2;
        add(s1, i);
        if (s2.find(c) != string::npos) ans2[i] = 1;
    }

    get_fail();
    query(a);
    topu();
    for (int i = 1; i <= n; i++) {
        if (ans1[i] > 0 && ans2[i] > 0) {
            cout << i << ' ';
        }
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t; cin >> t;
    while (t--)
        solve();
    return 0;
}
```

# 图论

## 链式前向星 

```c++
int h[N], e[M], ne[M], tot, w[N];

void add(int a, int b, int c) {
    tot++;
    e[tot] = b;
    w[tot] = c;
    ne[tot] = h[a];
    h[a] = tot;
}

for (int i = h[u]; i; i = ne[i]) {
    int v = e[i];......
}
```

## 最短路算法
### dijkstra
单源、正权边的最短路问题

时间复杂度：优先队列，O(mlogm)
```c++
int h[N], e[M], ne[M], tot, w[N];
void add(int a, int b, int c) {
    tot++;
    e[tot] = b;
    w[tot] = c;
    ne[tot] = h[a];
    h[a] = tot;
}
int dist[N];
bool st[N];
int dijkstra(int s){
    memset(dist, INF, sizeof dist);
    dist[s] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0,s});
    while(q.size()){
        auto now = q.top();
        q.pop();
        int u = now.second;
        int t = now.first;
        if(st[u]) continue;
        st[u]=true;
        for(int i = h[u]; i; i = ne[i]){
            int v=e[i];
            if(dist[v] > t + w[i]){
                dist[v] = t + w[i];
                q.push({dist[v], v});
            }
        }
    }
    if(dist[n] == INF) return -1;
    return dist[n];
}
```

### spfa
前言-bellmanford:
单源，且可含负权边的最短路问题，可以判断负环

时间复杂度为 O(n * m)。

先介绍 Bellman–Ford 算法要用到的松弛操作（Dijkstra 算法也会用到松弛操作）。

对于边 $(u,v)$，松弛操作对应下面的式子：dis(v) = min(dis(v), dis(u) + w(u, v))

这么做的含义是显然的：我们尝试用 $S \to u \to v$（其中 $S \to u$ 的路径取最短路）这条路径去更新 v 点最短路的长度，如果这条路径更优，就进行更新。

Bellman–Ford 算法所做的，就是不断尝试对图上每一条边进行松弛。我们每进行一轮循环，就对图上所有的边都尝试进行一次松弛操作，当一次循环中没有成功的松弛操作时，算法停止。

每次循环是 O(m) 的，那么最多会循环多少次呢？

在最短路存在的情况下，由于一次松弛操作会使最短路的边数至少 + 1，而最短路的边数最多为 n - 1，因此整个算法最多执行 n - 1 轮松弛操作。故总时间复杂度为 O( n * m)。

但还有一种情况，如果从 S 点出发，抵达一个负环时，松弛操作会无休止地进行下去。注意到前面的论证中已经说明了，对于最短路存在的图，松弛操作最多只会执行 $n-1$ 轮，因此如果第 $n$ 轮循环时仍然存在能松弛的边，说明从 $S$ 点出发，能够抵达一个负环。

**可以处理负权值，但是不能处理负环。可以判断是否有环以及负环**

SPFA算法的时间复杂度取决于边的数量和图的结构。在一般情况下，SPFA算法的时间复杂度为O(kE)，其中k是一个常数（一般在2到3之间），E是边的数量。然而，在最坏情况下，SPFA算法的时间复杂度可以达到O(VE)，其中V是点的数量，E是边的数量。

很多时候我们并不需要那么多无用的松弛操作。

很显然，只有上一次被松弛的结点，所连接的边，才有可能引起下一次的松弛操作。

那么我们用队列来维护「哪些结点可能会引起松弛操作」，就能只访问必要的边了。

SPFA 也可以用于判断 s 点是否能抵达一个负环，只需记录最短路经过了多少条边，当经过了至少 n 条边时，说明 s 点可以抵达一个负环。

#### 差分约束
核心：dist_v >= dist_v + w or dist_v <= dist_u + w

1.spfa
模板题；https://www.luogu.com.cn/problem/P5960
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

// 快读
// inline int read() {
//     register int x = 0, t = 1;
//     register char ch = getchar(); 
//     while (ch < '0'|| ch > '9'){
//         if (ch == '-')
//             t = -1;
//         ch = getchar();
//     }
//     while (ch >= '0' && ch <= '9'){
//         x = (x << 1) + (x << 3) + (ch ^ 48);  
//         ch = getchar();
//     }
//     return x * t;
// }

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

vector<pii> e[N];

int n, m;
int dist[N];
int vis[N];
int tot[N];
bool spfa() {
    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
    }

    queue<int> q;
    q.push(0);
    vis[0] = 1;
    dist[0] = 0;
    while (q.size()) {
        auto u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w]: e[u]) {
            if (dist[v] <= dist[u] + w) continue;//最短路
            dist[v] = dist[u] + w;
            if (!vis[v]) {
                tot[v]++;
                if (tot[v] == n + 1) return false; // 注意添加了一个超级源点
                q.push(v);
                vis[v] = 1;
            }
        }
    }
    return true;
}

void solve() {
    n = read(), m = read();

    for (int i = 1; i <= m; i++) {
        int v = read(), u = read(), w = read();
        e[u].push_back({v, w});// v <= u + w
    }
    for (int i = 1; i <= n; i++) {
        e[0].push_back({i, 0});
    }

    if (spfa()) {
        printn(dist, n);
    }
    else {
        print("NO");
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}
```

2.tarjan + 拓扑 dag
题目链接：https://www.luogu.com.cn/problem/P3275
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

// 快读
// inline int read() {
//     register int x = 0, t = 1;
//     register char ch = getchar(); 
//     while (ch < '0'|| ch > '9'){
//         if (ch == '-')
//             t = -1;
//         ch = getchar();
//     }
//     while (ch >= '0' && ch <= '9'){
//         x = (x << 1) + (x << 3) + (ch ^ 48);  
//         ch = getchar();
//     }
//     return x * t;
// }

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

vector<pii> e[N];

void addEdge(int x, int y, int w) {
    e[x].push_back({y, w});
} 

int dfn[N];
int low[N];
int scc[N];
int tot;
int instk[N];
int sz[N];
stack<int> stk;
int cnt;

int dp[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk.push(u);
    instk[u] = 1;
    for (auto [v, w]: e[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int v;
        cnt++;
        do {    
            v = stk.top();
            stk.pop();
            instk[v] = 0;
            scc[v] = cnt;
            sz[cnt]++;
        }while (v != u);
    }
}

vector<pii> E[N];

int indeg[N];

void solve() {
    int n = read(), m = read();
    for (int i = 1; i <= m; i++) {
        int op = read(), x = read(), y = read();
        if (op == 1) {
            addEdge(x, y, 0);
            addEdge(y, x, 0);
        }
        else if (op == 2) {
            addEdge(x, y, 1);
        }
        else if (op == 3) {
            addEdge(y, x, 0);
        }
        else if (op == 4) {
            addEdge(y, x, 1);
        }
        else {
            addEdge(x, y, 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    for (int u = 0; u <= n; u++) {
        for (auto [v, w]: e[u]) {
            if (scc[u] == scc[v] && w) {
                print(-1);
                return ;
            }
            else if (scc[u] == scc[v]) continue;
            E[scc[u]].push_back({scc[v], w});
            indeg[scc[v]]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= cnt; i++) {
        dp[i] = -inf;
        if (!indeg[i]) {
            q.push(i);
            dp[i] = 1;
        }
    }

    while (q.size()) {
        auto u = q.front();
        q.pop();

        for (auto [v, w]: E[u]) {
            dp[v] = max(dp[v], dp[u] + w);
            indeg[v]--;
            if (!indeg[v]) {
                q.push(v);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        ans += sz[i] * dp[i];
    }

    print(ans);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}

```
### floyd
全源最短路，插点法

时间复杂度O(n^3)
```c++
void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
```

### Johnson
全源最短路径算法

时间复杂度 O(n * m * logm + n * m)

知乎链接：https://zhuanlan.zhihu.com/p/99802850
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
#define all x.begin(), x.end()
const int N = 3e5 + 10;
vector<PII> e[N];
int n, m; 
int dist[N];
int h[N], cnt[N];
int vis[N];
bool spfa(int s) {
    queue<int> q;
    for (int i = 1; i <= n; i++) h[i] = 1e9;
    q.push(s);
    h[s] = 0, vis[s] = 1;
    while (q.size()) {
        auto u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w]: e[u]) {
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1) return false;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return true;
}
void dij(int s) {
    priority_queue<PII, vector<PII>, greater<PII>> q;
    for (int i = 0; i <= n; i++) dist[i] = 1e9;
    memset(vis, 0, sizeof vis);
    dist[s] = 0;
    q.push({0, s});
    while (q.size()) {
        auto [_, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w]: e[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!vis[v]) q.push({dist[v], v});
            }
        }
    }
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        e[u].push_back({v, w});
    }

    for (int i = 1; i <= n; i++) {
        e[0].push_back({i, 0});
    }

    if (!spfa(0)) {
        cout << -1 << '\n';
        return ;
    }

    for (int i = 1; i <= n; i++) {
        for (auto &[v, w]: e[i]) {
            w += h[i] - h[v];
        }
    }
    for (int i = 1; i <= n; i++) {
        dij(i);
        int ans = 0;
        for (int j = 1; j <= n; j++) {
            if (dist[j] == 1e9) {
                ans += j * (1e9);//题目特定要求
            }
            else {
                ans += j * (dist[j] + h[j] - h[i]);//存在最短路
            }
        }
        cout << ans << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    // int t; cin >> t;
    // while (t--) 
        solve();

    return 0;
}
```

## kruskal最小生成树
时间复杂度 O(n * logn)
```c++
//并查集贪心
struct edge{
    int u, v, w;
    bool operator <(const edge &t) const{
        return w < t.w;
    }
}e[N];
int fa[N], ans, cnt;//ans为树的最小边权值和
bool kruskal() {
    sort(e, e + m);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) {
            int x = find(e[i].u);
            int y = find(e[i].v);
            if (x != y) {
                fa[x] = y;
                ans += e[i].w;
                cnt++;
            }
    }
    return cnt == n - 1;
}
```

## 换根dp
也叫二次扫描法。先处理以每个节点为根节点的f。显然， 最终要求的并不是只包括子节点，还包括父节点。但是在第一次dfs中我们可以知道  ans[1] = f[1] 
我们可以再次dfs2， 从u节点的答案转换到v节点

题目链接：https://www.luogu.com.cn/problem/P1364
```c++


#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const int N = 110;
int w[N];
vector<int> e[N];

int s[N];
int f[N];
void dfs(int u, int fa) {
	s[u] = w[u];
	for(auto v: e[u]) {
		if (v == fa) continue;
		dfs(v, u);
		s[u] += s[v];
		f[u] += f[v] + s[v];
	}
}

int ans[N];
void dfs2(int u, int fa) {
	for (auto v: e[u]) {
		if (v == fa) continue;
		ans[v] = ans[u] - f[v] - s[v] + f[v] + s[1] - s[v];
		dfs2(v, u);
	}
}

signed main() {
	//freopen("in.txt", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		int a, b; cin >> a >> b;
		if (a) {
			e[i].push_back(a);
			e[a].push_back(i);
		}
		if (b) {
			e[i].push_back(b);
			e[b].push_back(i);
		}
	}

	dfs(1, 0);

	ans[1] = f[1];
	dfs2(1, 0);
	int mi = 1e18;
	for (int i = 1; i <= n; i++)
		mi = min(mi, ans[i]);

	cout << mi << endl;
	return 0;
}
```



## kruskal重构树
时间复杂度 O(n * logn)
不妨设求最小生成树，Kruskal 重构树有如下性质：

重构树是一棵恰有 n 个叶子节点的完满二叉树，每个非叶子节点都恰有 2 个儿子，重构树的点数为  2 * n - 1

重构树的点权符合大根堆的性质。

原图中两点间所有简单路径的最大边权最小值，等于最小生成树上两点之间边权最大值，等于重构树上两点 LCA 的点权。

到点u的简单路径上最大边权最小值 ≤k的所有节点v均在重构树上的某棵子树内，且恰为该子树内的所有叶子节点。

题目链接：https://www.luogu.com.cn/problem/P1967
```C++

int n, m, q;
struct edge{
    int u, v, w;
    bool operator <(const edge &t) const{
        return w > t.w;
    }
}E[N];
int f[M];
int find(int x) {
    return x == f[x]? x : f[x] = find(f[x]);
}
vector<int> e[M];
int val[M];
void kruskal() {
    sort(E + 1, E + m + 1);
    for (int i = 1; i < 2 * n; i++) f[i] = i;//1 -- 2 * n - 1
    int idx = n;
    for (int i = 1; i <= m; i++) {
        int u = E[i].u, v = E[i].v, w = E[i].w;
        u = find(u), v = find(v);
        if (u == v) continue;
        val[++idx] = w;
        e[idx].push_back(u);
        e[idx].push_back(v);
        f[u] = f[v] = idx;
    }
}

int dep[N], fa[N][22];
int col[M], cols;
void dfs(int u, int father) {
    col[u] = cols;
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    for (int i = 1; i <= 20; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (auto &v: e[u]) {
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    }
    if (u == v) return u;
    for (int i = 20; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i], v = fa[v][i];
            }
    }
    return fa[u][0];
}
void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> E[i].u >> E[i].v >> E[i].w;
    }
    kruskal();
    for (int i = 1; i < 2 * n; i++) {
        if (f[i] == i) {
            ++cols;
            dfs(i, 0);
        }
    }
    while (q--) {
        int x, y; cin >> x >> y;
        if (col[x] != col[y]) cout << -1 << endl;
        else {
            int l = lca(x, y);
            cout << val[l] << endl;
        }
    }
}
```

## 最近公共祖先

### 倍增算法

```C++
const int N = 5e5 + 10;
vector<int> e[N];
int dep[N], fa[N][21];
void dfs(int u, int father) {
	dep[u] = dep[father] + 1;
	fa[u][0] = father;

	for (int i = 1; i <= 20; i++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}

	for (auto v: e[u]) {
		if (v == father) continue;
		dfs(v, u);
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);

	//跳到同一层
	for (int i = 20; i >= 0; i--) {
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	}

	if (x == y) return x;//同一层可能为同一节点

	//继续往上跳
	for (int i = 20; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	//在lca的下一层停下来
	return fa[x][0];
}

```

### Tarjan算法

```C++
#include<bits/stdc++.h>
using namespace std;

int n, m, root;
const int N = 5e5 + 10;
int fa[N];
int ans[N];
int find(int x) {
	return fa[x] == x? x: find(fa[x]);
}
vector<int> e[N];
vector<pair<int, int>> query[N];
int vis[N];
void tarjan(int u) {
	vis[u] = 1;
	for (auto v: e[u]) {
		if (vis[v]) continue;
		tarjan(v);
		fa[v] = u;
	}

	for (auto q: query[u]) {
		int v = q.first, i = q.second;
		if (vis[v]) ans[i] = find(v);
	}
}

int main() {
	//freopen("in.txt", "r", stdin);
	cin >> n >> m >> root;
	for (int i = 1; i <= n; i++) fa[i] = i;

	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		query[x].push_back({y, i});
		query[y].push_back({x, i});
	}

	tarjan(root);

	for (int i = 1; i <= m; i++) cout << ans[i] << endl;

	return 0;
}
```

### 树链剖分

```C++
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, m, root;

vector<int> e[N];
int fa[N], dep[N], son[N], sz[N];
int top[N];
void dfs1(int u, int father) {//预处理fa,dep,son
	fa[u] = father;
	dep[u] = dep[father] + 1;
	sz[u] = 1;
	for (auto v: e[u]) {
		if (v == father) continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if (sz[son[u]] < sz[v]) son[u] = v;
	}
}
void dfs2(int u, int t) {
	top[u] = t;
	if (!son[u]) return ;
	dfs2(son[u], t);
	for (auto v: e[u]) {
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y]? x: y;
}
int main() {
	//freopen("in.txt", "r", stdin);
	cin >> n >> m >> root;

	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(root, 0);
	dfs2(root, root);

	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		cout << lca(x, y) << endl;
	}

	return 0;
}
```



## 树上点前缀和
$dist(x, y) = s[x] + s[y] - s[lca] - s[fa[lca]] $

luogu P4427 [BJOI2018] 求和
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
const int N = 3e5 + 10;
int s[N][51];
vector<int> e[N];

const int p = 998244353;

int qmi(int a, int b) {
	int ans = 1;
	a %= p;
	while (b) {
		if (b & 1) ans = ans * a % p;
		b >>= 1;
		a = a * a % p;
	}

	return ans;
}

int dep[N], fa[N][21];
void dfs(int u, int father) {
	dep[u] = dep[father] + 1;
	for (int k = 1; k <= 50; k++) {
		int t = qmi(dep[u], k);
		s[u][k] = (s[father][k]  + t % p) % p;
	}

	fa[u][0] = father;
	for (int i = 1; i <= 20; i++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (auto v: e[u]) {
		if (v == father) continue;
		dfs(v, u);
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);

	for (int i = 20; i >= 0; i--) {
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	}

	if (x == y) return x;

	for (int i = 20; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}
signed main() { 
	//freopen("in.txt", "r", stdin);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}

	dep[0] = -1;
	dfs(1, 0);

	cin >> m;
	while (m--) {
		int x, y, k; cin >> x >> y >> k;
		int l = lca(x, y);
		int ans = (s[x][k] + s[y][k] - s[l][k] - s[fa[l][0]][k] + 2 * p) % p;
		cout << ans << endl;
	}

	return 0;
}
```

## 树上边前缀和
$dist(x, y) = s[x] + s[y] - 2 * s[lca] $

```c++
int s[N];
void dfs1(int u, int fa) {
    for (auto v: e[u]) {
        if (v == fa) continue;
        s[v] = s[u] + w[v];
        dfs1(v, u);
    }
}
```

## 树上点差分
$(x, y) 上的点+1: diff[x] + 1, diff[y] + 1, diff[lca] - 1,diff[fa[lca]] - 1$
```c++

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
const int N = 5e4 + 10;
vector<int> e[N];
int diff[N];
int dep[N], fa[N][21];
void dfs(int u, int father) {
	dep[u] = dep[father] + 1;
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}

	for (auto v: e[u]) {
		if (v == father) continue;
		dfs(v, u); 
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);

	for (int i = 20; i >= 0; i--) {
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	}
	if (x == y) return x;

	for (int i = 20; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int a[N];
void dfs1(int u, int father) {
	for (auto v: e[u]) {
		if (v == father) continue;
		dfs1(v, u);
		diff[u] += diff[v];
	}
	a[u] += diff[u];
}
signed main(){
	//freopen("in.txt", "r", stdin);
	cin >> n >> m; 
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);

	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		int l = lca(x, y);
		diff[x]++, diff[y]++, diff[l]--, diff[fa[l][0]]--;
	}

	dfs1(1, 0);
	int mx = -1e18;
	for (int i = 1; i <= n; i++) {
		mx = max(mx, a[i]);
	}
	cout << mx << endl;
	return 0;
}
```

## 树上边差分
首先我们需要一种叫做“边权转点权”的方法，就是对于每个点我们认为其点权代表这个点与其父节点之间的边的边权，

对于每条边我们认为其边权是这条边所连两个点中深度较大的点的点权，根节点点权无意义

$diff[x]++, diff[y]++, diff[lca] -= 2$
```c++

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
int n, m;
const int N = 1e5 + 10;
vector<int> e[N];
int diff[N];
int dep[N], f[N][22];
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; i--) {
        if (dep[f[x][i]] >= dep[y]) {
            x = f[x][i];
        }
    }
    if (x == y) return ;

    for (int i = 20; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

void dfs2(int u, int fa) {
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs2(v, u);
        diff[u] += diff[v];
    }
}
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    dfs(1, 0);
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y; cin >> x >> y;
        int lc = lca(x, y);
        diff[x]++, diff[y]++, diff[lc] -= 2;
    }
    dfs2(1, 0);
}

signed main(){
    solve();
	return 0;
}
```



## 拓扑排序

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10;
vector<int> e[N];
int deg[N];
signed main() {
	int n; cin >> n;
    //输入
	for (int i = 1; i <= n; i++) {
		int v; cin >> v;
		while (v) {
			e[i].push_back(v);
			deg[v]++;//入度++
			cin >> v;
		}
	}


	queue<int> q; 
	for (int i = 1; i <= n; i++) {
		if (!deg[i]) {
			q.push(i);
		}
	}

	vector<int> ans;//ans为拓扑序
	while (q.size()) {
		int u = q.front();
		q.pop();
		ans.push_back(u);
		for (auto v: e[u]) {
			deg[v]--;
			if (!deg[v]) q.push(v);
		}
	}

	for (auto x: ans) cout << x << ' ';
    cout << '\n';

	return 0;
}

```

## 欧拉路径（Hierholzer算法）
如何判断一个图是否有欧拉路径呢？显然，与一笔画问题相同，一个图有欧拉路径需要以下几个条件：

首先，这是一个连通图

若是无向图，则这个图的度数为奇数的点的个数必须是0或2；若是有向图，则要么所有点的入度和出度相等，
要么有且只有两个点的入度分别比出度大1和少1

上面这两个条件很好证明。查找欧拉路径前，必须先保证该图满足以上两个条件，否则直接判误即可。

查找欧拉路径的算法有Fluery算法和Hierholzer算法。下面介绍一下Hierholzer算法。

从起点开始，每一次执行递归函数，相当于模拟一笔画的过程。递归的边界显然就是路径的终点，对于一个有欧拉路径的图，此时图上的所有边都已被删除，自然就不能继续递归。由于存储答案是在遍历以后进行的，答案存储也就是倒序的，因此要倒序输出答案。

在下面的代码中，找出的是起点字典序最小的欧拉路径，具体情况应视题意而定。
```C++
#include <iostream>
#include <stack>
using namespace std;
const int N = 500;
int n, tot, c = N, jp[N], cnt[N], edge[N][N];
char a, b;
stack<int> q;
void dfs(int now) {
    for (int i = 1; i <= N; i++)
        if (edge[now][i] == 1) {
            edge[now][i]--, edge[i][now]--;
            dfs(i);
        }
    q.push(now); // 加入答案队列
} // 算法过程
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        c = min(c, a);
        c = min(c, b);
        edge[a][b]++，edge[b][a]++;
        cnt[a]++;
        cnt[b]++; // 统计每个节点的度数
    }
    for (int i = 1; i <= N; i++)
        if (cnt[i] % 2 == 1)
            jp[tot++] = i; // 找出度数为奇数的节点
    if (tot != 2 && tot) {
        cout << "No Solution";
        return 0;
    } // 若该图没有欧拉路径则判误
    int stat;
    if (tot)
        stat = min(jp[0], jp[1]);
    else
        stat = c; // 找出起点
    dfs(stat);
    while (!q.empty()) {
        char ct = q.top();
        cout << ct;
        q.pop();
    } // 倒序输出
    return 0;
}
```

## Tarjan

### 强连通分量(SCC)
强连通的定义是：有向图 G 强连通是指，G 中任意两个结点连通。

强连通分量（Strongly Connected Components，SCC）的定义是：极大的强连通子图。(极大不是最大)

low: 能够回溯到的最早的已经在栈中的结点
```C++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
vector<int> e[N];
int dfn[N], low[N], tot;
int stk[N], instk[N], top;
int scc[N], sz[N], cnt;
void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    stk[++top] = x, instk[x] = 1;
    for (auto y: e[x]) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (instk[y]) {
            low[x] = min(low[x], low[y]);
        }
    }
    if (dfn[x] == low[x]) {
        int y;
        cnt++;
        do {
            y = stk[top--];
            instk[y] = 0;
            scc[y] = cnt;
            sz[cnt]++;
        }while (y != x);
    }
}
```

### SCC缩点
缩点：把一个强连通分量缩成一个点
```C++
void solve() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    for (int x = 1; x <= n; x++) {
        for (auto y: e[x]) {
            if (scc[x] != scc[y]) {
                E[x].push_back(y); //x -> y
            }
        }
    }
}
```

### 割点
相关阅读：双连通分量

注意，强连通分量是有向图，双连通分量是无向图

对于一个无向图，如果把一个点删除后这个图的极大连通分量数增加了，那么这个点就是这个图的割点（又称割顶）。

low: 不经过其父亲能到达的最小的时间戳
```C++
#include <bits/stdc++.h>
using namespace std;
int n, m; // n：点数 m：边数
int dfn[100001], low[100001], inde, res;
// dfn：记录每个点的时间戳
// low：能不经过父亲到达最小的编号，inde：时间戳，res：答案数量
bool vis[100001], flag[100001]; // flag: 答案 vis：标记是否重复
vector<int> edge[100001];       // 存图用的

void Tarjan(int u, int father) { // u 当前点的编号，father 自己爸爸的编号
    vis[u] = true;               // 标记
    low[u] = dfn[u] = ++inde; // 打上时间戳
    int child = 0;            // 每一个点儿子数量
    for (auto v : edge[u]) {  // 访问这个点的所有邻居 （C++11）
        if (!vis[v]) {
            child++;                      // 多了一个儿子
            Tarjan(v, u);                 // 继续
            low[u] = min(low[u], low[v]); // 更新能到的最小节点编号
            if (father != u && low[v] >= dfn[u] && !flag[u]) { // 主要代码
                // 如果不是自己，且不通过父亲返回的最小点符合割点的要求，并且没有被标记过
                // 要求即为：删了父亲连不上去了，即为最多连到父亲
                flag[u] = true;
                res++; // 记录答案
            }
        } else if (v != father) {
            // 如果这个点不是自己的父亲，更新能到的最小节点编号
            low[u] = min(low[u], dfn[v]);
        }
    }
    // 主要代码，自己的话需要 2 个儿子才可以
    if (father == u && child >= 2 && !flag[u]) {
        flag[u] = true;
        res++; // 记录答案
    }
}

int main() {
    cin >> n >> m;                 // 读入数据
    for (int i = 1; i <= m; i++) { // 注意点是从 1 开始的
        int x, y;
        cin >> x >> y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    } // 使用 vector 存图
    for (int i = 1; i <= n; i++) // 因为 Tarjan 图不一定连通
        if (!vis[i]) {
            inde = 0;     // 时间戳初始为 0
            Tarjan(i, i); // 从第 i 个点开始，父亲为自己
        }
    cout << res << endl;
    for (int i = 1; i <= n; i++)
        if (flag[i])
            cout << i << " "; // 输出结果
    return 0;
}
```

### 割边(桥)
和割点差不多，只要改一处: low[v] > dfn[u]即可，而且不需要考虑根节点的问题

low: 不经过其父亲能到达的最小的时间戳
```C++
int low[MAXN], dfn[MAXN], dfs_clock;
bool isbridge[MAXN];
vector<int> G[MAXN];
int cnt_bridge;
int father[MAXN];

void tarjan(int u, int fa) {
    father[u] = fa;
    low[u] = dfn[u] = ++dfs_clock;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                isbridge[v] = true;
                ++cnt_bridge;
            }
        } else if (dfn[v] < dfn[u] && v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
```

### eDCC缩点
边双连通分量，指的是原图中一个极大的连通子图（该子图没有桥）
```C++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
const int M = N << 1;
struct edge{
    int v, ne;
}e[M];
int h[N], idx = 1;
int dfn[N], low[N], tot;
stack<int> stk;
int dcc[N], cnt;
int bri[M], d[N];
void add(int a, int b) {
    e[++idx].v = b;
    e[idx].ne = h[a];
    h[a] = idx;
}
void tarjan(int x, int in_edg){
    dfn[x] = low[x] = ++tot;
    stk.push(x);
    for (int i = h[x]; i; i = e[i].ne) {
        int y = e[i].v;
        if (!dfn[y]) {
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if (low[y] > dfn[x]) {
                bri[i] = bri[i ^ 1] = 1;
            }
        }
        else if (i != (in_edg ^ 1)) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (dfn[x] == low[x]) {
        cnt++;
        while (true) {
            int y = stk.top();
            stk.pop();
            dcc[y] = cnt;
            if (y == x) break;
        }
    }
}
void solve() {
    tarjan(1, 0);
    for (int i = 2; i <= idx; i++) {
        if (bri[i]) d[e[i].v]++;
    }
}
```

### vDCC缩点
点双连通分量：边双连通分量，指的是原图中一个极大的连通子图（该子图没有割点）
```C++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
const int M = N << 1;
vector<int> e[N], ne[N];
int dfn[N], low[N], tot;
stack<int> stk;
vector<int> dcc[N];
int cut[N], root, cnt, num, id[N];
void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    stk.push(x);
    if (!e[x].size()) {
        dcc[++cnt].push_back(x);
        stk.pop();
        return ;
    }
    int child = 0;
    for (auto y: e[x]) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if (low[y] >= dfn[x]) {
                child++;
                if (x != root || child > 1) {
                    cut[x] = 1;
                }
                cnt++;
                while (true) {
                    int z = stk.top();
                    stk.pop();
                    dcc[cnt].push_back(z);
                    if (z == y) break;
                }
            }
        }
        else {
            low[x] = min(low[x], dfn[y]);
        }
    }
}

void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    for (root = 1; root <= n; root++) {
        if (!dfn[root]) tarjan(root);
    }

    num = cnt;
    for (int i = 1; i <= n; i++) {
        if (cut[i]) id[i] = ++num;
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = 0; j < dcc[i].size(); j++) {
            int x = dcc[i][j];
            if (cut[x]) {
                ne[i].push_back(id[x]);
                ne[id[x]].push_back(i);
            }
        }
    }
}
```



## 树的直径

### 两次bfs求树的直径

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	//freopen("in.txt", "r", stdin);
	int n; cin >> n;
	vector<vector<int>> e(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	auto bfs = [&](int st) -> vector<int> {
		vector<int> dist(n + 1, -1ll);
		queue<int> q;
		q.push(st);
		dist[st] = 0;
		while (q.size()) {
			int u = q.front();
			q.pop();
			for (auto v: e[u]) {
				if (dist[v] != -1) continue;
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
		return dist;
	};

	int st = 1;
	vector<int> dist;
	auto func = [&]() -> void {
		dist = bfs(st);
		for (int i = 1; i <= n; i++) {
			if (dist[i] > dist[st]) st = i;
		}
	};

	func();
	func();

	cout << dist[st] << endl;

	return 0;
}
```

### 树形dp求树的直径
$我们定义 dp[u]：以 u 为根的子树中，从 u 出发的最长路径。那么容易得出转移方程： $dp[u] = max(dp[u], dp[v] + w(u, v)) $

其中的v为的子节点， w(u, v)表示所经过边的权重

树形$ dp $可以在存在负权边的情况下求解出树的直径

对于树的直径，实际上是可以通过枚举从某个节点出发不同的两条路径相加的最大值求出。

因此，在 DP 求解的过程中，我们只需要在更新 dp[u] 之前，计算 d = max(d, dp[u] + dp[v] + w(u, v)) 即可算出直径 d 

```C++
const int N = 1e6 + 10;
vector<int> e[N];
int f[N];
int d;
void dfs(int u, int fa) {
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        d = max(d, f[u] + f[v] + 1);
        f[u] = max(f[u], f[v] + 1);
    }
}
void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);

    cout << d << '\n';
}
```

### 树的直径性质
树上的一点到任意一点的最远距离是直径的两个端点之一
题目链接：https://ac.nowcoder.com/acm/contest/91279/H
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void ewrite(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;
struct edge {
    int v, w;
};
vector<edge> e[M];

void dfs(int u, int fa, int dist[]) {
    for (auto [v, w]: e[u]) {
        if (v == fa) continue;
        dist[v] = dist[u] + w;
        dfs(v, u, dist);
    }
}

int dist[N];
int distl[N];
int distr[N];

void solve() {
    int n = read();
    for (int i = 1; i < n; i++) {
        int u, v, c;
        u = read(), v = read(), c = read();
        e[u].push_back({v, c});
        e[v].push_back({u, c});
    }
    for (int i = 1; i <= n; i++) {
        int d = read();
        e[i].push_back({i + n, d});
        e[i + n].push_back({i, d});
    }

    dfs(1, 0, dist);
    int l = max_element(dist + 1, dist + 1 + 2 * n) - dist;
    dfs(l, 0, distl);
    int r = max_element(distl + 1, distl + 1 + 2 * n) - distl;
    dfs(r, 0, distr);

    for (int i = 1; i <= n; i++) {
        if (i + n == l) {
            write(distr[i]);
        }
        else if (i + n == r) {
            write(distl[i]);
        }
        else {
            write(max(distl[i], distr[i]));
        }
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
    solve();

    return 0;
}
```



## 树上启发式合并

### 理论

对于节点u来说
1、先遍历u的轻儿子(非重儿子)，先计算轻儿子答案，然后再清除其对cnt数组的贡献。
2、遍历重儿子，计算答案，不必消除其对cnt数组的贡献(可以用一个变量标记其是否为重儿子）。
3、再次遍历u的轻儿子的子树结点，将这些结点的贡献与重儿子的贡献合并，以得到u的答案

最后，树上启发式合并有两种：
1、树链剖分。对原树进行重链剖分，直觉上，每次保留重子节点的信息，重新计算其他轻节点的信息可以优化时间复杂度；事实上，由重链剖分的结论可知，任意节点走到根节点最多经过 O($logn$) 条轻边。所以总的时间复杂度为 O($nlogn$)。 
2、按秩合并。对于每个节点，用一个map存储其子树内信息。通过深度优先搜索合并集合（深度大的子树计算完后信息就无用了，若集合大可以 $swap$到父节点）。每次合并集合大小会翻倍，所以合并插入的次数是  O($nlogn$)，总的时间复杂度是O($n * (logn)^2$)。

### 树链剖分
例题： https://www.lanqiao.cn/problems/5892/learning/
```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
using PII = pair<int, int>;

const int N = 1e5 + 10;
int ans[N];
int a[N];
vector<PII> qs[N];
vector<int> e[N];

int sz[N], son[N], dep[N];
void dfs(int u, int fa) {
    sz[u] = 1;
    dep[u] = dep[fa] + 1;
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

priority_queue<PII> q[N];
int vis[N];
int Son;
void add(int u, int fa) {
    vis[u] = 1;
    q[dep[u]].push({a[u], u});
    for (auto v: e[u]) {
        if (v == fa || v == Son) continue;
        add(v, u);
    }
}

void del(int u, int fa) {
    vis[u] = 0;
    for (auto v: e[u]) {
        if (v == fa) continue;
        del(v, u);
    }
}


void dfs2(int u, int fa, int op) {
    for (auto v: e[u]) {
        if (v == fa || v == son[u]) continue;
        dfs2(v, u, 0);
    }
    
    if (son[u]) {
        dfs2(son[u], u, 1);
        Son = son[u];
    }

    add(u, fa);

    for (auto p: qs[u]) {
        int k = p.first, i = p.second;
        int d = dep[u] + k;
        while (q[d].size() && !vis[q[d].top().second]) {
            q[d].pop();
        }

        ans[i] = q[d].top().first;
    }
    if (!op) {
        del(u, fa);
        Son = 0;
    }
}
signed main() {
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    for (int i = 0; i < q; i++) {
        int x, k; cin >> x >> k;
        qs[x].push_back({k, i});
    }

    dfs(1, 0);
    dfs2(1, 0, 0);

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';

    return 0;
}

```

### 按秩合并
例题：https://atcoder.jp/contests/abc359/tasks/abc359_g
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
const int N = 2e5 + 10;
int a[N];
vector<int> e[N];
int ans;
int cnt[N];
int sum[N];
vector<map<int, int>> mp(N);
void dfs(int u, int fa) {
	map<int, int> cc;
	int res = 0;
	for (auto v: e[u]) {
		if (v == fa) continue;
		dfs(v, u);
		if (mp[v].size() > cc.size()) {
			cc.swap(mp[v]);
			swap(res, sum[v]);
		}
		for (auto [k, t]: mp[v]) {
			res -= cc[k] * (cnt[k] - cc[k]);
			cc[k] += t;
			res += cc[k] * (cnt[k] - cc[k]);
		}	
		mp[v].clear();
	}

	res -= cc[a[u]] * (cnt[a[u]] - cc[a[u]]);
	cc[a[u]]++;
	res += cc[a[u]] * (cnt[a[u]] - cc[a[u]]);
	mp[u].swap(cc);
	ans += res;
	sum[u] = res;
}
void solve() {
	int n; cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}

	dfs(1, 0);

	cout << ans;
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	// int t; cin >> t;
	// while (t--) 
		solve();

	return 0;
}
```

## 虚树
虚树的主要思想是：对于一棵树，仅仅保留有用的点，重新构建一棵树

这里有用的点指的是询问点和它们的lca

题目链接：https://atcoder.jp/contests/abc359/tasks/abc359_g
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
#define all x.begin(), x.end()

const int N = 1e6 + 10;
vector<int> e[N];
set<int> s[N];
int dfn[N], dep[N], f[N][22];
int cnt;
void dfs(int u, int fa) {
    dfn[u] = ++cnt;
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (auto v: e[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; i--) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 20; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int sum(int x, int y) {
    int lc = lca(x, y);
    int ans = dep[x] + dep[y] - 2 * dep[lc];
    return ans;
}


int vis[N];
bool cmp(int x, int y) {
    return dfn[x] < dfn[y];
}
int poi[N];
vector<PII> ee[N];
int top, stk[N];
void build_VrTree(int m) {
    top = 1, stk[1] = 1;
    ee[1].clear();
    for (int i = 1; i <= m; i++) {
        if (poi[i] == 1) continue;
        int lc = lca(poi[i], stk[top]);
        if (lc != stk[top]) {
            while (dfn[stk[top - 1]] > dfn[lc]) {
                ee[stk[top - 1]].push_back({stk[top], sum(stk[top - 1], stk[top])});
                top--;
            }
            if (lc != stk[top - 1]) {
                ee[lc].clear();
                ee[lc].push_back({stk[top], sum(lc, stk[top])});
                stk[top] = lc;
            }
            else {
                ee[lc].push_back({stk[top], sum(lc, stk[top])});
                top--;
            }
        }
        ee[poi[i]].clear();
        stk[++top] = poi[i];
    }
    for (int i = 1; i < top; i++) ee[stk[i]].push_back({stk[i + 1], sum(stk[i], stk[i + 1])});
}

int ans;
int g[N], sz[N];
int dp[N];
int pre[N];
void dfs2(int u) {
    g[u] = sz[u] = 0;
    for (auto [v, w]: ee[u]) {
        pre[v] = pre[u] + w;
        dfs2(v);
        g[u] += g[v];
        sz[u] += sz[v];
    }
    if (vis[u]) {
        g[u] += pre[u];
        sz[u]++;
    }
}
int m;
void dfs3(int u) {
    for (auto [v, w]: ee[u]) {
        dp[v] = g[v] - sz[v] * pre[v] + dp[u] - (g[v] - sz[v] * pre[u]) + (m - sz[v]) * w;
        dfs3(v);
    }
}
 
void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        s[x].insert(i);
    }

    dfs(1, 0);
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        if (s[i].size() < 2) continue;
        m = 0;
        for (auto x: s[i]) {
            vis[x] = 1;
            poi[++m] = x;
        }
        sort(poi + 1, poi + 1 + m, cmp);
        build_VrTree(m);
        dfs2(1);
        dp[1] = g[1];
        dfs3(1);
        int t = 0;
        for (int i = 1; i <= m; i++) {
            //cout << poi[i] << ' ' << dp[poi[i]] << '\n';
            t += dp[poi[i]];
        }
        //cout << '\n';
        ans += t / 2;
        for (auto x: s[i]) {
            vis[x] = 0;
        }
    }
    cout << ans;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    // int t; cin >> t;
    // while (t--) 
        solve();

    return 0;
}
```

## 树上倍增
2024河北省赛H题：https://codeforces.com/group/mey3UXMrvB/contest/540698/attachments
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {int c; cin >> c; return c;}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) {cin >> x;});
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template<typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template<typename T, typename... Args>
void ewrite(const T& first, const Args&... args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"No", "Yes"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 1e9 + 7;

/* next is main_solve */

vector<int> e[N];
int dp[N];
int vis[N];

const int lgmx = 20;
int dep[N], fa[N][21];
int mi1[N][21];
int mi2[N][21];
void dfs(int u, int father) {
    dep[u] = dep[father] + 1;

    fa[u][0] = father;
    mi1[u][0] = 3 * dp[u] - dep[u];
    mi2[u][0] = 3 * dp[u] + dep[u];

    for (int i = 1; i <= lgmx; i++) {
        int v = fa[u][i - 1];
        fa[u][i] = fa[v][i - 1];
        mi1[u][i] = min(mi1[u][i - 1], mi1[v][i - 1]);
        mi2[u][i] = min(mi2[u][i - 1], mi2[v][i - 1]);
    }

    for (auto v: e[u]) {
        if (v == father) continue;
        dfs(v, u);
    }
}

int lca(int u, int v){
    if (dep[u] < dep[v])
        swap(u, v);
    for (int k = dep[u] - dep[v], lg; k; k -= 1 << lg) {
        lg = __lg(k);
        u = fa[u][lg];
    }
    if(u == v)
        return u;

    for(int k = __lg(dep[u]); k >= 0; k--) {
        if (fa[u][k] != fa[v][k])
            u = fa[u][k], v = fa[v][k];
    }
    return fa[u][0];
}

int ask1(int u, int v) {
    int ans = 1e18;
    for (int k = dep[u] - dep[v] + 1, lg; k; k -= 1 << lg) {
        lg = __lg(k);
        ans = min(ans, mi1[u][lg]);
        u = fa[u][lg];
    }
    return ans;
}

int ask2(int u, int v) {
    int ans = 1e18;
    for (int k = dep[u] - dep[v] + 1, lg; k; k -= 1 << lg) {
        lg = __lg(k);
        ans = min(ans, mi2[u][lg]);
        u = fa[u][lg];
    }
    return ans;
}

void solve() {
    int n, k;
    n = read(), k = read();
    for (int i = 1; i < n; i++) {
        int u, v;
        u = read(), v = read();
        e[u].push_back(v);
        e[v].push_back(u);
    }

    queue<int> q;
    for (int i = 1; i <= k; i++) {
        int v; 
        v = read();
        q.push(v);
        vis[v] = 1;
    }

    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (auto v: e[u]) {
            if (vis[v]) continue;
            dp[v] = dp[u] + 1;
            vis[v] = 1;
            q.push(v);
        }
    }

    dfs(1, 0);
    int Q;
    Q = read();
    while (Q--) {
        int x, y;
        x = read(), y = read();
        int lc = lca(x, y);

        int ans = 2 * (dep[x] + dep[y] - 2 * dep[lc]);
        //ewrite(ans);
        ans = min(ans, ask1(x, lc) + 2 * dep[x] + dep[y] - 2 * dep[lc]);
        //ewrite(ans);
        ans = min(ans, ask2(y, lc) + 2 * dep[x] + dep[y] - 4 * dep[lc]);
        //ewrite(ans);
        write(ans);
    }
}
void cloud_fly() {
    // int t;
    // cin >> t;
    // while (t--)
        solve();
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cloud_fly();
    return 0;
}
```

## 高级图论

### 最大流(EK算法)
在一个有向图G=(V,E)中：

有一个唯一的源点S， 有一个唯一的汇点T

图中的每一条边都一个非负的权值，这个权值叫做容量c(u,v)， 用f(u, v)表示u->v的流量。

最大流问题： 求满足流量小于等于容量的, 从源点流向汇点的最大流量

时间复杂度 O($n \cdot m^2$)
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void ewrite(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

struct edge {
    int v, w, ne;
}e[M];
int h[N], tot = 1;
int mf[N], pre[N];
int n, m, s, t;
void add(int u, int v, int w) {
    e[++tot] = {v, w, h[u]};
    h[u] = tot;
}

bool bfs() {
    for (int i = 1; i <= n; i++) {
        mf[i] = 0;
    }
    queue<int> q;
    q.push(s);
    mf[s] = 1e18;
    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].ne) {
            int v = e[i].v;
            if (!mf[v] && e[i].w) {
                mf[v] = min(mf[u], e[i].w);
                pre[v] = i;
                q.push(v);
                if (v == t) return true;
            }
        }
    }
    return false;
}

int EK() {
    int flow = 0;
    while (bfs()) {
        int v = t;
        while (v != s) {
            int i = pre[v];
            e[i].w -= mf[t];
            e[i ^ 1].w += mf[t];
            v = e[i ^ 1].v;
        }
        flow += mf[t];
    }
    return flow;
}

void solve() {
    n = read(), m = read(), s = read(), t = read();
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        u = read(), v = read(), w = read();
        add(u, v, w);
        add(v, u, 0);
    }
    int ans = EK();
    write(ans);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T;
    // T = read();
    // while (T--)
    solve();

    return 0;
}
```

### 最大流(Dinic算法)
时间复杂度O($n^2 \cdot m$)
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void ewrite(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

struct edge{
    int v, w, ne;
}e[M];
int h[N];
int tot = 1;
int dep[N], cur[N];
int n, m, s, t;
void add(int u, int v, int w) {
    e[++tot] = {v, w, h[u]};
    h[u] = tot;
}

bool bfs() {
    for (int i = 1; i <= n; i++) dep[i] = 0;
    queue<int> q;
    q.push(s);
    dep[s] = 1;
    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].ne) {
            int v = e[i].v;
            if (!dep[v] && e[i].w) {
                dep[v] = dep[u] + 1;
                q.push(v);
                if (v == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int mf) {
    if (u == t) return mf;
    int sum = 0;
    for (int i = cur[u]; i; i = e[i].ne) {
        cur[u] = i;
        int v = e[i].v;
        if (dep[v] == dep[u] + 1 && e[i].w) {
            int f = dfs(v, min(mf, e[i].w));
            e[i].w -= f;
            e[i ^ 1].w += f;
            sum += f;
            mf -= f;
            if (!mf) break;
        }
    }
    if (!sum) dep[u] = 0;
    return sum;
}

int dinic() {
    int flow = 0;
    while (bfs()) {
        for (int i = 1; i <= tot; i++) cur[i] = h[i];
        flow += dfs(s, 1e18); 
    }
    return flow;
}

void solve() {
    n = read(), m = read(), s = read(), t = read();
        for (int i = 1; i <= m; i++) {
        int u, v, w;
        u = read(), v = read(), w = read();
        add(u, v, w);
        add(v, u, 0);
    }
    int ans = dinic();
    write(ans);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T;
    // T = read();
    // while (T--)
    solve();

    return 0;
}
```

### 最小割(Dinic算法)
最大流 = 最小割

求最小割的最小边数：
第一遍dinic后，重建边时应当把第一遍dinic中剩余容量为0的正向边的边权设为1，其他正向边设为无穷大，反向边都设为零，因为只有流满的边才是最小割中的边。
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void ewrite(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

struct edge{
    int v, w, ne;
}e[M];
int h[N];
int tot = 1;
int dep[N], cur[N];
int n, m, s, t;
void add(int u, int v, int w) {
    e[++tot] = {v, w, h[u]};
    h[u] = tot;
}

bool bfs() {
    for (int i = 1; i <= n; i++) dep[i] = 0;
    queue<int> q;
    q.push(s);
    dep[s] = 1;
    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].ne) {
            int v = e[i].v;
            if (!dep[v] && e[i].w) {
                dep[v] = dep[u] + 1;
                q.push(v);
                if (v == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int mf) {
    if (u == t) return mf;
    int sum = 0;
    for (int i = cur[u]; i; i = e[i].ne) {
        cur[u] = i;
        int v = e[i].v;
        if (dep[v] == dep[u] + 1 && e[i].w) {
            int f = dfs(v, min(mf, e[i].w));
            e[i].w -= f;
            e[i ^ 1].w += f;
            sum += f;
            mf -= f;
            if (!mf) break;
        }
    }
    if (!sum) dep[u] = 0;
    return sum;
}

int dinic() {
    int flow = 0;
    while (bfs()) {
        for (int i = 1; i <= tot; i++) cur[i] = h[i];
        flow += dfs(s, 1e18); 
    }
    return flow;
}

int vis[N];

//求最小割划分
void micut(int u) {
    vis[u] = 1;
    for (int i = h[u]; i; i = e[i].ne) {
        int v = e[i].v;
        if (!vis[v] && e[i].w) micut(v);
    }
}

void solve() {
    n = read(), m = read(), s = 1, t = n;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        u = read(), v = read(), w = read();
        add(u, v, w);
        add(v, u, 0);
    }
    int ans1 = 0, ans2 = 0;
    ans1 = dinic();

    for (int i = 1; i <= tot; i++) {
        if (i % 2 == 0) {
            e[i].w = e[i].w > 0 ? 1e18 : 1;
        }
        else {
            e[i].w = 0;
        }
    }
    ans2 = dinic();
    write(ans1, ans2);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T;
    // T = read();
    // while (T--)
    solve();

    return 0;
}
```

### 费用流(EK算法)
即最小费用最大流
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

// inline int read() {
//     register int x = 0, t = 1;
//     register char ch = getchar();
//     while (ch < '0'|| ch > '9'){
//         if (ch == '-')
//             t = -1;
//         ch = getchar();
//     }
//     while (ch >= '0' && ch <= '9'){
//         x = (x << 1) + (x << 3) + (ch ^ 48);
//         ch = getchar();
//     }
//     return x * t;
// }

// void print128(__int128 x) {
//     if (x < 0)
//         putchar('-'), x = -x;
//     if (x > 9)
//         print128(x / 10);
//     putchar(x % 10 + '0');
// }

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;

const int N = 5010, M = 100010;

int n, m, S, T;

struct edge {
    int v, c, w, ne;
} e[M];

int h[N], idx = 1; // 从2,3开始配对
int d[N], mf[N], pre[N], vis[N];
int flow, cost;

void add(int a, int b, int c, int d) {
    e[++idx] = {b, c, d, h[a]};
    h[a] = idx;
}

bool spfa() {
    for (int i = 1; i <= n; i++) {
      d[i] = inf;
      mf[i] = 0;
    }
    queue<int> q;
    q.push(S);
    d[S] = 0, mf[S] = inf, vis[S] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = h[u]; i; i = e[i].ne) {
            int v = e[i].v, c = e[i].c, w = e[i].w;
            if (d[v] > d[u] + w && c) {
                d[v] = d[u] + w; // 最短路
                pre[v] = i;
                mf[v] = min(mf[u], c);
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return mf[T] > 0;
}
void EK() {
    while (spfa()) {
        for (int v = T; v != S;) {
            int i = pre[v];
            e[i].c -= mf[T];
            e[i ^ 1].c += mf[T];
            v = e[i ^ 1].v;
        }
        flow += mf[T];        // 累加可行流
        cost += mf[T] * d[T]; // 累加费用
    }
}
void solve() {
    n = read(), m = read(), S = read(), T = read();
    while (m--) {
        int a = read(), b = read(), c = read(), d = read();
        add(a, b, c, d);
        add(b, a, 0, -d);
    }
    EK();
    print(flow, cost);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
    solve();

    return 0;
}
```

### 二分图判定（染色法）
时间复杂度 O($n$)

该算法可以用来判断一个图是不是二分图以及是否含有奇环

题目链接: https://codeforces.com/contest/1991/problem/E
```C++

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
// #define endl '\n'
inline int read() {int c;cin>>c;return c;}
inline void readn(int a[], int n){
    for_each(a + 1, a + n + 1, [](int &x){cin>>x;});
}
inline void printn(int a[], int n){
    for_each(a + 1, a + n + 1, [](int &x){
        cout<<x<<' ';
    });
    cout<<endl;
}
template<typename T, typename... Args>
void write(const T& first, const Args&... args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
char out[2][10] = {"No", "Yes"};
const int N = 1e6 + 10;
/* next is main_solve */
int a[N];
vector<int> e[N];
int color[N];
int dfs(int x, int col, int fa) {
    color[x] = col;
    for (auto y : e[x]) {
        if (y == fa)
            continue;
        if (!color[y]) {
            if (dfs(y, 3 - col, x))
                return 1;
        } else {
            if (color[y] == col) {
                return 1;
            }
        }
    }
    return 0;//是二分图，即不存在奇数环
}

vector<int> sb[3];

void solve() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        e[i].clear();
        color[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    for (int i = 1; i <= 2; i++) sb[i].clear();

    if (dfs(1, 1, 0)) {
        cout << "Alice" << endl;
        for (int i = 1; i <= n; i++) {
            cout << 1 << ' ' << 2 << endl;
            read(), read();
        }
    }
    else {
        for (int i = 1; i <= n; i++) sb[color[i]].push_back(i);
        cout << "Bob" << endl;
        for (int i = 1; i <= n; i++) {
            int x = read(), y = read();
            if (x > y) swap(x, y);
            if (sb[1].size() && sb[2].size()) {
                if (x == 1) {
                    int v = sb[1].back();
                    sb[1].pop_back();
                    cout << v << ' ' << 1 << endl;
                }
                else {
                    int v = sb[2].back();
                    sb[2].pop_back();
                    cout << v << ' ' << 2 << endl;
                }
            }
            else {
                if (sb[1].size()) {
                    int v = sb[1].back();
                    sb[1].pop_back();
                    if (x == 2) cout << v << ' ' << y << endl;
                    else cout << v << ' ' << x << endl;
                }
                else {
                    int v = sb[2].back();
                    sb[2].pop_back();
                    if (x == 1) cout << v << ' ' << y << endl;
                    else cout << v << ' ' << x << endl;
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t; cin >> t;
    while (t--)
        solve();
    return 0;
}
```

# 数据结构

## 单调队列
如果一个选手比你小还比你强，你就可以退役了。”——单调队列

单调队列：擅长维护定长区间最大/最小值，最小值对应着递增队列，最大值对应着递减队列

例题：https://www.luogu.com.cn/problem/P1714
```C++

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
#define all x.begin(), x.end()
const int N = 1e6 + 10;
int a[N];
int s[N];
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        s[i] = s[i - 1] + x;
    }

    int ans = -1e18;
    deque<int> dq;
    dq.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (dq.size() && i - dq.front() > m) dq.pop_front();
        ans = max(ans, s[i] - s[dq.front()]);
        while (dq.size() && s[i] <= s[dq.back()]) dq.pop_back();
        dq.push_back(i);
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    // int t; cin >> t;
    // while (t--) 
        solve();

    return 0;
}
```

## 单调栈
栈是单调的

单调栈：：擅长维护最近大于/小于关系，从左侧先入栈就是维护左侧最近关系，从右侧先入栈就是维护右侧最近关系
```C++

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
#define all x.begin(), x.end()
const int N = 1e6 + 10;
int dp[N];
int h[N];
void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    h[0] = 1e9;
    vector<int> arr;
    arr.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (arr.size() && h[i] > h[arr.back()]) arr.pop_back();
        dp[i] = dp[arr.back()] + (i - arr.back()) * h[i];
        arr.push_back(i);
    }

    for (int i = 1; i <= n; i++) cout << dp[i] + 1 << ' ';
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    // int t; cin >> t;
    // while (t--) 
        solve();

    return 0;
}
```



## 并查集 

### 路径压缩

```c++
int fa[N];
int find(int x) {
	return fa[x] == x? x: fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) fa[x] = y;
}
```

### 按秩合并

```c++
int fa[N], rnk[N];
int find(int x) {
	while (fa[x] ^ x) x = fa[x];
	return x;
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		if (rnk[x] > rnk[y]) swap(x, y);
		fa[x] = y;
		if (rnk[x] == rnk[y]) rnk[y]++;
	}
}
```

### 启发式合并

```C++
int fa[N], sz[N];
int find(int x) {
	while (fa[x] ^ x) x = fa[x];
	return x;
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		if (sz[x] > sz[y]) swap(x, y);
		fa[x] = y;
		sz[y] += sz[x];
	}
}
```

## 字典树（前缀树）
例题：https://atcoder.jp/contests/abc353/tasks/abc353_e
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 10;
int cnt[N];
int tr[N][26];
int idx = 1;
void insert(string s, int k) {
    int p = 1;
    for (auto ch: s) {
        int x = ch - 'a';
        if (!tr[p][x]) tr[p][x] = ++idx;
        p = tr[p][x];
        cnt[p] += k;
    }
}

// int query(string str) {
//     int p = 1;
//     for (auto ch: str) {
//         int x = ch - 'a';
//         if (tr[p][x]) p = tr[p][x];
//         else return 0;
//     }
//     return cnt[p];
// }
void solve() {
    int n; cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        int p = 1;
        for (auto ch: s) {
            int x = ch - 'a';
            if (tr[p][x]) p = tr[p][x];
            else break;
            ans += cnt[p];
        }
        insert(s, 1);
    }
    cout << ans;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    // int t; cin >> t;
    // while (t--) 
        solve();

    return 0;
}
```

## ST表（静态RMQ问题）

```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {int c; cin >> c; return c;}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) {cin >> x;});
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template<typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template<typename T, typename... Args>
void ewrite(const T& first, const Args&... args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"No", "Yes"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 1e9 + 7;

/* next is main_solve */
int n, m;
int a[N];
const int lgmx = 20;
int mx[N][21];
void st() {
    for (int i = 1; i <= n; i++) {
        mx[i][0] = a[i];
    }

    for (int i = 1; i <= lgmx; i++) {
        for (int j = 1; j <= n; j++) {
            mx[j][i] = max(mx[j][i - 1], mx[j + (1 << (i - 1))][i - 1]);
        }
    }
}

int ask(int l, int r) {
    int ans = -1e18;
    for (int k = r - l + 1, lg; k; k -= 1 << lg) {
        lg = __lg(k);
        ans = max(ans, mx[l][lg]);
        l += 1 << lg;
    }
    return ans;
}

void solve() {
    n = read(), m = read();
    readn(a, n);

    st();

    while (m--) {
        int l, r;
        l = read(), r = read();
        cout << ask(l, r) << '\n';
    }
}
void cloud_fly() {
    // int t;
    // cin >> t;
    // while (t--)
        solve();
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cloud_fly();
    return 0;
}
```

## 分块
暴力加暴力

$len：每一个块的大小  tot：块的个数 l[i]：第i个块的的左端点  r[i]:第i个块的的右端点  belong[i]:每一个点属于的块$

$sum[i]:每一个块块内的前缀和  b[i]：第i个块的前缀和  add[i]:第i个块每个数增加的个数$
```C++
using ll = long long;
const int N = 5e5 + 10;
int n, m;
ll a[N];
int len, tot, l[N], r[N], belong[N];
ll sum[N], b[N], add[N];
void init() {
    len = (int)sqrt(n),tot = (n + len - 1) / len;
    for (int i = 1; i <= tot; i++) {
        l[i] = r[i - 1] + 1;
        r[i] = i * len;
    }
    r[tot] = n;
    for (int i = 1; i <= tot; i++) {
        for (int j = l[i]; j <= r[i]; j++) {
            belong[j] = i;
            sum[i] += a[j];
        }
        b[i] = b[i - 1] + sum[i];
    }
}

void modify(int k, int x) {//单点修改
    a[k] += x;
    sum[belong[k]] += x;
    for (int i = belong[k]; i <= tot; i++)
        b[i] += x;
}

void update(int L, int R, int x) {//区间修改
    int p = belong[L], q = belong[R];
    if (p == q) {
        for (int i = L; i <= R; i++)a[i] += x, sum[p] += x;
        for (int i = p; i <= tot; i++) b[i] = b[i - 1] + sum[i];
        return ;
    }
    for (int i = L; i <= r[p]; i++) a[i] += x, sum[p] += x;
    for (int i = p + 1; i <= q - 1; i++) add[i] += x, sum[i] += (ll)(r[i] - l[i] + 1) * x;
    for (int i = l[q]; i <= R; i++) a[i] += x, sum[q] += x;

    for (int i = p; i <= tot; i++) b[i] = b[i - 1] + sum[i];
}

ll query(int L, int R) {//区间查询
    int p = belong[L], q = belong[R];
    ll ans = 0;
    if (p == q) {
        for (int i = L; i <= R; i++) ans += a[i] + add[p];
        return ans;
    }
    ans = b[q - 1] - b[p + 1 - 1];
    for (int i = L; i <= r[p]; i++) ans += a[i] + add[p];
    for (int i = l[q]; i <= R; i++) ans += a[i] + add[q];
    return ans;
}
```

## 对顶堆（动态求第k大）
例题：https://codeforces.com/contest/1945/problem/F
```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
using i64 = long long;

const int N = 2e5 + 10;

int a[N];
int arr[N];
void solve(){
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        int p; cin >> p;
        arr[i] = a[p];
    }

    priority_queue<int> q1;
    priority_queue<int, vector<int>, greater<>> q2;
    int ans = 0, cnt = 0;
    for (int i = n; i >= 1; i--) {
        int x = arr[i];
        if (q2.empty() || x >= q2.top()) q2.push(x);
        else q1.push(x);
        if (n - i + 1 < i) continue;
        while (q2.size() > i) q1.push(q2.top()), q2.pop();
        while (q2.size() < i) q2.push(q1.top()), q1.pop();
        int sum = i * q2.top();
        if (sum >= ans) {
            ans = sum;
            cnt = i;
        }
    }
    cout << ans << ' ' << cnt << '\n';
}   

signed main() {
    IOS;
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    int T; cin >> T;
    while (T--)
        solve();

    return 0;
} 
```



## 树状数组
约瑟夫问题：树状数组解决

bit[i] 这个位置辖域是 [i - lowbit(i) + 1, i]

ans += 1ll<<i后，在树状数组上tr[ans]存储的是 ans-(1ll<<i)+1 到 ans 这长度为 (1ll<<i) 位置上的和
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void ewrite(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int N = 2e6 + 10;
const int M = N << 1;
const int mod = 1e9 + 7;

int a[N];
int tr[N];
int maxn;
int lowbit(int x) { return x & -x; }

void add(int x, int k) {
    for (int i = x; i < N; i += lowbit(i)) {
        tr[i] += k;
    }
}

int sum(int x) {
    int ans = 0;
    for (int i = x; i; i -= lowbit(i)) {
        ans += tr[i];
    }
    return ans;
}

int kth(int k) {
    int ans = 0, now = 0;
    for (int i = 20; i >= 0; i--) {
        ans += 1ll << i;
        if (ans > maxn || tr[ans] + now >= k)
            ans -= 1ll << i;
        else
            now += tr[ans];
    }
    return ans + 1;
}

void solve() {
    int n, k;
    n = read(), k = read();
    maxn = n;
    for (int i = 1; i <= n; i++) {
        add(i, 1);
    }

    int now = 1;
    while (n > 1) {
        now = (now + k - 2) % n + 1;
        int ans = kth(now);
        add(ans, -1);
        cout << ans << ' ';
        n--;
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T;
    // T = read();
    // while (T--)
    solve();

    return 0;
}
```

## 线段树

### 单点修改

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
const int inf = LONG_LONG_MAX;
using i64 = long long;

const int N = 1e6;
#define lc p << 1
#define rc p << 1 | 1
struct Tree {
    int l, r, mx;
}tr[N * 4];

void pushup(int p) {
    tr[p].mx = max(tr[lc].mx, tr[rc].mx);
}
void build(int p, int l, int r) {
    tr[p] = {l, r, 0ll};
    if (l == r) return ;
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}

int query(int p, int ql, int qr) {
    if (ql <= tr[p].l && qr >= tr[p].r) return tr[p].mx;
    if (ql > tr[p].r || qr < tr[p].l) return 0;
    return max(query(lc, ql, qr), query(rc, ql, qr)); 
}

void modify(int p, int x, int k) {
    if (tr[p].l == tr[p].r && tr[p].l == x) {
        tr[p].mx = k;
        return ;
    }
    if (x <= tr[lc].r) modify(lc, x, k);
    if (x >= tr[rc].l) modify(rc, x, k);
    pushup(p);
}

int dp[N];
void solve() {
    int n, d; cin >> n >> d;
    build(1, 0ll, 500000ll);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        int l = max(0ll, x - d), r = min(500000ll, x + d);
        int t = query(1, l, r);
        dp[x] = t + 1;
        modify(1, x, dp[x]);
    }

    int ans = 0;
    for (int i = 1; i <= 5e5; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
}

signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

#### 单点修改最大字段和

```C++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 10;
int a[N];
#define lc p << 1
#define rc p << 1 | 1
struct Tree {
    int l, r;
    int lsum, rsum, sum, mx;
}tr[N * 4];

void pushup(int p) {
    tr[p].lsum = max(tr[lc].lsum, tr[lc].sum + tr[rc].lsum);
    tr[p].rsum = max(tr[rc].rsum, tr[lc].rsum + tr[rc].sum);
    tr[p].sum = tr[lc].sum + tr[rc].sum;
    tr[p].mx = tr[lc].rsum + tr[rc].lsum;
    tr[p].mx = max(tr[p].mx, tr[lc].mx);
    tr[p].mx = max(tr[p].mx, tr[rc].mx);
}
void build(int p, int l, int r) {
    tr[p] = {l, r, a[l], a[l], a[l], a[l]};
    if (l == r) {
        return ;
    }
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}

void modify(int p, int x, int y) {
    if (tr[p].r < x || tr[p].l > x) return ;
    if (tr[p].l == tr[p].r && tr[p].l == x) {
        tr[p].mx = y;
        tr[p].lsum = tr[p].rsum = y;
        tr[p].sum = y;
        return ;
    }
    int mid = tr[p].l + tr[p].r >> 1;
    if (x <= mid) modify(lc, x, y);
    else modify(rc, x, y);
    pushup(p);
}

Tree merge(Tree p1, Tree p2) {
    Tree ans = {0, 0, 0, 0, 0, 0};
    ans.lsum = max(p1.lsum, p1.sum + p2.lsum);
    ans.rsum = max(p2.rsum, p1.rsum + p2.sum);
    ans.sum = p1.sum + p2.sum;
    ans.mx = p1.rsum + p2.lsum;
    ans.mx = max(ans.mx, p1.mx);
    ans.mx = max(ans.mx, p2.mx);
    return ans;
}
Tree query(int p, int ql, int qr) {
    if (tr[p].l >= ql && tr[p].r <= qr) return tr[p];
    if (tr[p].r < ql || tr[p].l > qr) return {0, 0, 0, 0, 0, 0};
    int mid = tr[p].l + tr[p].r >> 1;
    if (qr <= mid) return query(lc, ql, qr);
    if (ql > mid) return query(rc, ql, qr);
    return merge(query(lc, ql, qr), query(rc, ql, qr));
}

void solve() {
    int n, q; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 0) {
            int x, y; cin >> x >> y;
            modify(1, x, y);
        }
        else {
            int ql, qr; cin >> ql >> qr;
            cout << query(1, ql, qr).mx << '\n';
        }
    }
}

signed main() {
    //freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(0);

    // int T; cin >> T;
    // while (T--) 
        solve();

    return 0;
}
```



### 区间修改

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
const int inf = LONG_LONG_MAX;
using i64 = long long;

const int N = 4e5 + 10;
#define lc p << 1
#define rc p << 1 | 1
struct Tree {
    int l, r, sum, add, mul;
}tr[N * 4];

int n, q, mod;
int a[N];
void pushup(int p) {
    tr[p].sum = (tr[lc].sum + tr[rc].sum) % mod;
}

void build(int p, int l, int r) {
    tr[p] = {l, r, 0, 0, 1};
    if (l == r) {
        tr[p].sum = a[l] % mod;
        return ;
    }

    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}

void pushdown(int p) {
    tr[lc].sum = (tr[lc].sum * tr[p].mul % mod + (tr[p].add * (tr[lc].r - tr[lc].l + 1) % mod)) % mod;
    tr[lc].mul = (tr[lc].mul * tr[p].mul) % mod;
    tr[lc].add = (tr[lc].add * tr[p].mul + tr[p].add) % mod;

    tr[rc].sum = (tr[rc].sum * tr[p].mul % mod + (tr[p].add * (tr[rc].r - tr[rc].l + 1) % mod)) % mod;
    tr[rc].mul = (tr[rc].mul * tr[p].mul) % mod;
    tr[rc].add = (tr[rc].add * tr[p].mul + tr[p].add) % mod;

    tr[p].add = 0;
    tr[p].mul = 1;
}
void update_add(int p, int ql, int qr, int k) {
    if (tr[p].l > qr || tr[p].r < ql) return ;
    if (ql <= tr[p].l && qr >= tr[p].r) {
        tr[p].add = (tr[p].add + k) % mod;
        tr[p].sum = (tr[p].sum + (tr[p].r - tr[p].l + 1) * k) % mod;
        return ;
    }
    
    pushdown(p);
    int mid = tr[p].l + tr[p].r >> 1;
    if (ql <= mid) update_add(lc, ql, qr, k);
    if (qr > mid) update_add(rc, ql, qr, k);
    pushup(p);
}

void update_mul(int p, int ql, int qr, int k) {
    if (tr[p].l > qr || tr[p].r < ql) return ;
    if (ql <= tr[p].l && qr >= tr[p].r) {
        tr[p].mul = tr[p].mul * k % mod;
        tr[p].add = tr[p].add * k % mod;
        tr[p].sum = tr[p].sum * k % mod;
        return ;
    }

    pushdown(p);
    int mid = tr[p].l + tr[p].r >> 1;
    if (ql <= mid) update_mul(lc, ql, qr, k);
    if (qr > mid) update_mul(rc, ql, qr, k);
    pushup(p);
}

int query(int p, int ql, int qr) {
    if (tr[p].l > qr || tr[p].r < ql) return 0;
    if (ql <= tr[p].l && qr >= tr[p].r) return tr[p].sum % mod;
    pushdown(p);

    int ans = 0;
    int mid = tr[p].l + tr[p].r >> 1;
    if (ql <= mid) ans += query(lc, ql, qr);
    if (qr > mid) ans += query(rc, ql, qr);
    ans %= mod;
    return ans;
}

void solve() {
    cin >> n >> q >> mod;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    while (q--) {
        int op; cin >> op;
        int l, r; cin >> l >> r;
        if (op == 1) {
            int k; cin >> k;
            update_mul(1, l, r, k);
        }
        else if (op == 2) {
            int k; cin >> k;
            update_add(1, l, r, k);
        }
        else {
            cout << query(1, l, r) << '\n';
        }
    }
}

signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

### 势能线段树

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
//#define int long long
#define endl '\n'
const int inf = LONG_LONG_MAX;
using i64 = long long;

const int N = 4e5 + 10;
#define lc p << 1
#define rc p << 1 | 1

struct Tree {
    int l, r, sum, mx;
}tr[N * 4];
int a[N];

void pushup(int p) {
    tr[p].sum = tr[lc].sum | tr[rc].sum;
    tr[p].mx = max(tr[lc].mx, tr[rc].mx);
}

void build(int p, int l, int r) {
    tr[p] = {l, r, a[l], a[l]};
    if (l == r) return ;
    
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}


void modify(int p, int x, int v) {
    if (x < tr[p].l || x > tr[p].r) return ;
    if (tr[p].l == tr[p].r && tr[p].l == x) {
        tr[p].sum = v;
        tr[p].mx = v;
        return ;
    }

    int mid = tr[p].l + tr[p].r >> 1;
    if (x <= mid) modify(lc, x, v);
    if (x > mid) modify(rc, x, v);
    pushup(p);
}

void update(int p, int ql, int qr, int v) {
    if (tr[p].l > qr || tr[p].r < ql) return ;
    if (tr[p].l == tr[p].r) {
        tr[p].sum &= v;
        tr[p].mx &= v;
        return ;
    }

    if ((tr[p].sum & v) == tr[p].sum) return ;
    update(lc, ql, qr, v);
    update(rc, ql, qr, v);
    pushup(p);
}

int query(int p, int ql, int qr) {
    if (tr[p].l > qr || tr[p].r < ql) return 0;
    if (ql <= tr[p].l && qr >= tr[p].r) return tr[p].mx;
    int ans = 0;
    int mid = tr[p].l + tr[p].r >> 1;
    if (ql <= mid) ans = max(ans, query(lc, ql, qr));
    if (qr > mid) ans = max(ans, query(rc, ql, qr));
    return ans;
}

int read() {
    int x; scanf("%lld", &x);
    return x;
}

char op[4];
void solve() {
    int n, m; n = read(), m = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    build(1, 1, n);

    while (m--) {
        scanf("%s", op);
        if (op[0] == 'A') {
            int l, r, v; l = read(), r = read(), v = read();
            update(1, l, r, v);
        }
        else if (op[0] == 'U') {
            int x, v; x = read(), v = read();
            modify(1, x, v);
        }
        else {
            int l, r; l = read(), r = read();
            cout << query(1, l, r) << '\n';
        }
    }
}

signed main() {
    //IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

### 主席树

#### 求区间第k大
```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
const int inf = LONG_LONG_MAX;
using i64 = long long;

const int N = 2e5 + 10;
#define lc(x) tr[x].ch[0]
#define rc(x) tr[x].ch[1]
struct Tree {
    int ch[2];
    int s;
}tr[N * 22];
int root[N];
int a[N];
int idx;

void build(int &p, int l, int r) {
    p = ++idx;
    if (l == r) return ;
    int mid = l + r >> 1;
    build(lc(p), l, mid);
    build(rc(p), mid + 1, r);
}

void insert(int x, int &y, int l, int r, int v) {
    y = ++idx;
    tr[y] = tr[x];
    tr[y].s++;
    if (l == r) return ;
    int mid = l + r >> 1;
    if (v <= mid) insert(lc(x), lc(y), l, mid, v);
    else insert(rc(x), rc(y), mid + 1, r, v);
}

int query(int x, int y, int l, int r, int k) {
    if (l == r) return l;
    int mid = l + r >> 1;
    int sum = tr[lc(y)].s - tr[lc(x)].s;
    if (sum >= k) return query(lc(x), lc(y), l, mid, k);
    else return query(rc(x), rc(y), mid + 1, r, k - sum);
}

int arr[N];
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        arr[i] = a[i];
    }  
    build(root[0], 1, n);

    sort(arr + 1, arr + 1 + n);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(arr + 1, arr + 1 + n, a[i]) - arr;
    }

    for (int i = 1; i <= n; i++) {
        insert(root[i - 1], root[i], 1, n, a[i]);
    }

    while (m--) {
        int l, r, k; cin >> l >> r >> k;
        int t = query(root[l - 1], root[r], 1, n, k);
        cout << arr[t] << '\n';
    }
}

signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

#### 主席树二分
题目链接: https://codeforces.com/contest/1997/problem/E
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {int c; cin >> c; return c;}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) {cin >> x;});
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template<typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template<typename T, typename... Args>
void ewrite(const T& first, const Args&... args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"No", "Yes"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

/* next is main_solve */
int n;
int a[N];


struct node {
    int l, r, sum;
} o[N * 30];
int rt[N];
int tot;
int add(int x, int l, int r, int v) {
    int t = ++tot;
    o[t] = o[x];
    o[t].sum++;
    if (l == r)
        return t;
    int mid = (l + r) / 2;
    if (v <= mid)
        o[t].l = add(o[t].l, l, mid, v);
    else
        o[t].r = add(o[t].r, mid + 1, r, v);
    return t;
}

int asksum(int x, int l, int r, int ql, int qr)
{
    if (x == 0)
        return 0;
    if (ql <= l && r <= qr)
        return o[x].sum;
    int mid = l + r >> 1;
    if (ql <= mid && qr > mid)
        return asksum(o[x].l, l, mid, ql, qr) + asksum(o[x].r, mid + 1, r, ql, qr);
    else if (ql <= mid)
        return asksum(o[x].l, l, mid, ql, qr);
    else
        return asksum(o[x].r, mid + 1, r, ql, qr);
}
int ask(int x, int l, int r, int cnt)
{
    if (l == r)
        return l;
    int mid = l + r >> 1;
    if (o[o[x].l].sum >= cnt)
        return ask(o[x].l, l, mid, cnt);
    else
        return ask(o[x].r, mid + 1, r, cnt - o[o[x].l].sum);

}
int ask(int beg, int i, int k)
{

    int sum = o[rt[i]].sum; //总的大于等于i的位置的数量
    int suml;
    if (beg == 1)
        suml = 0;
    else
        suml = asksum(rt[i], 1, n, 1, beg - 1);//beg前面有几个大于等于i

    if (sum - suml < k) //如果剩下的数量不足k个则无法升级，返回n+1
        return n + 1;

    return ask(rt[i], 1, n, suml + k); //区间里第一个等于suml+k的位置
}

vector<int> sb[N];
vector<int> pos[N];

void solve() {
    n = read();
    int q;
    q = read();
    readn(a, n);

    for (int i = 1; i <= n; i++) {
        sb[a[i]].pb(i);
    }

    for (int i = 200000; i >= 1; i--) {
        rt[i] = rt[i + 1];
        for (auto x : sb[i]) {
            rt[i] = add(rt[i], 1, n, x);
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int l = 1, r, i = 1; l <= n; i++) {
            r = ask(l, i, k);
            pos[k].pb(r);
            l = r + 1;
        }
    }

    while (q--) {
        int p, k;
        p = read(), k = read();
        int t = lower_bound(all(pos[k]), p) - pos[k].begin() + 1;
        if (a[p] >= t) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}

void cloud_fly() {
    // int t;
    // cin >> t;
    // while (t--)
    solve();
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cloud_fly();
    return 0;
}

```

### 扫描线

#### 扫描线求面积

```C++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 10;

struct line{
    int x1, x2, y, tag;
}L[N * 2];
bool cmp(line l1, line l2) {
    return l1.y < l2.y;
}
int X[N * 2];

#define lc p << 1
#define rc p << 1 | 1
struct Tree{
    int l, r;
    int cnt, len;
}tr[N * 16];

void pushup(int p) {
    int l = tr[p].l, r = tr[p].r;
    if (tr[p].cnt > 0) tr[p].len = X[r + 1] - X[l];
    else tr[p].len = tr[lc].len + tr[rc].len;
}
void build(int p, int l, int r) {
    tr[p] = {l, r, 0, 0};
    if (l == r) return ;
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

void update(int p, int ql, int qr, int k) {
    if (tr[p].r < ql || tr[p].l > qr) return ;
    if (tr[p].l >= ql && tr[p].r <= qr) {
        tr[p].cnt += k;
        pushup(p);
        return ;
    }

    update(lc, ql, qr, k);
    update(rc, ql, qr, k);
    pushup(p);
}

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        L[i] = {x1, x2, y1, 1};
        L[n + i] = {x1, x2, y2, -1};
        X[i] = x1;
        X[n + i] = x2;
    }
    n *= 2;
    sort(L + 1, L + 1 + n, cmp);
    sort(X + 1, X + 1 + n);
    int m = unique(X + 1, X + 1 + n) - X - 1;
    build(1, 1, m - 1);

    int ans = 0;
    for (int i = 1; i < n; i++) {
        int ql = lower_bound(X + 1, X + 1 + m, L[i].x1) - X;
        int qr = lower_bound(X + 1, X + 1 + m, L[i].x2) - X;
        update(1, ql, qr - 1, L[i].tag);
        ans += 1ll * tr[1].len * (L[i + 1].y - L[i].y);
    }
    cout << ans << '\n';
}

signed main() {
    //freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(0);

    // int T; cin >> T;
    // while (T--) 
        solve();

    return 0;
}
```

#### 扫描线求周长

```C++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 5e3 + 10;
int X[N * 2];
struct line{
    int x1, x2, y, tag;
    bool operator< (const line t) {
        if (y == t.y) return tag > t.tag;
        return y < t.y;
    }
}L[N * 16];

struct Tree{
    int l, r;
    int cnt, len; 
    int lcover, rcover, sum;
}tr[N * 8];
#define lc p << 1
#define rc p << 1 | 1

void build(int p, int l, int r) {
    tr[p] = {l, r, 0, 0, 0, 0, 0};
    if (l == r) return ;
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

void pushup(int p) {
    int l = tr[p].l, r = tr[p].r;
    if (tr[p].cnt) {
        tr[p].len = X[r + 1] - X[l];
        tr[p].sum = 2;
        tr[p].lcover = tr[p].rcover = 1;
    }
    else {
        tr[p].len = tr[lc].len + tr[rc].len;
        tr[p].sum = tr[lc].sum + tr[rc].sum;
        tr[p].lcover = tr[lc].lcover;
        tr[p].rcover = tr[rc].rcover;
        if (tr[lc].rcover && tr[rc].lcover) {
            tr[p].sum -= 2;
        } 
    }
}

void update(int p, int ql, int qr, int k) {
    if (tr[p].r < ql || tr[p].l > qr) return ;
    if (tr[p].l >= ql && tr[p].r <= qr) {
        tr[p].cnt += k;
        pushup(p);
        return ;
    }
    update(lc, ql, qr, k);
    update(rc, ql, qr, k);
    pushup(p);
}

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        X[i] = x1;
        X[n + i] = x2;
        L[i] = {x1, x2, y1, 1};
        L[n + i] = {x1, x2, y2, -1};
    }
    n *= 2;
    sort(X + 1, X + 1 + n);
    int m = unique(X + 1, X + 1 + n) - X - 1;
    sort(L + 1, L + 1 + n);

    build(1, 1, m - 1);
    int ans = 0;
    int lst = 0;
    for (int i = 1; i < n; i++) {
        int l = lower_bound(X + 1, X + 1 + m, L[i].x1) - X;
        int r = lower_bound(X + 1, X + 1 + m, L[i].x2) - X;
        update(1, l, r - 1, L[i].tag);
        ans += abs(tr[1].len - lst);
        lst = tr[1].len;
        ans += tr[1].sum * (L[i + 1].y - L[i].y);
    }
    ans += L[n].x2 - L[n].x1;
    cout << ans << '\n';
}

signed main() {
    //freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(0);

    // int T; cin >> T;
    // while (T--) 
        solve();

    return 0;
}
```

## 平衡树
### Splay
#### 普通平衡树
```c++
#include <iostream>
using namespace std;

#define ls(x) tr[x].s[0]
#define rs(x) tr[x].s[1]
const int N = 1100010, INF = (1 << 30) + 1;
struct node {
    int s[2]; // 左右儿子
    int p;    // 父亲
    int v;    // 节点权值
    int cnt;  // 权值出现次数
    int siz;  // 子树大小
    void init(int p1, int v1) {
        p = p1, v = v1;
        cnt = siz = 1;
    }
} tr[N];
int root; // 根节点编号
int idx;  // 节点个数

void pushup(int x) { tr[x].siz = tr[ls(x)].siz + tr[rs(x)].siz + tr[x].cnt; }
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1];
    tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y;
    tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) // 折转底，直转中
            (ls(y) == x) ^ (ls(z) == y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (!k)
        root = x;
}
void insert(int v) { // 插入
    int x = root, p = 0;
    while (x && tr[x].v != v)
        p = x, x = tr[x].s[v > tr[x].v];
    if (x)
        tr[x].cnt++;
    else {
        x = ++idx;
        if (p)
            tr[p].s[v > tr[p].v] = x;
        tr[x].init(p, v);
    }
    splay(x, 0);
}
void find(int v) { // 找到v并转到根
    int x = root;
    while (tr[x].s[v > tr[x].v] && v != tr[x].v)
        x = tr[x].s[v > tr[x].v];
    splay(x, 0);
}
int getpre(int v) { // 前驱
    find(v);
    int x = root;
    if (tr[x].v < v)
        return x;
    x = ls(x);
    while (rs(x))
        x = rs(x);
    splay(x, 0);
    return x;
}
int getsuc(int v) { // 后继
    find(v);
    int x = root;
    if (tr[x].v > v)
        return x;
    x = rs(x);
    while (ls(x))
        x = ls(x);
    splay(x, 0);
    return x;
}
void del(int v) { // 删除
    int pre = getpre(v);
    int suc = getsuc(v);
    splay(pre, 0), splay(suc, pre);
    int del = tr[suc].s[0];
    if (tr[del].cnt > 1)
        tr[del].cnt--, splay(del, 0);
    else
        tr[suc].s[0] = 0, splay(suc, 0);
}
int getrank(int v) { // 排名
    insert(v);
    int res = tr[tr[root].s[0]].siz;
    del(v);
    return res;
}
int getval(int k) { // 数值
    int x = root;
    while (true) {
        if (k <= tr[ls(x)].siz)
            x = ls(x);
        else if (k <= tr[ls(x)].siz + tr[x].cnt)
            break;
        else
            k -= tr[ls(x)].siz + tr[x].cnt, x = rs(x);
    }
    splay(x, 0);
    return tr[x].v;
}
int main() {
    insert(-INF);
    insert(INF); // 哨兵
    int n, t;
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        insert(x);
    }
    int res = 0, last = 0;
    while (t--) {
        int op, x;
        scanf("%d%d", &op, &x);
        x ^= last;
        if (op == 1)
            insert(x);
        if (op == 2)
            del(x);
        if (op == 3)
            res ^= (last = getrank(x));
        if (op == 4)
            res ^= (last = getval(x + 1));
        if (op == 5)
            res ^= (last = tr[getpre(x)].v);
        if (op == 6)
            res ^= (last = tr[getsuc(x)].v);
    }
    printf("%d\n", res);
    return 0;
}
```
#### 文艺平衡树
```c++
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 100010;
int n, m;
struct node {
    int s[2], p, v;
    int size, tag; // 懒标记
    void init(int p1, int v1) {
        p = p1;
        v = v1;
        size = 1;
    }
} tr[N];
int root, idx;

void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void pushdown(int x) { // 下传
    if (tr[x].tag) {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].tag ^= 1;
        tr[tr[x].s[1]].tag ^= 1;
        tr[x].tag = 0;
    }
}
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1];
    tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y;
    tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) // 折转底，直转中
            (tr[y].s[0] == x) ^ (tr[z].s[0] == y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (k == 0)
        root = x;
}
void insert(int v) {
    int x = root, p = 0;
    while (x)
        p = x, x = tr[x].s[v > tr[x].v];
    x = ++idx;
    tr[p].s[v > tr[p].v] = x;
    tr[x].init(p, v);
    splay(x, 0);
}
int get_k(int k) { // 返回第k个节点编号
    int x = root;
    while (1) {
        pushdown(x);
        int y = tr[x].s[0];
        if (tr[y].size + 1 < k)
            k -= tr[y].size + 1, x = tr[x].s[1];
        else if (tr[y].size >= k)
            x = y;
        else
            return x;
    }
}
void output(int x) { // 中序遍历输出
    pushdown(x);
    if (tr[x].s[0])
        output(tr[x].s[0]);
    if (tr[x].v >= 1 && tr[x].v <= n)
        printf("%d ", tr[x].v);
    if (tr[x].s[1])
        output(tr[x].s[1]);
}
int main() {
    insert(-1e6);
    insert(1e6); // 哨兵
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        insert(i);
    while (m--) {
        // 把[l,r]夹挤到l-1和r+1之间
        int l, r;
        scanf("%d%d", &l, &r);
        l = get_k(l), r = get_k(r + 2);
        splay(l, 0);
        splay(r, l);
        tr[tr[r].s[0]].tag ^= 1;
    }
    output(root);
    return 0;
}
```

### FHQ
#### 普通平衡树
```c++
#include <iostream>
#include <random>
using namespace std;

mt19937_64 rng(time(0));

const int N = 100005;
struct node {
    int l, r; // 左右儿子
    int val;  // 树的权值
    int rnd;  // 堆的随机值
    int size; // 子树大小
} tr[N];
int root, idx;

void newnode(int &x, int v) {
    x = ++idx;
    tr[x].val = v;
    tr[x].rnd = rng();
    tr[x].size = 1;
}
void pushup(int p) { tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1; }
void split(int p, int v, int &x, int &y) {
    if (!p) {
        x = y = 0;
        return;
    }
    if (tr[p].val <= v) {
        x = p;
        split(tr[x].r, v, tr[x].r, y);
        pushup(x);
    } else {
        y = p;
        split(tr[y].l, v, x, tr[y].l);
        pushup(y);
    }
}
int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (tr[x].rnd < tr[y].rnd) {
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    } else {
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}
void insert(int v) {
    int x, y, z;
    split(root, v, x, y);
    newnode(z, v);
    root = merge(merge(x, z), y);
}
void del(int v) {
    int x, y, z;
    split(root, v, x, z);
    split(x, v - 1, x, y);
    y = merge(tr[y].l, tr[y].r);
    root = merge(merge(x, y), z);
}
int getrank(int v) {
    int x, y;
    split(root, v - 1, x, y);
    int ans = tr[x].size + 1;
    root = merge(x, y);
    return ans;
}
int getval(int root, int v) {
    if (v == tr[tr[root].l].size + 1)
        return tr[root].val;
    else if (v <= tr[tr[root].l].size)
        return getval(tr[root].l, v);
    else
        return getval(tr[root].r, v - tr[tr[root].l].size - 1);
}
int getpre(int v) {
    int x, y, s, ans;
    split(root, v - 1, x, y);
    s = tr[x].size;
    ans = getval(x, s);
    root = merge(x, y);
    return ans;
}
int getnxt(int v) {
    int x, y, ans;
    split(root, v, x, y);
    ans = getval(y, 1);
    root = merge(x, y);
    return ans;
}
int main() {
    int n, op, v;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &op, &v);
        if (op == 1)
            insert(v);
        else if (op == 2)
            del(v);
        else if (op == 3)
            printf("%d\n", getrank(v));
        else if (op == 4)
            printf("%d\n", getval(root, v));
        else if (op == 5)
            printf("%d\n", getpre(v));
        else
            printf("%d\n", getnxt(v));
    }
    return 0;
}
```

#### 文艺平衡树
```c++
#include <iostream>
#include <random>
using namespace std;

mt19937_64 rng(time(0));

const int N = 100010;
struct node {
    int l, r; // 左右儿子
    int val;  // 树的权值
    int key;  // 堆的随机值
    int size; // 子树大小
    int tag;  // 懒标记
} tr[N];
int n, m, root, idx;

int newnode(int v) {
    tr[++idx].val = v;
    tr[idx].key = rng();
    tr[idx].size = 1;
    return idx;
}
void pushup(int p) { tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1; }
void pushdown(int p) {
    if (!tr[p].tag || !p)
        return;
    swap(tr[p].l, tr[p].r);
    tr[tr[p].l].tag ^= 1;
    tr[tr[p].r].tag ^= 1;
    tr[p].tag = 0;
}
void split(int p, int k, int &x, int &y) {
    if (!p) {
        x = y = 0;
        return;
    }
    pushdown(p);
    if (k > tr[tr[p].l].size) {
        k -= tr[tr[p].l].size + 1;
        x = p;
        split(tr[p].r, k, tr[p].r, y);
    } else {
        y = p;
        split(tr[p].l, k, x, tr[p].l);
    }
    pushup(p);
}
int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (tr[x].key < tr[y].key) {
        pushdown(x);
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    } else {
        pushdown(y);
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}
void reverse(int l, int r) {
    int x, y, z;
    split(root, r, x, z);
    split(x, l - 1, x, y);
    tr[y].tag ^= 1; // 标记
    root = merge(merge(x, y), z);
}
void output(int p) {
    if (!p)
        return;
    pushdown(p);
    output(tr[p].l);
    printf("%d ", tr[p].val);
    output(tr[p].r);
}
int main() {
    srand(time(0));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        root = merge(root, newnode(i));
    for (int x, y, i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        reverse(x, y);
    }
    output(root);
    return 0;
}
```


# 取模类（MLong & MInt）
```c++
using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
i64 MLong<0LL>::Mod = i64(1E18) + 9;

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 998244353;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1000000007;
using Z = MInt<P>;
```


# 数学

## 快速幂
```c++
int qmi(int a, int b, int p){
    a %= p;
    int ans = 1;
    while (b) {     
        if(b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
```

## 高精度

### 高精度加法

```c++
int A[N], B[N], C[N];
int la, lb, lc;
void add(int A[], int B[], int C[]) {
    for (int i = 0; i < lc; i++) {
        C[i] += A[i] + B[i];//累加
        C[i + 1] += C[i] / 10;//进位
        C[i] %= 10;//存余
    }
    if (C[lc]) lc++;//处理高位
}
void solve() {
    string a, b; cin >> a >> b;
    la = a.size(), lb = b.size(), lc = max(la, lb);
    //反转
    for (int i = la - 1; ~i; i--) A[la - 1 - i] = a[i] - '0';
    for (int i = lb - 1; ~i; i--) B[lb - 1 - i] = b[i] - '0';
    add(A, B, C);
    for (int i = lc - 1; ~i; i--) printf("%d", C[i]);
}
```

### N进制加法

```c++
//luogu 1601
int A[N], B[N], C[N];
int la, lb, lc;
int n;
bool check(int C[]) {
	int i = 0, j = lc - 1;
	while (i < j) {
		if (C[i] != C[j]) return false;
		i++, j--;
	}
	return true;
}
void add(int A[], int B[], int C[]) {
	for (int i = 0; i < lc; i++) {
		C[i] += A[i] + B[i];
		C[i + 1] += C[i] / n;
		C[i] %= n;
	}
	if (C[lc]) lc++;
}
void solve() {
	n = read();
	string m; cin >> m;
	lc = m.size();
	if (n == 16) {//16进制特判
		for (int i = lc - 1; ~i; i--) {
			if (m[i] >= 'A' && m[i] <= 'Z') C[lc - 1 - i] = m[i] - 'A' + 10;
			else C[lc - 1 - i] = m[i] - '0';
		}
	}
	else {
		for (int i = lc - 1; ~i; i--) 
			C[lc - 1 - i] = m[i] - '0';
	}
	 
	if (check(C)) {
		printf("STEP=%d\n", 0);
		return ;
	}
	for (int i = 1; i <= 30; i++) {
		la = lc;
		lb = lc;
		for (int i = lc - 1; i >= 0; i--) {
			A[lc - 1 - i] = C[i];
			B[i] = C[i];
		}
		memset(C, 0, sizeof C);
		add(A, B, C);
		if (check(C)) {
			printf("STEP=%d\n", i);
			return ;
		}
	}
	cout << "Impossible!" << endl;
}
```

### 八进制小数转十进制小数

```C++
#include<bits/stdc++.h>
using namespace std;
int ten[15051]; // 用于存储结果的十进制数

int main(){
	string eight; // 用于存储输入的八进制数
	cin >> eight;
	int index = 0;
	
    // 从八进制数的最低位开始处理
    for (int i = eight.size() - 1; i >= 0; i--){//i是外层已经枚举到的小数位数
        int num = eight[i] - '0'; // 当前处理的八进制位的数字
        int j = 0; //j是每一位计算时已到达的小数位数
        // 对当前位进行处理，计算其在十进制中的值，并累加到结果中
        while(j < index || num ){
            int d = num * 10 + (j < index ? ten[j] :0 ); // 将当前位转换为十进制，并加上之前的结果
            ten[j++] = d / 8;    // 计算当前位的十进制值，并存储到结果数组中
            num = d % 8;      // 计算余数，用于下一轮处理
        }
        index = j; // 更新当前处理的位置
    }
    
    int len = 10000;
    while (!ten[len]) len--;
    for (int i = 0; i <= len; i++) cout << ten[i];

	return 0;
}
```

### 高精度乘低精度

```C++
#include<bits/stdc++.h>
using namespace std;
//C = A * b;A是大数，b使用int类型存储 
vector<int> mul(vector<int> &A,int b)
{
	vector<int> C;//声明一个动态数组，用于储存结果 
	int t=0;//进位的值，初始值是0，即最开始的进位是0 
	for(int i = 0;i < A.size() || t;i++) 
	//在这里循环进行下去的条件是，i还没有循环结束或者进位值t不等于0 
	{
		if(i<A.size()) t += A[i]*b; //计算出，A的其中1位和b的乘积 
		C.push_back(t%10);//余数就是其中一位的值 
		t /= 10; //这个就是需要进到下一位的值 
	}
	while(C.size()>1&&C.back()==0) C.pop_back();//去除前导0 
	return C;
}

int main()
{
	string a;
	int b;
	cin>>a>>b;
	vector<int> A;
	for(int i=a.size()-1;i>=0;i--) A.push_back(a[i]-'0');
	//将a存储在int类型的动态数组中，并且翻转，方便后续计算。 
	vector<int> C = mul(A,b);
	for(int i=C.size()-1;i>=0;i--) printf("%d",C[i]);
	return 0;
}
```

### 高精度乘高精度（O（n^2））

```C++
#include<bits/stdc++.h>
using namespace std;

vector<int> mul(vector<int> &A,vector<int> &B)
{
	vector<int> C(A.size() + B.size());
	for(int i=0;i<A.size();i++)
	{
		for(int j=0;j<B.size();j++)
		{
			C[i + j] += A[i] * B[j];
		}
	}
	int t=0;
	for(int i=0;i<C.size();i++)
	{
		t+=C[i];
		C[i]=t%10;
		t/=10;
	}
	while(C.size()>1&&C.back()==0) C.pop_back();
	
	return C;
} 

int main()
{
    string a,b;
    cin>>a>>b;
    vector<int> A,B;
    for (int i = a.size() - 1;i >= 0;i--) A.push_back(a[i]-'0');
    for (int i = b.size() - 1;i >= 0;i--) B.push_back(b[i]-'0');
    vector<int> C = mul(A,B);
    for (int i = C.size() - 1;i >= 0;i--) cout<<C[i];
    
    return 0;
}
```

### 高精度乘高精度O(nlogn)
luogu P1919 【模板】A*B Problem 升级版（FFT 快速傅里叶变换）
```C++
const int N = 1e7 + 10;
int A[N], B[N];
const int p = 998244353;
const int g = 3, gi = 332748118;
int qmi(int a, int b){
	a %= p;
	int res=1;
	while(b){
		if(b & 1) res = res * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return res;
}
void change(int A[], int n) {
    int k;
    //0 和 最后一个不用反转
    for (int i = 1, j = n / 2; i < n - 1; i++) {
        if (i < j) swap(A[i], A[j]);// i < j 保证只交换一次

        // i 做正常的加1， j 做左反转类型的加1， 始终保持i和j是反转的
        k = n / 2;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        if (j < k) j += k;
    }
}
void ntt(int A[], int n, int op) {
    change(A, n);//位逆序变换（蝴蝶变换）
    for (int m = 2; m <= n; m <<= 1) {//枚举块宽
        int g1 = qmi(op == 1? g : gi, (p - 1) / m);
        for (int i = 0; i < n; i += m) {//枚举块数
            int gk = 1;
            for (int j = 0; j < m / 2; j++) {//枚举半块
                int x = A[i + j] % p, y = gk * A[i + j + m / 2]  % p;
                A[i + j] = (x + y) % p;
                A[i + j + m / 2] = (x - y + 2 * p) % p;
                gk = gk * g1 % p;
            }
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> A[i];
    for (int i = 0; i <= m; i++) cin >> B[i];

    int sum = n + m;
    for (m = n + m + 1, n = 1; n <= m; n <<= 1) ;

    ntt(A, n, 1), ntt(B, n, 1);
    for (int i = 0; i < n; i++) A[i] = A[i] * B[i] % p;
    ntt(A, n, -1);

    int inv = qmi(n, p - 2);
    for (int i = 0; i <= sum; i++) {
        cout << (A[i] * inv) % p << " " ;
    }
}
```

## 数论
### 试除法判定质数

```c++
bool is_prime(int x) {
    if(x < 2) return false;
    for(int i = 2; i <= x / i; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
```

### 最大公约数

#### 欧几里德算法

```c++
int gcd(int a, int b) {
    return b? gcd(b, a % b) : a;
}
```

#### 扩展欧几里德算法
$ a * x + b * y = gcd(a, b)的一组整数解 O(logn) $
```c++
int x, y;
int exgcd(int a, int b, int &x, int &y) {//返回gcd(a,b) 并求出解(引用带回)
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

//如果求不定方程：a * x + b * y = c的一组整数解
int d = exgcd(a, b, x, y);
if (c % d == 0) {
    x = c / d * x;
    y = c / d * y;
}
else {
    puts("无解");
}
```

### 数论分块（整除分块）
$ ∑f[i] * (k / i) $
```c++

int res = n * k;

for (int l = 1, r; l <= n; l = r + 1) {

  if (k / l == 0) break;

  r = min(k / (k / l), n);

  res -= (k / l) * (r - l + 1) * (l + r) / 2; 

}
```

### 欧拉函数

```c++
int phi(int x) {
    int res = x;
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            res = res / i * (i - 1);
        }
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}
```

### 筛法

#### 埃式筛

```c++
const int N = 1e7 + 10;
int pr[N];
void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            if (!pr[j]) pr[j] = i;
        }
    }
}
```

#### 线性筛求质数

```c++
vector<int> minp, primes;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p: primes) {
            if (i * p > n) break;
            minp[i * p] = p;
            if (p == minp[i]) break;
        }
    }
}
```

#### 线性筛求欧拉函数

```c++
int primes[N], cnt;
int phi[N];
bool st[N];
void sieve(int n) {
    st[1] = true;
    phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}
```

### 分解质因数

```c++
vector<int> breakdown(int n) {
    vector<int> result;
    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) { 
        while (n % i == 0) n /= i;
        result.push_back(i);
      }
    }
    if (n != 1) {  
      result.push_back(n);
    }
    return result;
}
```

### 约数

```c++
void get_divisors(int n)
{
    vector<int> res;
    for (int i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            res.push_back(i);

            if (i != n / i) {  
                res.push_back(n / i);
            }
        }
    }
    sort(res.begin(), res.end());
    for (auto item : res) {
        cout << item << " ";
    }
    puts("");
}
```

### 裴蜀定理


特别地，一定存在整数 $x$ 和 $y$ 的解，使得 $ax+by=gcd(a,b)$ 成立。
它的一个重要推论为：a,b互质的充分必要条件是存在整数 $x$ , $y$ 使 $ax+by=1$ ; 
或者说对于方程 $ax+by=1$ 只有整数 $a$ 和 $b$ 互质时，方程才有整数解 $x,y$ 


### 欧拉定理&费马小定理


定义：对任意两个正整数 $a$ , $n$ ,如果两者互质，那么 $a^{φ(n)} ≡ 1(mod \ n)$

若存在整数 $a$ , $p$

$p$ 为质数, 那么 $a^{p-1}≡ 1(mod \ p)$

费马小定理是欧拉定理的一种特殊情况(当 $n$ 为质数时 $φ(n)$ 为 $n-1$ )


### 乘法逆元

欧拉定理 $a^{p-1} ≡ 1(mod \ p)$
对于任意互质的 $a$ , $p$ 恒成立。
欧拉定理用来求逆元用的是欧拉定理的一个推论：
$a * a ^ {φ(p) - 1} ≡ 1(mod \ p)$
由于 $a * a^{-1} ≡ 1(mod \ p)$ 
在这里的 $a^{-1}$ 不就是上面的 $a ^ {φ(p) -1}$ 吗？，所以求出 $a ^ {φ(p) - 1}$ 就好了。

补充：其实如果$p$是质数的话，可以用费马小定理，与欧拉定理是完全一样的，费马小定理在p不是质数时，则只能用欧拉定理。
怎么弄呢？费马小定理 $a ^ {p - 1} ≡ 1(mod \ p)$ $p$ 是质数，且 $a$, $p$ 互质，
然后将上面的式子变一下, $a * a ^ {p - 2} ≡ 1(mod \ p)$ 
再变一下
$a ^ {p - 2} ≡ a ^ {-1} (mod \ p)$ 
然后求出 $a ^ {p - 2}$ 就可以了。
然后再看一下欧拉定理，
如果p是质数
$φ(p) = p - 1$
那么我们求 $a ^ {φ(p) - 1}$ 
也就是求 $a ^ {p - 2}$ 
和费马小定理是一样的。
因此, 分数取余如下：
一般 $p$ 为质数, 则直接乘 $qmi(b, p - 2, p)$
欧拉广义降幂：求 $a ^ {b} \ mod \ p$

1. $gcd(a, p) = 1$, $a ^ {b} \ mod \ p =  a ^ {b \ mod \ φ(p)} \ mod \ p$
2. $gcd(a, p) != 1$ ,

    若 $b < φ(p)$ , $a ^ {b} \ mod \ p = a ^ {b} \ mod \ p$ ;

    若 $b >= φ(p)$ , $a ^ {b} \ mod \ p = a ^ {b \ mod \ φ(p) + φ(p)} \ mod \ p$

### 除法取模

```C++
int qmi(int a, int b, int p){
    a %= p;
    int res=1;
    while (b) {     
        if(b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return res;
}

int inv(int x) {
	return qmi(x, mod - 2, mod);
}
```



### 线性同余方程
 a * x ≡ b (mod m) <=> a * x (mod m) m ≡ b

当b = 1时，x 为 a 的乘法逆元

```c++
void solve() {
    int d = exgcd(a, m, x, y);
    if (b % d == 0) {
        res = 1ll * x * b / d % m;
    }
    else {
        puts("无解");
    }
}
```

## 组合数学

### 排列组合
#### 组合数
##### dp
```C++
const int N = 1e3 + 10;
const int mod = 998244353;
int C[N][N];
void init() {
    for (int i = 0; i < N; i++) C[i][0] = 1, C[i][1] = i;
    for (int i = 2; i < N; i++) {
        for (int j = 2; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
}
```

##### 预处理法
```C++
const int N = 1e6 + 10;
const int mod = 998244353;
int fac[N], invfac[N];
int qmi(int a, int b, int p){
    a %= p;
    int res = 1;
    while (b) {     
        if(b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return res;
}
int inv(int x) {
    return qmi(x, mod - 2, mod);
}
void init() {
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        invfac[i] = invfac[i - 1] * inv(i) % mod;
    }
}
int C(int n, int r) {
    if (r > n) return 0;
    return fac[n] * invfac[r] % mod * invfac[n - r] % mod;
}
```

##### Lucas定理
模板题：https://www.luogu.com.cn/problem/P3807
```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr)
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
using i64 = long long;

const int N = 1e5 + 10;
int mod = 998244353;
int fac[N], invfac[N];
int qmi(int a, int b, int p){
    a %= p;
    int res = 1;
    while (b) {     
        if(b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return res;
}
int inv(int x) {
    return qmi(x, mod - 2, mod);
}
void init() {
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        invfac[i] = invfac[i - 1] * inv(i) % mod;
    }
}
int C(int n, int r) {
    if (r > n) return 0;
    return fac[n] * invfac[r] % mod * invfac[n - r] % mod;
}

int Lucas(int n, int r) {
    if (r == 0) return 1;
    return C(n % mod, r % mod) * Lucas(n / mod, r / mod) % mod;  
}
void solve(){
    int n, m, p; cin >> n >> m >> p;
    mod = p;
    init();
    cout << Lucas(n + m, n) << '\n';
}   

signed main() {
    IOS;
    int T; cin >> T;
    while (T--)
        solve();

    return 0;
} 
```

##### 十二重计数法
```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr)
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
using i64 = long long;
int n, m; 
const int N = 2e5 + 10;
const int mod = 998244353;
int fac[N], invfac[N];
int qmi(int a, int b, int p){
    a %= p;
    int res = 1;
    while (b) {     
        if(b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return res;
}
int inv(int x) {
    return qmi(x, mod - 2, mod);
}
void init() {
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        invfac[i] = invfac[i - 1] * inv(i) % mod;
    }
}
int C(int n, int r) {
    if (r > n) return 0;
    return fac[n] * invfac[r] % mod * invfac[n - r] % mod;
}

//I：球之间互不相同，盒子之间互不相同。
void solve1(){
    int ans = qmi(m, n, mod);
    cout << ans << '\n';
}   


//II：球之间互不相同，盒子之间互不相同，每个盒子至多装一个球
void solve2(){
    int ans = 1;
    for (int i = 0; i < n; i++) {
        ans = ans * (m - i) % mod;
    }
    cout << ans << '\n';
}   


//III：球之间互不相同，盒子之间互不相同，每个盒子至少装一个球。
//考虑容斥：枚举多少个盒子空了，然后剩下的部分就是第一个部分了。
void solve3(){
    int ans = 0;
    for (int i = 0; i < m; i++) {
        ans += ((i & 1? mod - C(m, i): C(m, i)) * qmi(m - i, n, mod)) % mod;
        ans %= mod;
    }
    cout << ans << '\n';
}   

//IV：球之间互不相同，盒子全部相同。
//考虑第二类斯特林数
int Stirling[N];
void solve4(){
    
}   
void solve5(){

}   
void solve6(){

}   
void solve7(){

}   
void solve8(){

}   
void solve9(){

}   
void solve10(){

}   
void solve11(){

}   

void solve12(){

}   

signed main() {
    IOS;
    init();
    cin >> n >> m;
    solve1();
    solve2();
    solve3();
    solve4();
    solve5();
    solve6();
    solve7();
    solve8();
    solve9();
    solve10();
    solve11();
    solve12();

    return 0;
} 
```

### 容斥原理与鸽巢原理

## 线性代数

### 矩阵快速幂加速递推
例题： https://codeforces.com/group/mey3UXMrvB/contest/515223/problem/B
```C++
struct mat {
    int row, col;
    int a[4][4];
    mat() {
        row = col = 4;
        memset(a, 0, sizeof a);
    }
    mat operator* (mat b) {
        mat c;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < b.col; j++) {
                for (int k = 0; k < col; k++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j] % mod) % mod;
                }
            }
        }
        return c;
    }
};
mat pow(mat p, int m) {
    mat ans;
    for (int i = 0; i <= 3; i++) ans.a[i][i] = 1;
    while (m) {
        if (m & 1) ans = ans * p;
        m >>= 1;
        p = p * p;
    }
    return ans;
}
```



### 异或线性基

高斯消元法求解异或线性基

2024CCPC网络赛J题
```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void writen(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void write(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void ewrite(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 1e9 + 7;

int a[N];
int b[N];
int p[N];
int d[N];
int tot = 0;

int lgmx = 30;
void insert(int x) {
    for (int i = lgmx; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (!p[i]) {
                p[i] = x;
                break;
            }
            x ^= p[i];
        }
    }
}

void rebuild() {
    for (int i = 0; i <= lgmx; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if ((p[i] >> j) & 1) {
                p[i] ^= p[j];
            }
        }
    }
    for (int i = 0; i <= lgmx; i++) {
        if (p[i]) d[tot++] = p[i];
    }
}
void solve() {
    int n;
    n = read();

    int xa = 0, xb = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        xa ^= a[i];
    }
    for (int i = 1; i <= n; i++) {
        b[i] = read();
        xb ^= b[i];
    }

    tot = 0;
    for (int i = 0; i <= lgmx; i++) {
        p[i] = d[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        insert(a[i] ^ b[i]);
    }
    rebuild();

    int ans = max(xa, xb);
    for (int i = tot - 1; i >= 0; i--) {
        int mx = max(xa ^ d[i], xb ^ d[i]);
        if (mx < ans) {
            xa ^= d[i];
            xb ^= d[i];
            ans = mx;
        }
    }
    write(ans);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T;
    T = read();
    while (T--)
        solve();

    return 0;
}
```
### 逆序对
#### 线性判定排列逆序数的奇偶性
```c++
int parity(const vector<int> &a) {
    const int n = a.size();
    vector<int> vis(n);
    int p = n % 2;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        for (int j = i; !vis[j]; j = a[j]) {
            vis[j] = 1;
        }
        p ^= 1;
    }
    return p;
}
```

#### 求解逆序对个数
##### 树状数组
```c++

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 5e5 + 10;
int tr[N];

int n;

int lowbit(int x) {
    return x & -x;
}

void add(int i, int k) {
    for ( ; i < N; i += lowbit(i)) {
        tr[i] += k;
    }
}

int sum(int i) {
    int s = 0;
    for ( ; i; i -= lowbit(i)) {
        s += tr[i];
    }
    return s;
}

vector<int> vec;
int ans;
int a[N];
signed main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        vec.push_back(x);
        a[i] = x;
    }

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    for (int i = 0; i < n; i++) {
        int x = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
        ans += sum(N - 1) - sum(x);
        add(x, 1);
    }

    cout << ans << endl;

    return 0;
}
```

##### 归并排序
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

// inline int read() {
//     register int x = 0, t = 1;
//     register char ch = getchar(); 
//     while (ch < '0'|| ch > '9'){
//         if (ch == '-')
//             t = -1;
//         ch = getchar();
//     }
//     while (ch >= '0' && ch <= '9'){
//         x = (x << 1) + (x << 3) + (ch ^ 48);  
//         ch = getchar();
//     }
//     return x * t;
// }

// void print128(__int128 x) {
//     if (x < 0)
//         putchar('-'), x = -x;
//     if (x > 9)
//         print128(x / 10);
//     putchar(x % 10 + '0');
// }

inline int read() {
    int c;
    cin >> c;
    return c;
}

inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }


int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

int a[N];
int tmp[N];
int ans = 0;
void merge(int l, int r) {
    if (l == r) return ;
    int mid = l + r >> 1;
    merge(l, mid);
    merge(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (i = l; i <= r; i++) a[i] = tmp[i];
}

void solve() {
    int n = read();
    readn(a, n);
    merge(1, n);
    print(ans);
}


signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // int T = 1;
    // T = read();
    // while (T--)
        solve();

    return 0;
}
```



## 多项式与生成函数

### 快速傅里叶变换
luogu P1919 【模板】A*B Problem 升级版（FFT 快速傅里叶变换）
```c++
const double PI = acos(-1.0);
struct Complex{
    double x, y;
    Complex(double _x = 0.0, double _y = 0.0) {
        x = _x, y = _y;
    }
    Complex operator +(const Complex &b) const{
        return Complex(x + b.x, y + b.y);
    }
    Complex operator -(const Complex &b) const{
        return Complex(x - b.x, y - b.y);
    }
    Complex operator *(const Complex &b) const{
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }   
};
Complex A[N], B[N];
void change(Complex A[], int n) {
    int k;
    //0 和 最后一个不用反转
    for (int i = 1, j = n / 2; i < n - 1; i++) {
        if (i < j) swap(A[i], A[j]);// i < j 保证只交换一次

        // i 做正常的加1， j 做左反转类型的加1， 始终保持i和j是反转的
        k = n / 2;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        if (j < k) j += k;
    }
}
void fft(Complex A[], int n, int op) {
    change(A, n);//位逆序变换（蝴蝶变换）
    for (int m = 2; m <= n; m <<= 1) {//枚举块宽
        Complex w1({cos(2 * PI / m), sin(2 * PI / m) * op});
        for (int i = 0; i < n; i += m) {//枚举块数
            Complex wk({1, 0});
            for (int j = 0; j < m / 2; j++) {//枚举半块
                Complex x = A[i + j], y = A[i + j + m / 2] * wk;
                A[i + j] = x + y;
                A[i + j + m / 2] = x - y;
                wk = wk * w1;
            }
        }
    }
}
char a[N], b[N];
int ans[N];
void solve() {
    scanf("%s%s", a, b);
    int n = strlen(a) - 1, m = strlen(b) - 1;
    for (int i = 0; i <= n; i++) A[i].x = a[n - i] - '0';
    for (int i = 0; i <= m; i++) B[i].x = b[m - i] - '0';
    for (m = n + m, n = 1; n <= m; n <<= 1) ;
    fft(A, n, 1), fft(B, n, 1);
    for (int i = 0; i < n; i++) A[i] = A[i] * B[i];
    fft(A, n, -1);
    int k = 0;
    for (int i = 0, t = 0; i < n || t; i++) {
        t += A[i].x / n + 0.5;
        ans[k++] = t % 10;
        t /= 10;
    }
    while (k > 1 && !ans[k - 1]) k--;
    for (int i = k - 1; i >= 0; i--)
	    printf("%d", ans[i]);
}
```

### 快速数论变换
luohu P3803 【模板】多项式乘法（FFT）
```c++
const int N = 1e7 + 10;
int A[N], B[N];
const int p = 998244353;
const int g = 3, gi = 332748118;
int qmi(int a, int b){
	a %= p;
	int res=1;
	while(b){
		if(b & 1) res = res * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return res;
}
void change(int A[], int n) {
    int k;
    //0 和 最后一个不用反转
    for (int i = 1, j = n / 2; i < n - 1; i++) {
        if (i < j) swap(A[i], A[j]);// i < j 保证只交换一次

        // i 做正常的加1， j 做左反转类型的加1， 始终保持i和j是反转的
        k = n / 2;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        if (j < k) j += k;
    }
}
void ntt(int A[], int n, int op) {
    change(A, n);//位逆序变换（蝴蝶变换）
    for (int m = 2; m <= n; m <<= 1) {//枚举块宽
        int g1 = qmi(op == 1? g : gi, (p - 1) / m);
        for (int i = 0; i < n; i += m) {//枚举块数
            int gk = 1;
            for (int j = 0; j < m / 2; j++) {//枚举半块
                int x = A[i + j] % p, y = gk * A[i + j + m / 2]  % p;
                A[i + j] = (x + y) % p;
                A[i + j + m / 2] = (x - y + 2 * p) % p;
                gk = gk * g1 % p;
            }
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> A[i];
    for (int i = 0; i <= m; i++) cin >> B[i];

    int sum = n + m;
    for (m = n + m + 1, n = 1; n <= m; n <<= 1) ;

    ntt(A, n, 1), ntt(B, n, 1);
    for (int i = 0; i < n; i++) A[i] = A[i] * B[i] % p;
    ntt(A, n, -1);

    int inv = qmi(n, p - 2);
    for (int i = 0; i <= sum; i++) {
        cout << (A[i] * inv) % p << " " ;
    }
}
```
## bitset

### bitset异或
bitset计算一次的复杂度 O( n / 32 )
```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
using i64 = long long;

int a[2010][2010];
bitset<2010> f[2010][1010];//第j列
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        bitset<2010> bi;
        for (int j = 1; j <= m; j++) {
            bi ^= f[j][a[i][j]];
            f[j][a[i][j]][i] = 1;
        }
        ans += bi.count();
    }

    cout << ans << '\n';
}
 
signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
 
```

### bitset加速背包

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
using i64 = long long;

const int N = 1e6 + 10;
bitset<N> dp[110];
void solve() {
    int n; cin >> n;
    dp[0].set(0);
    for (int i = 1; i <= n; i++) {
        int l, r; cin >> l >> r;
        for (int j = l; j <= r; j++) {
            dp[i] |= (dp[i - 1] << (j * j));
        }
    }

    cout << dp[n].count();
}
 
signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

## 01分数规划
分数规划顾名思义就是求一个分数表达式的最大（小）值。
分数规划是一项不常用到的（但还蛮实用的）算法，一般来讲就是求一个最优比率。
### 二分法
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define vi vector
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second
#define endl '\n'

inline int read() {
    int c;
    cin >> c;
    return c;
}
inline void readn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cin >> x; });
}
inline void printn(int a[], int n) {
    for_each(a + 1, a + n + 1, [](int &x) { cout << x << ' '; });
    cout << endl;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template <typename T, typename... Args>
void eprint(const T &first, const Args &...args) {
    cerr << '*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n)                                                          \
    {                                                                          \
        cerr << #a << ' ';                                                     \
        for (int i = 1; i <= n; i++)                                           \
            cerr << (a)[i] << ' ';                                             \
        cerr << endl;                                                          \
    }

char out[2][10] = {"NO", "YES"};
const double eps = 1e-6;
const int inf = 1e18;
const int N = 1e6 + 10;
const int M = N << 1;
const int mod = 998244353;

void print128(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print128(x / 10);
    putchar(x % 10 + '0');
}

int Sqrt(int x) {
    assert(x >= 0);
    int t = sqrt(x);
    while ((t + 1) * (t + 1) <= x)
        t++;
    while (t * t > x)
        t--;
    return t;
}
int n, k;
int v[N], w[N];
double a[N];
bool cmp(double x, double y) {
    return x > y;
} 
bool check(double mid) {
    for (int i = 1; i <= n; i++) a[i] = w[i] - mid * v[i];
    sort(a + 1, a + 1 + n, cmp);
    double sum = 0;
    for (int i = 1; i <= k; i++) {
        sum += a[i];
    }
    return sum > 0;
}

void solve() {
    n = read(), k = read();
    for (int i = 1; i <= n; i++) {
        v[i] = read();
        w[i] = read();
    }
    
    double l = 0, r = 1e9;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }

    printf("%.2lf\n", l);
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T = 1;
    T = read();
    while (T--)
        solve();

    return 0;
}
```

### Dinkelbach
Dinkelbach 算法的大概思想是每次用上一轮的答案当做新的 L 来输入，不断地迭代，直至答案收敛。

# 离线算法
## 莫队

### 基础莫队

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
using i64 = long long;

const int N = 1e5 + 10;
struct Q{
    int l, r, id;
}q[N];
int B;
bool cmp(Q x, Q y) {
    if (x.l / B != y.l / B) return x.l < y.l;
    return x.r < y.r;
}

int a[N];
int ans[N];
int sum;
int cnt[N];
void add(int x) {
    sum -= cnt[x] * cnt[x];
    cnt[x]++;
    sum += cnt[x] * cnt[x];
}
void del(int x) {
    sum -= cnt[x] * cnt[x];
    cnt[x]--;
    sum += cnt[x] * cnt[x];
}
void solve() {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    B = sqrt(n);
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        q[i] = {l, r, i};
    }

    sort(q, q + m, cmp);
    for (int i = 0, l = 1, r = 0; i < m; i++) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].id] = sum;
    }

    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
}
 
signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}

```

### 带修莫队

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
const int inf = LONG_LONG_MAX;
using i64 = long long;

const int N = 1e6 + 10;
int a[N];
int mq, mr;
int B;
struct Q{ 
  int l,r,id,tim; 
  bool operator<(Q &b){
    if(l / B != b.l / B) return l < b.l;
    if(r / B != b.r / B) return r < b.r;
    return tim < b.tim;
  }
}q[N];
struct R{ 
  int p,c;
}R[N];
int sum,cnt[N],ans[N];
void add(int x) {
    if (!cnt[x]) sum++;
    cnt[x]++;
}

void del(int x) {
    cnt[x]--;
    if (!cnt[x]) sum--;
}

void solve() {
    int n, m; cin >> n >> m;
    B = pow(n, 0.66);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        char ch; cin >> ch;
        int l, r; cin >> l >> r;
        if (ch == 'Q') {
            q[++mq] = {l, r, mq, mr};
        }
        else {
            R[++mr] = {l, r};
        }
    }

    sort(q + 1, q + 1 + mq);
    for (int i = 1, l = 1, r = 0, x = 0; i <= mq; i++) {
        while(l > q[i].l) add(a[--l]); 
        while(r < q[i].r) add(a[++r]); 
        while(l < q[i].l) del(a[l++]); 
        while(r > q[i].r) del(a[r--]); 

        while (x < q[i].tim) {
            int p = R[++x].p;
            if (l <= p && p <= r) {
                del(a[p]);
                add(R[x].c);
            }
            swap(a[p], R[x].c);
        }
        while (x > q[i].tim) {
            int p = R[x].p;
            if (l <= p && p <= r) {
                del(a[p]);
                add(R[x].c);
            }
            swap(a[p], R[x--].c);
        }
        ans[q[i].id] = sum;
    }

    for (int i = 1; i <= mq; i++) {
        cout << ans[i] << '\n';
    }
}

signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

### 回滚莫队

```C++
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr);
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
#define all(x) x.begin(),x.end()
#define PII pair<int, int>
#define x first
#define y second
#define ll long long
#define int long long
#define endl '\n'
const int inf = LONG_LONG_MAX;
using i64 = long long;

const int N = 1e6 + 10;
int a[N], b[N];
int block[N];
int res,last,ans[N],cnt[N],c[N];
int B;
struct Q{
    int l,r,id;
    bool operator<(Q &b){
      if(block[l] != block[b.l])return l < b.l;
      return r < b.r;
    }
}q[N];

int calc(int l, int r) {
    int mx = 0;
    for (int i = l; i <= r; i++) c[a[i]] = 0;
    for (int i = l; i <= r; i++) {
        c[a[i]]++;
        mx = max(mx, c[a[i]] * b[a[i]]);
    }
    return mx;
}

void add(int x) {
    cnt[x]++;
    res = max(res, cnt[x] * b[x]);
}
void solve() {
    int n, m; cin >> n >> m;
    B = sqrt(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
        block[i] = (i - 1) / B + 1;
    }
    int num = block[n];
    
    sort(b + 1, b + 1 + n);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
    }

    for (int i = 1; i <= m; i++) {
        int l, r; cin >> l >> r;
        q[i] = {l, r, i};
    }
    sort(q + 1, q + 1 + m);

    for (int i = 1, x = 1; i <= num; i++) {
        for (int j = 1; j <= n; j++) cnt[j] = 0;
        res = last = 0;
        int R = min(i * B, n);
        int l = R + 1, r = R;
        for ( ; block[q[x].l] == i; x++) {
            if (block[q[x].l] == block[q[x].r]) {
                ans[q[x].id] = calc(q[x].l, q[x].r);
                continue;
            }
            while (r < q[x].r) add(a[++r]);
            last = res;
            while (l > q[x].l) add(a[--l]);
            ans[q[x].id] = res;
            while (l <= R) cnt[a[l++]]--;
            res = last;
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
}

signed main() {
    IOS;
    // int T; cin >> T;
    // while (T--)
        solve();
 
    return 0;
}
```

### 树上莫队
时间复杂度 O(n^(5/3))
```C++
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

#define LL long long
const int N = 200005;
int head[N], to[N], ne[N], idx;
void link(int u, int v) { // 连边
    to[++idx] = v;
    ne[idx] = head[u];
    head[u] = idx;
}

int fa[N], son[N], siz[N], dep[N], top[N];
int tim, in[N], out[N], a[N << 1];
void dfs1(int u, int f) { // 树链剖分
    fa[u] = f;
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = ne[i]) {
        int v = to[i];
        if (v == f)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v])
            son[u] = v;
    }
}
void dfs2(int u, int t) {
    in[u] = ++tim; // 进u时刻
    a[tim] = u;    // 括号序
    top[u] = t;
    if (son[u])
        dfs2(son[u], t);
    for (int i = head[u]; i; i = ne[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
    out[u] = ++tim; // 出u时刻
    a[tim] = u;     // 括号序
}
int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int n, m, k, B, tot, V[N], W[N], C[N];
int pos[N], newC[N], vis[N], cnt[N];
LL ans[N], sum;
struct Q {
    int l, r, t, id, lca;
    bool operator<(Q &b) {
        if (l / B != b.l / B)
            return l < b.l;
        if (r / B != b.r / B)
            return r < b.r;
        return t < b.t;
    }
} q[N];

void add(int x) {
    vis[x] ^= 1; // 访问x点的次数
    // 一次扩展 加上贡献，两次扩展 减去贡献
    if (vis[x])
        sum += 1ll * W[++cnt[C[x]]] * V[C[x]];
    else
        sum -= 1ll * W[cnt[C[x]]--] * V[C[x]];
}
int main() {
    scanf("%d%d%d", &n, &m, &k); // 点,糖果种类,操作
    for (int i = 1; i <= m; ++i)
        scanf("%d", &V[i]); // 美味
    for (int i = 1; i <= n; ++i)
        scanf("%d", &W[i]);           // 新奇
    for (int i = 1, u, v; i < n; ++i) // 连边
        scanf("%d%d", &u, &v), link(u, v), link(v, u);
    // 预处理括号序和LCA
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &C[i]); // 糖果类型
    // 预处理操作
    for (int i = 1, t = 0, Type, x, y; i <= k; ++i) {
        scanf("%d%d%d", &Type, &x, &y);
        if (Type == 1) { // 区查
            int lca = LCA(x, y);
            q[++tot].t = t;
            q[tot].id = tot;
            if (in[x] > in[y])
                swap(x, y); // 先x后y
            if (lca == x) { // 直链情况
                q[tot].l = in[x];
                q[tot].r = in[y];
            } else { // 折链情况
                q[tot].l = out[x];
                q[tot].r = in[y];
                q[tot].lca = lca; // 以便补偿
            }
        } else {          // 点修
            pos[++t] = x; // 位置
            newC[t] = y;  // 修改值
        }
    }
    // 树上带修莫队
    B = pow(2 * n, 0.66);
    sort(q + 1, q + tot + 1);
    for (int i = 1, l = 1, r = 0, t = 0; i <= tot; ++i) {
        while (l > q[i].l)
            add(a[--l]);
        while (r < q[i].r)
            add(a[++r]);
        while (l < q[i].l)
            add(a[l++]);
        while (r > q[i].r)
            add(a[r--]);
        while (t < q[i].t) { // 时间戳变大则替换
            ++t;
            if (vis[pos[t]]) {
                add(pos[t]);
                swap(C[pos[t]], newC[t]); // 换成修改值
                add(pos[t]);
            } else
                swap(C[pos[t]], newC[t]);
        }
        while (t > q[i].t) { // 时间戳变小则还原
            if (vis[pos[t]]) {
                add(pos[t]);
                swap(C[pos[t]], newC[t]); // 还原修改值
                add(pos[t]);
            } else
                swap(C[pos[t]], newC[t]);
            t--;
        }
        ans[q[i].id] = sum;
        if (q[i].lca)
            ans[q[i].id] += // 补上lca的
                1ll * W[cnt[C[q[i].lca]] + 1] * V[C[q[i].lca]];
    }
    for (int i = 1; i <= tot; ++i)
        printf("%lld\n", ans[i]);
}
```
