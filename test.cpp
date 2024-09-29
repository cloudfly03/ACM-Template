#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    // 读取每次操作的移动距离
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 记录原始的索引顺序
    vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        indices[i] = i + 1;
    }

    // 按照移动距离从大到小排序，同时保持原始的索引顺序
    sort(indices.begin(), indices.end(), [&](int i, int j) {
        return a[i - 1] > a[j - 1];
        });

    // 当前的绝对位置
    int current_position = abs(x);
    int total_distance = 0;

    // 遍历排序后的步长，贪心选择
    for (int i = 0; i < n; ++i) {
        int step = a[indices[i]-1];
        if (current_position == 0) {
            break;
        }
        if (current_position >= step) {
            total_distance += step;
            current_position -= step;
        }
        else {
            total_distance += current_position;
            current_position = 0;
        }
    }

    // 输出最小总移动距离
    cout << total_distance << endl;

    // 输出操作顺序
    for (int i = 0; i < n; ++i) {
        cout << indices[i] << " ";
    }
    cout << endl;

    return 0;
}
