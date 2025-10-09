#include <bits/stdc++.h>
using namespace std;

// 矩阵乘法：计算两个矩阵的乘积并对结果取模
// 使用优化的循环顺序(i-k-j)来提高缓存命中率
// 常数模数，用来控制结果范围
static constexpr long long MOD = 1'000'000'007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, m;
    if (!(cin >> n >> p >> m)) {
        return 0;
    }

    // 存储输入的矩阵 A 与 B，提前取模确保乘法安全
    vector<vector<long long>> a(n, vector<long long>(p));
    vector<vector<long long>> b(p, vector<long long>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            long long x;
            cin >> x;
            x %= MOD;
            if (x < 0) {
                x += MOD;
            }
            a[i][j] = x;
        }
    }
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < m; ++j) {
            long long x;
            cin >> x;
            x %= MOD;
            if (x < 0) {
                x += MOD;
            }
            b[i][j] = x;
        }
    }

    // 结果矩阵 C = A × B
    // 使用 i-k-j 循环顺序，当A[i][k]为0时跳过内层循环以提高效率
    vector<vector<long long>> c(n, vector<long long>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < p; ++k) {
            long long aik = a[i][k];
            if (aik == 0) {
                continue;
            }
            for (int j = 0; j < m; ++j) {
                c[i][j] += aik * b[k][j] % MOD;
                if (c[i][j] >= MOD) {
                    c[i][j] -= MOD;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << c[i][j];
            if (j + 1 < m) {
                cout << ' ';
            }
        }
        if (i + 1 < n) {
            cout << '\n';
        }
    }
    return 0;
}
