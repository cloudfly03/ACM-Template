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
#define INF (int)(1e8+1)
#define MOD (int)(998244353)
#define eps (ld)(1e-9)
#define P (int)(998244353)
#define G (int)(3)
#define mpair(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define lowbit(x) (x&-x)


int n, p;
rand rnd(clock());

int qpow(int base, int p, int mod) {
    int ans = 1;
    while (p) {
        if (p & 1) ans = ans * base % mod;
        base = base * base % mod;
        p >>= 1;
    }
    return ans;
}

int complexpow(int x, int y, int ipow2, int p, int mod) {
    int a = 1, b = 0, t1, t2;
    while (p) {
        if (p & 1) {
            t1 = a, t2 = b;
            a = (t1 * x % mod + t2 * y % mod * ipow2 % mod) % mod;
            b = (t1 * y % mod + t2 * x % mod) % mod;
        }
        t1 = x, t2 = y;
        x = (t1 * t1 % mod + t2 * t2 % mod * ipow2 % mod) % mod;
        y = t1 * t2 % mod * 2 % mod;
        p >>= 1;
    }
    return a;
}

int Cipolla(int n, int p) {
    n %= p;
    if (!n || n == 1) return n;
    if (qpow(n, (p - 1) / 2, p) == p - 1) return -1;
    int a = rnd() % p;
    while (!a || qpow((a * a + p - n) % p, (p - 1) / 2, p) == 1) a = rnd() % p;
    int ret = complexpow(a, 1, (a * a + p - n) % p, (p + 1) / 2, p);
    return min(ret, p - ret);
}

void solve() {
    cin >> n >> p;
    int ret = Cipolla(n, p);
    if (ret == -1)
        cout << "Hola!" << endl;
    else if (ret && ret != p - ret)
        cout << ret << ' ' << p - ret << endl;
    else cout << ret << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    // freopen("test.err", "w", stderr);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}