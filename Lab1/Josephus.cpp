#include <iostream>

// 链表节点结构体
struct Node {
    int id;      // 人的编号
    Node* next;  // 指向下一个人的指针

    // 构造函数
    Node(int _id) : id(_id), next(nullptr) {}
};

// 循环单链表类来模拟约瑟夫问题
class JosephusCircle {
private:
    Node* tail; // 尾指针，tail->next 即为头节点

public:
    // 构造函数，建立一个n个人的圆圈
    JosephusCircle(int n) {
        // 处理n=0或n=1的边界情况
        if (n <= 0) {
            tail = nullptr;
            return;
        }

        // 创建第一个节点（编号为1），让它自己指向自己形成一个最小的环
        tail = new Node(1);
        tail->next = tail;

        // 循环创建并插入后续节点（编号从2到n）
        for (int i = 2; i <= n; ++i) {
            Node* newNode = new Node(i);
            newNode->next = tail->next; // 新节点指向头节点
            tail->next = newNode;       // 原尾节点指向新节点
            tail = newNode;             // 更新尾指针为新节点
        }
    }

    // 析构函数，释放所有节点的内存
    ~JosephusCircle() {
        if (tail == nullptr) {
            return;
        }
        // 获取头节点
        Node* current = tail->next;
        // 断开环，方便遍历删除
        tail->next = nullptr;
        
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // 模拟报数过程并找出获胜者
    int findWinner(int k) {
        if (tail == nullptr) {
            return -1; // 空圆圈，返回错误码
        }

        // prev指针指向被淘汰者的前一个节点
        // 初始时，从编号为1的人开始报数，其前一个节点是tail（编号为n的人）
        Node* prev = tail;

        // 循环直到只剩下一个人
        // 结束条件：当一个节点的next指针指向自己时，说明链表中只剩它一个
        while (prev->next != prev) {
            // 从当前位置前进 k-1 步，找到要被淘汰者的前一个节点
            // 报数k的人出列，相当于从前一个人开始走k-1步
            for (int i = 1; i < k; ++i) {
                prev = prev->next;
            }

            // 待淘汰的节点
            Node* victim = prev->next;

            // 从链表中移除victim节点
            prev->next = victim->next;

            // 如果被淘汰的是尾节点，需要更新尾指针
            if (victim == tail) {
                tail = prev;
            }

            // 释放内存
            delete victim;
        }

        // 循环结束后，prev（也是tail）指向唯一的幸存者
        return prev->id;
    }
};

int main() {
    // 提高C++ I/O效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k;

    // 创建约瑟夫环
    JosephusCircle circle(n);

    // 找到并输出获胜者
    int winner = circle.findWinner(k);
    std::cout << winner << std::endl;

    return 0;
}