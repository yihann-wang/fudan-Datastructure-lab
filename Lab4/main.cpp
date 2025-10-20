#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

// 定义二叉树节点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 根据层序遍历序列构建二叉树
TreeNode* buildTree(const std::vector<std::string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") {
        return nullptr;
    }

    TreeNode* root = new TreeNode(std::stoi(nodes[0]));
    std::queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < nodes.size()) {
        TreeNode* current = q.front();
        q.pop();

        // 处理左子节点
        if (i < nodes.size() && nodes[i] != "null") {
            current->left = new TreeNode(std::stoi(nodes[i]));
            q.push(current->left);
        }
        i++;

        // 处理右子节点
        if (i < nodes.size() && nodes[i] != "null") {
            current->right = new TreeNode(std::stoi(nodes[i]));
            q.push(current->right);
        }
        i++;
    }

    return root;
}

// 前序遍历
void preorderTraversal(TreeNode* root, std::vector<int>& result) {
    if (root == nullptr) {
        return;
    }
    result.push_back(root->val);
    preorderTraversal(root->left, result);
    preorderTraversal(root->right, result);
}

// 中序遍历
void inorderTraversal(TreeNode* root, std::vector<int>& result) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// 后序遍历
void postorderTraversal(TreeNode* root, std::vector<int>& result) {
    if (root == nullptr) {
        return;
    }
    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result.push_back(root->val);
}

// 打印vector中的元素
void printVector(const std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> nodes;
    while (ss >> item) {
        nodes.push_back(item);
    }

    TreeNode* root = buildTree(nodes);

    std::vector<int> preorder, inorder, postorder;

    preorderTraversal(root, preorder);
    inorderTraversal(root, inorder);
    postorderTraversal(root, postorder);

    printVector(preorder);
    printVector(inorder);
    printVector(postorder);

    return 0;
}
