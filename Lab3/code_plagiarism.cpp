#include <bits/stdc++.h>
using namespace std;

// 代码抄袭检测：使用改进的KMP算法，支持变量名替换的模式匹配
// 大写字母表示关键字/常量（必须完全匹配），小写字母表示变量名（可替换但需保持一致性）
namespace {
inline bool isUpper(char ch) {
    // 是否为表示关键字/常量的大写字母
    return ch >= 'A' && ch <= 'Z';
}

inline bool isLower(char ch) {
    // 是否为表示变量名的小写字母
    return ch >= 'a' && ch <= 'z';
}

vector<int> computePrevLower(const string& s) {
    // 记录每个位置的同名变量上一次出现在哪，便于检查替换关系
    vector<int> prev(s.size(), -1);
    array<int, 26> last;
    last.fill(-1);
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        const char ch = s[i];
        if (isLower(ch)) {
            const int idx = ch - 'a';
            prev[i] = last[idx];
            last[idx] = i;
        }
    }
    return prev;
}

bool canMatchPatternIndices(const string& pattern, const vector<int>& prevPattern,
                            int suffixIdx, int prefixIdx) {
    // 前后缀匹配时检查变量依赖是否一致
    const int start = suffixIdx - prefixIdx;
    const char prefixChar = pattern[prefixIdx];
    const char suffixChar = pattern[suffixIdx];
    if (isUpper(prefixChar)) {
        return isUpper(suffixChar) && prefixChar == suffixChar;
    }
    if (!isLower(suffixChar)) {
        return false;
    }
    const int prevPrefix = prevPattern[prefixIdx];
    const int prevSuffix = prevPattern[suffixIdx];
    if (prevPrefix == -1) {
        return prevSuffix < start;
    }
    return prevSuffix == start + prevPrefix;
}

vector<int> prefixFunction(const string& pattern, const vector<int>& prevPattern) {
    // 针对自定义匹配规则构建 KMP 的前缀函数
    const int m = static_cast<int>(pattern.size());
    vector<int> pi(m, 0);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && !canMatchPatternIndices(pattern, prevPattern, i, j)) {
            j = pi[j - 1];
        }
        if (canMatchPatternIndices(pattern, prevPattern, i, j)) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

bool canMatchTextChar(const string& pattern, const vector<int>& prevPattern,
                      const string& text, const vector<int>& prevText,
                      int patIdx, int textIdx, int start) {
    // 将模式串当前位置与文本字符进行匹配判断
    const char patChar = pattern[patIdx];
    const char textChar = text[textIdx];
    if (isUpper(patChar)) {
        return isUpper(textChar) && patChar == textChar;
    }
    if (!isLower(textChar)) {
        return false;
    }
    const int prevPat = prevPattern[patIdx];
    const int prevTxt = prevText[textIdx];
    if (prevPat == -1) {
        return prevTxt < start;
    }
    return prevTxt == start + prevPat;
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pattern;
    if (!(cin >> text)) {
        return 0;
    }
    if (!(cin >> pattern)) {
        return 0;
    }

    // 如果长度不满足要求则直接返回 0
    if (pattern.empty() || text.empty() || pattern.size() > text.size()) {
        cout << 0;
        return 0;
    }

    const int m = static_cast<int>(pattern.size());
    // 预处理模式串与文本中变量的前一次出现位置
    const vector<int> prevPattern = computePrevLower(pattern);
    const vector<int> pi = prefixFunction(pattern, prevPattern);
    const vector<int> prevText = computePrevLower(text);

    // 使用KMP算法在文本中搜索所有匹配的模式串
    long long matches = 0;
    int j = 0;
    for (int i = 0; i < static_cast<int>(text.size()); ++i) {
        const int start = i - j;
        // 若当前字符不匹配，则根据前缀函数回退
        while (j > 0 && !canMatchTextChar(pattern, prevPattern, text, prevText, j, i, start)) {
            j = pi[j - 1];
        }
        if (canMatchTextChar(pattern, prevPattern, text, prevText, j, i, i - j)) {
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
