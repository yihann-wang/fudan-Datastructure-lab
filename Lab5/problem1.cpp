#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// 功能：根据前序遍历和中序遍历重建二叉树，并输出后序遍历
// 参数：
//   preorder: 前序遍历序列
//   inorder: 中序遍历序列
void printPostOrder(const std::string& preorder, const std::string& inorder) {
    if (preorder.empty()) {
        return;
    }

    // 前序遍历的第一个节点是根节点
    char root_val = preorder[0];

    // 在中序遍历中找到根节点的位置
    size_t root_idx_inorder = inorder.find(root_val);

    // 根据根节点位置，划分左右子树
    // 左子树的中序遍历
    std::string left_inorder = inorder.substr(0, root_idx_inorder);
    // 右子树的中序遍历
    std::string right_inorder = inorder.substr(root_idx_inorder + 1);

    // 左子树的前序遍历
    std::string left_preorder = preorder.substr(1, left_inorder.length());
    // 右子树的前序遍历
    std::string right_preorder = preorder.substr(1 + left_inorder.length());

    // 递归处理左子树
    printPostOrder(left_preorder, left_inorder);
    // 递归处理右子树
    printPostOrder(right_preorder, right_inorder);
    // 访问根节点
    std::cout << root_val;
}

int main() {
    // 优化 cin 和 cout 的性能
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string inorder, preorder;
    
    // 读取中序和前序遍历
    std::cin >> inorder >> preorder;

    // 计算并输出后序遍历
    printPostOrder(preorder, inorder);

    std::cout << std::endl;

    return 0;
}
