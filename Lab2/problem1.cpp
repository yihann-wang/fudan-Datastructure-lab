#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>

/**
 * 问题1：下一个更大元素（循环数组版本）
 * 
 * 功能描述：
 * 给定一个循环数组（最后一个元素的下一个元素是第一个元素），
 * 对于数组中的每个元素，找到它右边第一个比它大的元素。
 * 如果不存在，则返回-1。
 * 
 * 算法思路：
 * 使用单调栈来解决，栈中存储元素的索引。
 * 由于是循环数组，我们遍历两遍数组来模拟循环效果。
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
int main() {
    // 读取输入的一行数字
    std::string line;
    std::getline(std::cin, line);
    
    // 使用字符串流解析输入的数字
    std::stringstream ss(line);
    std::vector<int> nums;
    int num;
    while (ss >> num) {
        nums.push_back(num);
    }

    int n = nums.size();
    // 初始化结果数组，默认值为-1（表示没有找到更大的元素）
    std::vector<int> res(n, -1);
    // 单调栈，存储元素的索引
    std::stack<int> s;

    // 遍历两遍数组来模拟循环数组
    for (int i = 0; i < 2 * n; ++i) {
        // 获取当前位置的元素值（使用取模运算实现循环）
        int current_num = nums[i % n];
        
        // 当栈不为空且栈顶元素对应的值小于当前元素时
        while (!s.empty() && nums[s.top()] < current_num) {
            // 找到了栈顶元素的下一个更大元素
            res[s.top()] = current_num;
            s.pop();  // 弹出已处理的元素
        }
        
        // 只在第一轮遍历时将索引入栈
        if (i < n) {
            s.push(i);
        }
    }

    // 输出结果
    for (int i = 0; i < n; ++i) {
        std::cout << res[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;

    return 0;
}
