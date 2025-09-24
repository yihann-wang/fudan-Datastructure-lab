#include <iostream>
#include <vector>
#include <stack>

/**
 * 问题3：栈序列验证
 * 
 * 功能描述：
 * 给定两个序列：pushed（入栈序列）和popped（出栈序列），
 * 判断这两个序列是否能够对应一个合法的栈操作序列。
 * 
 * 算法思路：
 * 模拟栈的操作过程：
 * 1. 按照pushed序列的顺序依次入栈
 * 2. 每次入栈后，检查栈顶元素是否与当前期望的出栈元素相同
 * 3. 如果相同，则出栈并移动到下一个期望出栈的元素
 * 4. 最终如果栈为空，说明序列合法
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
int main() {
    // 读取序列长度
    int n;
    std::cin >> n;

    // 读取入栈序列
    std::vector<int> pushed(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> pushed[i];
    }

    // 读取期望的出栈序列
    std::vector<int> popped(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> popped[i];
    }

    // 模拟栈操作
    std::stack<int> s;
    int j = 0;  // 指向当前期望出栈的元素在popped数组中的位置
    
    // 按照pushed序列依次入栈
    for (int i = 0; i < n; ++i) {
        // 将当前元素入栈
        s.push(pushed[i]);
        
        // 检查是否可以出栈：当栈不为空且栈顶元素等于期望出栈的元素时
        while (!s.empty() && s.top() == popped[j]) {
            s.pop();    // 出栈
            j++;        // 移动到下一个期望出栈的元素
        }
    }

    // 判断结果：如果栈为空，说明所有元素都按照popped序列成功出栈
    if (s.empty()) {
        std::cout << "YES" << std::endl;  // 序列合法
    } else {
        std::cout << "NO" << std::endl;   // 序列不合法
    }

    return 0;
}
