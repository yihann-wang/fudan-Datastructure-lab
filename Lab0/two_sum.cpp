#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

using namespace std;

/**
 * 两数之和问题解决方案
 * 使用哈希表优化查找，时间复杂度O(n)，空间复杂度O(n)
 */
vector<int> twoSum(vector<int>& nums, int target) {
    // 使用哈希表存储值和对应的索引
    unordered_map<int, int> numMap;
    
    // 遍历数组
    for (int i = 0; i < nums.size(); i++) {
        // 计算当前数字需要匹配的补数
        int complement = target - nums[i];
        
        // 检查补数是否已经存在于哈希表中
        if (numMap.find(complement) != numMap.end()) {
            // 找到匹配的两个数，返回它们的索引
            return {numMap[complement], i};
        }
        
        // 将当前数字和索引存入哈希表
        numMap[nums[i]] = i;
    }
    
    // 如果没有找到匹配的两个数，返回空数组（题目保证有解，所以不会执行到这里）
    return {};
}

int main() {
    int target;
    string line;
    
    // 读取目标值
    cin >> target;
    cin.ignore(); // 忽略换行符
    
    // 读取数组
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int num;
    
    // 解析输入的数组
    while (ss >> num) {
        nums.push_back(num);
    }
    
    // 调用两数之和函数
    vector<int> result = twoSum(nums, target);
    
    // 输出结果
    cout << result[0] << " " << result[1] << endl;
    
    return 0;
}