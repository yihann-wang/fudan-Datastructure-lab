#include <iostream>
#include <string>
#include <stack>
#include <cctype>

/**
 * 问题2：字符串解码
 * 
 * 功能描述：
 * 给定一个编码字符串，按照规则解码返回原始字符串。
 * 编码规则：k[encoded_string]，表示将 encoded_string 重复 k 次。
 * 例如：3[a]2[bc] -> aaabcbc，2[abc]3[cd]ef -> abcabccdcdcdef
 * 
 * 算法思路：
 * 使用两个栈来处理嵌套结构：
 * - countStack：存储重复次数
 * - stringStack：存储当前层级的字符串
 * 
 * 时间复杂度：O(n * k)，其中n是输入长度，k是最大重复次数
 * 空间复杂度：O(n)
 */
int main() {
    // 读取输入的编码字符串
    std::string s;
    std::cin >> s;

    // 存储重复次数的栈
    std::stack<int> countStack;
    // 存储字符串的栈，用于处理嵌套结构
    std::stack<std::string> stringStack;
    // 当前正在构建的字符串
    std::string currentString = "";
    // 当前数字（重复次数）
    int k = 0;

    // 遍历编码字符串的每个字符
    for (char ch : s) {
        if (isdigit(ch)) {
            // 如果是数字，构建重复次数（可能是多位数）
            k = k * 10 + (ch - '0');
        } else if (ch == '[') {
            // 遇到'['，表示开始一个新的编码块
            // 将当前的重复次数和字符串分别压入栈中
            countStack.push(k);
            stringStack.push(currentString);
            // 重置变量为新的编码块做准备
            currentString = "";
            k = 0;
        } else if (ch == ']') {
            // 遇到']'，表示一个编码块结束，需要解码
            // 获取之前保存的字符串和重复次数
            std::string decodedString = stringStack.top();
            stringStack.pop();
            int count = countStack.top();
            countStack.pop();
            
            // 将当前字符串重复count次，追加到之前的字符串后面
            for (int i = 0; i < count; ++i) {
                decodedString += currentString;
            }
            // 更新当前字符串为解码后的结果
            currentString = decodedString;
        } else {
            // 普通字符，直接添加到当前字符串中
            currentString += ch;
        }
    }
    
    // 输出最终解码的字符串
    std::cout << currentString << std::endl;

    return 0;
}
