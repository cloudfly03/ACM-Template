#include<bits/stdc++.h>
using namespace std;
// #define int long long
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
// #define P (int)(998244353)
// #define G (int)(3)
// #define mpair(x,y) make_pair(x,y)
// #define all(x) x.begin(),x.end()
// #define lowbit(x) (x&-x)
rand rnd(clock());

template<int P = 998244353> struct Poly : public vector<int> {
    using vint = vector<int>;

    static map<int, vector<int>> mp;

    // 空构造 *
    Poly() : vint() {}
    // 指定大小空构造 *
    explicit constexpr Poly(int n) : vint(n) {}
    // 传入 vector 拷贝构造 *
    explicit constexpr Poly(const vint& a) : vint(a) {}
    // 初始化列表构造 ?
    constexpr Poly(const initializer_list<int>& a) : vint(a) {}
    // 迭代器构造 *
    template<class InputIt, class = _RequireInputIter<InputIt>>
    explicit constexpr Poly(InputIt first, InputIt last) : vint(first, last) {}

    // 移位重载 *
    constexpr Poly shift(int k) const {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        }
        else if (this->size() <= -k) {
            return Poly();
        }
        else {
            return Poly(this->begin() + (-k), this->end());
        }
    }
    constexpr Poly operator<<(int k) {
        if (k >= this->size())
            return Poly();
        return Poly(this->begin() + k, this->end());
    }
    constexpr Poly operator>>(int k) {
        auto r = *this;
        r.insert(r.begin(), k, 0);
        return r;
    }
    constexpr Poly& operator<<=(int k) {
        if (k >= this->size())
            this->clear();
        else this->erase(this->begin(), this->begin() + k);
        return *this;
    }
    constexpr Poly& operator>>=(int k) {
        this->insert(this->begin(), k, 0);
        return *this;
    }
    // 复制一个幂次为 0~k-1 的子多项式
    constexpr Poly trunc(int k) const {
        Poly f = *this;
        f.resize(k);
        return f;
    }
    constexpr friend Poly operator+(const Poly& a, const Poly& b) {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) res[i] += a[i];
        for (int i = 0; i < b.size(); i++) res[i] += b[i];
        return res;
    }
    constexpr friend Poly operator-(const Poly& a, const Poly& b) {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) res[i] += a[i];
        for (int i = 0; i < b.size(); i++) res[i] -= b[i];
        return res;
    }
    // 相反化
    constexpr friend Poly operator-(const Poly& a) {
        vector<int> res(a.size());
        for (int i = 0; i < res.size(); i++) res[i] = -a[i];
        return Poly(res);
    }
    // 记忆化加速 *
    constexpr vint getR() {
        int n = this->size();
        // if (n > (1 << 15) && Poly<P>::mp.find(n) != Poly<P>::mp.end()) return mp[n];
        vint R(n);
        for (int i = 1;i < n;++i)
            R[i] = R[i / 2] / 2 + (i & 1 ? n / 2 : 0);
        // if (n > (1 << 15)) Poly<P>::mp[n] = R;
        return R;
    }
    // 快速幂 % P *
    constexpr int qpow(int base, int p) {
        int ans = 1;
        while (p) {
            if (p & 1) ans = ans * base % P;
            base = base * base % P;
            p >>= 1;
        }
        return ans;
    }
    // 乘法逆元 *
    constexpr int inv(int x) {
        return qpow(x, P - 2);
    }

    // 快速数论变换 非递归 *
    constexpr void NTT(bool rev) {
        vint R = this->getR();
        int n = this->size(), G = 3;
        for (int i = 0;i < n;++i)
            if (i < R[i]) {
                int t = (*this)[i];
                (*this)[i] = (*this)[R[i]];
                (*this)[R[i]] = t;
            }
        for (int m = 2;m <= n;m <<= 1) {
            int g1 = qpow(rev ? inv(G) : G, (P - 1) / m);
            for (int i = 0;i < n;i += m) {
                int gk = 1;
                for (int j = 0;j < m / 2;++j) {
                    int x = (*this)[i + j], y = (*this)[i + j + m / 2] * gk % P;
                    (*this)[i + j] = (x + y) % P;
                    (*this)[i + j + m / 2] = (x - y + P) % P;
                    gk = gk * g1 % P;
                }
            }
        }
        if (!rev) return;
        int invn = inv(n);
        for (auto& v : *this) (v *= invn) %= P;
    }

    // 多项式乘
    constexpr friend Poly operator*(Poly a, Poly b) {
        if (a.empty() || b.empty()) return Poly<P>();
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) n <<= 1;
        // // a,b规模小时 暴力
        // if (a.size() * b.size() < 1e5) {
        //     Poly c(a.size() + b.size() - 1);
        //     for (int i = 0; i < a.size(); i++)
        //         for (int j = 0; j < b.size(); j++)
        //             c[i + j] += a[i] * b[j];
        //     return c;
        // }
        a.resize(n), b.resize(n);
        a.NTT(0), b.NTT(0);
        for (int i = 0; i < n; ++i) (a[i] *= b[i]) %= P;
        a.NTT(1);
        a.resize(tot);
        return a;
    }
};


