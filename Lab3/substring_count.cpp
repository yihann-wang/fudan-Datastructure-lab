#include <bits/stdc++.h>
using namespace std;

// 子串计数：使用KMP算法统计模式串在文本中出现的次数（允许重叠）
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pattern;
    if (!getline(cin, text)) {
        return 0;
    }
    if (!getline(cin, pattern)) {
        return 0;
    }

    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());
    if (m == 0 || n == 0 || m > n) {
        cout << 0;
        return 0;
    }

    // 预处理模式串的前缀函数（失败指针），用于KMP算法的高效匹配
    vector<int> pi(m, 0);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }

    // 在文本中搜索模式串，使用KMP算法避免重复比较
    int matches = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            ++matches;
            j = pi[j - 1];
        }
    }

    cout << matches;
    return 0;
}
