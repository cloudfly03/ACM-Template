#include <iostream>
using namespace std;

extern "C" int __stdcall multi(int x, int y);

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int x, y;
    cin >> x >> y;
    cout << multi(x, y) << endl;
    return 0;
}

int __stdcall multi(int x, int y) {
    int ans = 0;
    asm(
        "movl %1,%%eax;"
        "movl %2,%%ebx;"
        "mul %%ebx;"
        "movl %%eax,%0;"
        :"=m"(ans)
        :"m"(x), "m"(y)
    );
    return ans;
}