// template<int P = 998244353> struct Poly : vector<int> {
//     constexpr friend Poly operator*(Poly a, Poly b) {
//         if (a.size() == 0 || b.size() == 0) {
//             return Poly();
//         }
//         if (a.size() < b.size()) {
//             swap(a, b);
//         }
//         int n = 1, tot = a.size() + b.size() - 1;
//         while (n < tot) {
//             n *= 2;
//         }
//         if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
//             Poly c(a.size() + b.size() - 1);
//             for (int i = 0; i < a.size(); i++) {
//                 for (int j = 0; j < b.size(); j++) {
//                     c[i + j] += a[i] * b[j];
//                 }
//             }
//             return c;
//         }
//         a.resize(n);
//         b.resize(n);
//         dft(a);
//         dft(b);
//         for (int i = 0; i < n; ++i) {
//             a[i] *= b[i];
//         }
//         idft(a);
//         a.resize(tot);
//         return a;
//     }
//     constexpr friend Poly operator*(int a, Poly b) {
//         for (int i = 0; i < int(b.size()); i++) {
//             b[i] *= a;
//         }
//         return b;
//     }
//     constexpr friend Poly operator*(Poly a, int b) {
//         for (int i = 0; i < int(a.size()); i++) {
//             a[i] *= b;
//         }
//         return a;
//     }
//     constexpr friend Poly operator/(Poly a, int b) {
//         for (int i = 0; i < int(a.size()); i++) {
//             a[i] /= b;
//         }
//         return a;
//     }
//     constexpr Poly& operator+=(Poly b) {
//         return (*this) = (*this) + b;
//     }
//     constexpr Poly& operator-=(Poly b) {
//         return (*this) = (*this) - b;
//     }
//     constexpr Poly& operator*=(Poly b) {
//         return (*this) = (*this) * b;
//     }
//     constexpr Poly& operator*=(int b) {
//         return (*this) = (*this) * b;
//     }
//     constexpr Poly& operator/=(int b) {
//         return (*this) = (*this) / b;
//     }
//     constexpr Poly deriv() const {
//         if (this->empty()) {
//             return Poly();
//         }
//         Poly res(this->size() - 1);
//         for (int i = 0; i < this->size() - 1; ++i) {
//             res[i] = (i + 1) * (*this)[i + 1];
//         }
//         return res;
//     }
//     constexpr Poly integr() const {
//         Poly res(this->size() + 1);
//         for (int i = 0; i < this->size(); ++i) {
//             res[i + 1] = (*this)[i] / (i + 1);
//         }
//         return res;
//     }
//     constexpr Poly inv(int m) const {
//         Poly x{ (*this)[0].inv() };
//         int k = 1;
//         while (k < m) {
//             k *= 2;
//             x = (x * (Poly{ 2 } - trunc(k) * x)).trunc(k);
//         }
//         return x.trunc(m);
//     }
//     constexpr Poly log(int m) const {
//         return (deriv() * inv(m)).integr().trunc(m);
//     }
//     constexpr Poly exp(int m) const {
//         Poly x{ 1 };
//         int k = 1;
//         while (k < m) {
//             k *= 2;
//             x = (x * (Poly{ 1 } - x.log(k) + trunc(k))).trunc(k);
//         }
//         return x.trunc(m);
//     }
//     constexpr Poly pow(int k, int m) const {
//         int i = 0;
//         while (i < this->size() && (*this)[i] == 0) {
//             i++;
//         }
//         if (i == this->size() || 1LL * i * k >= m) {
//             return Poly(m);
//         }
//         int v = (*this)[i];
//         auto f = shift(-i) * v.inv();
//         return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
//     }
//     constexpr Poly sqrt(int m) const {
//         Poly x{ 1 };
//         int k = 1;
//         while (k < m) {
//             k *= 2;
//             x = (x + (trunc(k) * x.inv(k)).trunc(k)) * CInv<2, P>;
//         }
//         return x.trunc(m);
//     }
//     constexpr Poly mulT(Poly b) const {
//         if (b.size() == 0) {
//             return Poly();
//         }
//         int n = b.size();
//         reverse(b.begin(), b.end());
//         return ((*this) * b).shift(-(n - 1));
//     }
//     constexpr vector<int> eval(vector<int> x) const {
//         if (this->size() == 0) {
//             return vector<int>(x.size(), 0);
//         }
//         const int n = max(x.size(), this->size());
//         vector<Poly> q(4 * n);
//         vector<int> ans(x.size());
//         x.resize(n);
//         function<void(int, int, int)> build = [&](int p, int l, int r) {
//             if (r - l == 1) {
//                 q[p] = Poly{ 1, -x[l] };
//             }
//             else {
//                 int m = (l + r) / 2;
//                 build(2 * p, l, m);
//                 build(2 * p + 1, m, r);
//                 q[p] = q[2 * p] * q[2 * p + 1];
//             }
//             };
//         build(1, 0, n);
//         function<void(int, int, int, const Poly&)> work = [&](int p, int l, int r,
//             const Poly& num) {
//                 if (r - l == 1) {
//                     if (l < int(ans.size())) {
//                         ans[l] = num[0];
//                     }
//                 }
//                 else {
//                     int m = (l + r) / 2;
//                     work(2 * p, l, m, num.mulT(q[2 * p + 1]).resize(m - l));
//                     work(2 * p + 1, m, r, num.mulT(q[2 * p]).resize(r - m));
//                 }
//             };
//         work(1, 0, n, mulT(q[1].inv(n)));
//         return ans;
//     }
// };

int n, m;

void solve() {
    cin >> n >> m;
    Poly a(n + 1), b(m + 1);
    for (int i = 0;i <= n;++i) cin >> a[i];
    for (int i = 0;i <= m;++i) cin >> b[i];
    for (auto v : a) cout << v << ' ';
    cout << endl;
    for (auto v : b) cout << v << ' ';
    cout << endl;
    Poly c = a * b;
    for (auto v : c) cout << v << ' ';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    // freopen("test.err", "w", stderr);

    int t = 1;
    //cin >> t;
    while (t--) solve();

    return 0;
}