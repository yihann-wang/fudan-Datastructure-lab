#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class SeqList {
private:
    T* data;           // 指向动态分配的存储空间
    int maxSize;       // 顺序表的最大容量
    int length;        // 顺序表当前长度

public:
    // 构造函数
    SeqList(int size = 10) : maxSize(size), length(0) {
        data = new T[maxSize];
    }
    
    // 拷贝构造函数
    SeqList(const SeqList<T>& other) : maxSize(other.maxSize), length(other.length) {
        data = new T[maxSize];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }
    
    // 析构函数
    ~SeqList() {
        delete[] data;
    }
    
    // 赋值运算符重载
    SeqList<T>& operator=(const SeqList<T>& other) {
        if (this != &other) {
            delete[] data;
            maxSize = other.maxSize;
            length = other.length;
            data = new T[maxSize];
            for (int i = 0; i < length; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // 基本操作
    bool isEmpty() const { return length == 0; }
    bool isFull() const { return length == maxSize; }
    int size() const { return length; }
    int capacity() const { return maxSize; }
    
    // 在指定位置插入元素
    bool insert(int pos, const T& item) {
        if (isFull() || pos < 0 || pos > length) {
            return false;
        }
        
        // 将pos位置及其后面的元素向后移动
        for (int i = length; i > pos; i--) {
            data[i] = data[i-1];
        }
        
        data[pos] = item;
        length++;
        return true;
    }
    
    // 尾插
    bool push_back(const T& item) {
        return insert(length, item);
    }
    
    // 头插
    bool push_front(const T& item) {
        return insert(0, item);
    }
    
    // 删除指定位置的元素
    bool remove(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            return false;
        }
        
        // 将pos位置后面的元素向前移动
        for (int i = pos; i < length - 1; i++) {
            data[i] = data[i+1];
        }
        
        length--;
        return true;
    }
    
    // 按值删除元素（删除第一个匹配的）
    bool removeByValue(const T& item) {
        int pos = find(item);
        if (pos != -1) {
            return remove(pos);
        }
        return false;
    }
    
    // 清空顺序表
    void clear() {
        length = 0;
    }
    
    // 查找元素，返回位置（未找到返回-1）
    int find(const T& item) const {
        for (int i = 0; i < length; i++) {
            if (data[i] == item) {
                return i;
            }
        }
        return -1;
    }
    
    // 获取指定位置的元素
    T& get(int pos) const {
        if (pos < 0 || pos >= length) {
            throw out_of_range("索引超出范围");
        }
        return data[pos];
    }
    
    // 重载[]运算符
    T& operator[](int pos) {
        if (pos < 0 || pos >= length) {
            throw out_of_range("索引超出范围");
        }
        return data[pos];
    }
    
    const T& operator[](int pos) const {
        if (pos < 0 || pos >= length) {
            throw out_of_range("索引超出范围");
        }
        return data[pos];
    }
    
    // 修改指定位置的元素
    bool set(int pos, const T& item) {
        if (pos < 0 || pos >= length) {
            return false;
        }
        data[pos] = item;
        return true;
    }
    
    // 显示所有元素
    void display() const {
        cout << "顺序表内容: [";
        for (int i = 0; i < length; i++) {
            cout << data[i];
            if (i < length - 1) cout << ", ";
        }
        cout << "]" << endl;
        cout << "长度: " << length << ", 容量: " << maxSize << endl;
    }
};

// 使用示例
int main() {
    cout << "=== 顺序表使用示例 ===" << endl;
    
    // 1. 创建顺序表
    SeqList<int> list(5);  // 创建容量为5的整数顺序表
    cout << "创建空的顺序表:" << endl;
    list.display();
    
    cout << "\n=== 插入操作测试 ===" << endl;
    
    // 2. 尾插元素
    cout << "尾插元素 10, 20, 30:" << endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.display();
    
    // 3. 头插元素
    cout << "头插元素 5:" << endl;
    list.push_front(5);
    list.display();
    
    // 4. 在指定位置插入
    cout << "在位置2插入元素15:" << endl;
    list.insert(2, 15);
    list.display();
    
    cout << "\n=== 访问操作测试 ===" << endl;
    
    // 5. 访问元素
    cout << "使用get()访问位置1的元素: " << list.get(1) << endl;
    cout << "使用[]访问位置3的元素: " << list[3] << endl;
    
    // 6. 查找元素
    int target = 20;
    int pos = list.find(target);
    if (pos != -1) {
        cout << "元素 " << target << " 在位置 " << pos << endl;
    } else {
        cout << "未找到元素 " << target << endl;
    }
    
    cout << "\n=== 修改操作测试 ===" << endl;
    
    // 7. 修改元素
    cout << "将位置2的元素修改为25:" << endl;
    list.set(2, 25);
    list.display();
    
    // 8. 使用[]运算符修改
    cout << "使用[]将位置0的元素修改为1:" << endl;
    list[0] = 1;
    list.display();
    
    cout << "\n=== 删除操作测试 ===" << endl;
    
    // 9. 删除指定位置元素
    cout << "删除位置1的元素:" << endl;
    list.remove(1);
    list.display();
    
    // 10. 按值删除元素
    cout << "删除值为25的元素:" << endl;
    list.removeByValue(25);
    list.display();
    
    cout << "\n=== 状态查询测试 ===" << endl;
    
    // 11. 查询状态
    cout << "顺序表是否为空: " << (list.isEmpty() ? "是" : "否") << endl;
    cout << "顺序表是否已满: " << (list.isFull() ? "是" : "否") << endl;
    cout << "当前长度: " << list.size() << endl;
    cout << "最大容量: " << list.capacity() << endl;
    
    cout << "\n=== 拷贝构造测试 ===" << endl;
    
    // 12. 测试拷贝构造
    SeqList<int> list2(list);
    cout << "拷贝构造的新顺序表:" << endl;
    list2.display();
    
    cout << "\n=== 赋值操作测试 ===" << endl;
    
    // 13. 测试赋值操作
    SeqList<int> list3;
    list3 = list;
    cout << "赋值后的顺序表:" << endl;
    list3.display();
    
    cout << "\n=== 清空操作测试 ===" << endl;
    
    // 14. 清空操作
    list.clear();
    cout << "清空后的顺序表:" << endl;
    list.display();
    
    cout << "\n=== 异常处理测试 ===" << endl;
    
    // 15. 异常处理测试
    try {
        cout << "尝试访问空顺序表的元素:" << endl;
        cout << list[0] << endl;  // 这会抛出异常
    } catch (const out_of_range& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    
    cout << "\n=== 字符串顺序表测试 ===" << endl;
    
    // 16. 字符串顺序表测试
    SeqList<string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_back("Data");
    strList.push_back("Structure");
    
    cout << "字符串顺序表:" << endl;
    strList.display();
    
    return 0;
}