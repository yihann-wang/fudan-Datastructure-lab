#include <iostream>
#include <string>
#include <vector>
#include <map>

// 二叉树节点定义
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

// 辅助函数：从前序和中序遍历序列构建二叉树
Node* buildTreeHelper(const std::string& preorder, int& pre_idx, const std::string& inorder, int in_start, int in_end, const std::map<char, int>& inorder_map) {
    if (pre_idx >= preorder.length() || in_start > in_end) {
        return nullptr;
    }

    char root_val = preorder[pre_idx++];
    Node* root = new Node(root_val);

    int root_idx_inorder = inorder_map.at(root_val);

    root->left = buildTreeHelper(preorder, pre_idx, inorder, in_start, root_idx_inorder - 1, inorder_map);
    root->right = buildTreeHelper(preorder, pre_idx, inorder, root_idx_inorder + 1, in_end, inorder_map);

    return root;
}

// 主函数：构建二叉树
Node* buildTree(const std::string& preorder, const std::string& inorder) {
    if (preorder.empty() || inorder.empty()) {
        return nullptr;
    }
    // 创建一个map来存储中序遍历中字符的索引，以加速查找
    std::map<char, int> inorder_map;
    for (int i = 0; i < inorder.length(); ++i) {
        inorder_map[inorder[i]] = i;
    }
    int pre_idx = 0;
    return buildTreeHelper(preorder, pre_idx, inorder, 0, inorder.length() - 1, inorder_map);
}

// 查找最近公共祖先 (LCA)
Node* findLCA(Node* root, char n1, char n2) {
    if (root == nullptr) {
        return nullptr;
    }

    // 如果根节点是两个节点之一，则它就是LCA
    if (root->data == n1 || root->data == n2) {
        return root;
    }

    // 在左右子树中查找LCA
    Node* left_lca = findLCA(root->left, n1, n2);
    Node* right_lca = findLCA(root->right, n1, n2);

    // 如果左右子树都找到了LCA，说明当前根节点是它们的LCA
    if (left_lca && right_lca) {
        return root;
    }

    // 否则，LCA在非空的一边
    return (left_lca != nullptr) ? left_lca : right_lca;
}

// 检查节点是否存在于树中
bool doesNodeExist(const std::string& traversal, char node_val) {
    return traversal.find(node_val) != std::string::npos;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string preorder, inorder;
    char node1, node2;

    // 读取前序、中序遍历和两个节点
    std::cin >> preorder >> inorder >> node1 >> node2;

    // 检查两个节点是否存在于树中
    if (!doesNodeExist(inorder, node1) || !doesNodeExist(inorder, node2)) {
        std::cout << "NA" << std::endl;
        return 0;
    }

    // 构建二叉树
    Node* root = buildTree(preorder, inorder);

    // 查找并输出LCA
    Node* lca = findLCA(root, node1, node2);
    if (lca != nullptr) {
        std::cout << lca->data << std::endl;
    }

    // (此处省略了释放树内存的代码，因为程序即将结束)

    return 0;
}
