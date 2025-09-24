#include <iostream>

// 为了安全处理 2^32-1 范围内的数据，我们使用 long long 类型
using DataType = long long;

// 定义链表节点结构体
struct Node {
    DataType val; // 数据域
    Node* next;   // 指针域

    // 构造函数，方便创建新节点
    Node(DataType value) : val(value), next(nullptr) {}
};

// 定义单链表类
class LinkedList {
private:
    Node* head; // 指向链表头节点的指针

    // 私有辅助函数：根据值查找节点，返回节点指针
    // 在多个成员函数中都会用到，可以提高代码复用性
    Node* findNode(DataType value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->val == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // 如果没有找到，返回空指针
    }

public:
    // 构造函数：初始化链表，创建一个值为1的头节点
    LinkedList() {
        head = new Node(1);
    }

    // 析构函数：释放链表所有节点的内存，防止内存泄漏
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // 1. 返回头节点
    Node* getHead() {
        return head;
    }

    // 2. 返回下一个节点
    Node* getNext(Node* node) {
        if (node) {
            return node->next;
        }
        return nullptr;
    }

    // 3. 插入节点：在值为 x 的节点后插入值为 y 的新节点
    void insertAfter(DataType x, DataType y) {
        Node* nodeX = findNode(x);
        if (nodeX != nullptr) { // 仅当值为x的节点存在时才操作
            Node* newNode = new Node(y);
            newNode->next = nodeX->next;
            nodeX->next = newNode;
        }
    }

    // 4. 删除节点：删除值为 x 的节点
    void deleteNode(DataType x) {
        // 题目保证头节点(1)不会被删除，因此无需处理删除头节点的情况
        if (head == nullptr) {
            return;
        }

        Node* current = head;
        // 寻找要删除节点的前一个节点
        while (current->next != nullptr && current->next->val != x) {
            current = current->next;
        }

        // 如果找到了（即 current->next 的值是 x）
        if (current->next != nullptr) {
            Node* nodeToDelete = current->next;
            current->next = nodeToDelete->next; // 绕过要删除的节点
            delete nodeToDelete; // 释放内存
        }
    }

    // 5. 修改节点：将值为 x 的节点的值修改为 y
    void modifyNode(DataType x, DataType y) {
        Node* nodeX = findNode(x);
        if (nodeX != nullptr) { // 仅当值为x的节点存在时才操作
            nodeX->val = y;
        }
    }

    // 6. 查询节点对应数值：查询值为 x 的节点的后继节点的值
    void querySuccessor(DataType x) {
        Node* nodeX = findNode(x);
        // 如果节点x存在，并且它有后继节点
        if (nodeX != nullptr && nodeX->next != nullptr) {
            std::cout << nodeX->next->val << "\n";
        } else {
            std::cout << 0 << "\n";
        }
    }

    // 7. 顺序打印全部节点
    void printList() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->val;
            if (current->next != nullptr) {
                std::cout << " "; // 最后一个数后不加空格
            }
            current = current->next;
        }
        std::cout << "\n";
    }
};

int main() {
    // 提高C++的I/O效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int q;
    std::cin >> q;

    LinkedList list; // 创建一个链表对象，构造函数会自动初始化

    for (int i = 0; i < q; ++i) {
        int op;
        std::cin >> op;
        DataType x, y;

        switch (op) {
            case 1: // 插入
                std::cin >> x >> y;
                list.insertAfter(x, y);
                break;
            case 2: // 查询后继
                std::cin >> x;
                list.querySuccessor(x);
                break;
            case 3: // 删除
                std::cin >> x;
                list.deleteNode(x);
                break;
            case 4: // 修改
                std::cin >> x >> y;
                list.modifyNode(x, y);
                break;
            case 5: // 打印
                list.printList();
                break;
        }
    }

    return 0;
}