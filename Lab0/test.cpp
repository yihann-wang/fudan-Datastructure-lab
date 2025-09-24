#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class SeqList {
private:
    T* data;           // ָ��̬����Ĵ洢�ռ�
    int maxSize;       // ˳�����������
    int length;        // ˳���ǰ����

public:
    // ���캯��
    SeqList(int size = 10) : maxSize(size), length(0) {
        data = new T[maxSize];
    }
    
    // �������캯��
    SeqList(const SeqList<T>& other) : maxSize(other.maxSize), length(other.length) {
        data = new T[maxSize];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }
    
    // ��������
    ~SeqList() {
        delete[] data;
    }
    
    // ��ֵ���������
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
    
    // ��������
    bool isEmpty() const { return length == 0; }
    bool isFull() const { return length == maxSize; }
    int size() const { return length; }
    int capacity() const { return maxSize; }
    
    // ��ָ��λ�ò���Ԫ��
    bool insert(int pos, const T& item) {
        if (isFull() || pos < 0 || pos > length) {
            return false;
        }
        
        // ��posλ�ü�������Ԫ������ƶ�
        for (int i = length; i > pos; i--) {
            data[i] = data[i-1];
        }
        
        data[pos] = item;
        length++;
        return true;
    }
    
    // β��
    bool push_back(const T& item) {
        return insert(length, item);
    }
    
    // ͷ��
    bool push_front(const T& item) {
        return insert(0, item);
    }
    
    // ɾ��ָ��λ�õ�Ԫ��
    bool remove(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            return false;
        }
        
        // ��posλ�ú����Ԫ����ǰ�ƶ�
        for (int i = pos; i < length - 1; i++) {
            data[i] = data[i+1];
        }
        
        length--;
        return true;
    }
    
    // ��ֵɾ��Ԫ�أ�ɾ����һ��ƥ��ģ�
    bool removeByValue(const T& item) {
        int pos = find(item);
        if (pos != -1) {
            return remove(pos);
        }
        return false;
    }
    
    // ���˳���
    void clear() {
        length = 0;
    }
    
    // ����Ԫ�أ�����λ�ã�δ�ҵ�����-1��
    int find(const T& item) const {
        for (int i = 0; i < length; i++) {
            if (data[i] == item) {
                return i;
            }
        }
        return -1;
    }
    
    // ��ȡָ��λ�õ�Ԫ��
    T& get(int pos) const {
        if (pos < 0 || pos >= length) {
            throw out_of_range("����������Χ");
        }
        return data[pos];
    }
    
    // ����[]�����
    T& operator[](int pos) {
        if (pos < 0 || pos >= length) {
            throw out_of_range("����������Χ");
        }
        return data[pos];
    }
    
    const T& operator[](int pos) const {
        if (pos < 0 || pos >= length) {
            throw out_of_range("����������Χ");
        }
        return data[pos];
    }
    
    // �޸�ָ��λ�õ�Ԫ��
    bool set(int pos, const T& item) {
        if (pos < 0 || pos >= length) {
            return false;
        }
        data[pos] = item;
        return true;
    }
    
    // ��ʾ����Ԫ��
    void display() const {
        cout << "˳�������: [";
        for (int i = 0; i < length; i++) {
            cout << data[i];
            if (i < length - 1) cout << ", ";
        }
        cout << "]" << endl;
        cout << "����: " << length << ", ����: " << maxSize << endl;
    }
};

// ʹ��ʾ��
int main() {
    cout << "=== ˳���ʹ��ʾ�� ===" << endl;
    
    // 1. ����˳���
    SeqList<int> list(5);  // ��������Ϊ5������˳���
    cout << "�����յ�˳���:" << endl;
    list.display();
    
    cout << "\n=== ����������� ===" << endl;
    
    // 2. β��Ԫ��
    cout << "β��Ԫ�� 10, 20, 30:" << endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.display();
    
    // 3. ͷ��Ԫ��
    cout << "ͷ��Ԫ�� 5:" << endl;
    list.push_front(5);
    list.display();
    
    // 4. ��ָ��λ�ò���
    cout << "��λ��2����Ԫ��15:" << endl;
    list.insert(2, 15);
    list.display();
    
    cout << "\n=== ���ʲ������� ===" << endl;
    
    // 5. ����Ԫ��
    cout << "ʹ��get()����λ��1��Ԫ��: " << list.get(1) << endl;
    cout << "ʹ��[]����λ��3��Ԫ��: " << list[3] << endl;
    
    // 6. ����Ԫ��
    int target = 20;
    int pos = list.find(target);
    if (pos != -1) {
        cout << "Ԫ�� " << target << " ��λ�� " << pos << endl;
    } else {
        cout << "δ�ҵ�Ԫ�� " << target << endl;
    }
    
    cout << "\n=== �޸Ĳ������� ===" << endl;
    
    // 7. �޸�Ԫ��
    cout << "��λ��2��Ԫ���޸�Ϊ25:" << endl;
    list.set(2, 25);
    list.display();
    
    // 8. ʹ��[]������޸�
    cout << "ʹ��[]��λ��0��Ԫ���޸�Ϊ1:" << endl;
    list[0] = 1;
    list.display();
    
    cout << "\n=== ɾ���������� ===" << endl;
    
    // 9. ɾ��ָ��λ��Ԫ��
    cout << "ɾ��λ��1��Ԫ��:" << endl;
    list.remove(1);
    list.display();
    
    // 10. ��ֵɾ��Ԫ��
    cout << "ɾ��ֵΪ25��Ԫ��:" << endl;
    list.removeByValue(25);
    list.display();
    
    cout << "\n=== ״̬��ѯ���� ===" << endl;
    
    // 11. ��ѯ״̬
    cout << "˳����Ƿ�Ϊ��: " << (list.isEmpty() ? "��" : "��") << endl;
    cout << "˳����Ƿ�����: " << (list.isFull() ? "��" : "��") << endl;
    cout << "��ǰ����: " << list.size() << endl;
    cout << "�������: " << list.capacity() << endl;
    
    cout << "\n=== ����������� ===" << endl;
    
    // 12. ���Կ�������
    SeqList<int> list2(list);
    cout << "�����������˳���:" << endl;
    list2.display();
    
    cout << "\n=== ��ֵ�������� ===" << endl;
    
    // 13. ���Ը�ֵ����
    SeqList<int> list3;
    list3 = list;
    cout << "��ֵ���˳���:" << endl;
    list3.display();
    
    cout << "\n=== ��ղ������� ===" << endl;
    
    // 14. ��ղ���
    list.clear();
    cout << "��պ��˳���:" << endl;
    list.display();
    
    cout << "\n=== �쳣������� ===" << endl;
    
    // 15. �쳣�������
    try {
        cout << "���Է��ʿ�˳����Ԫ��:" << endl;
        cout << list[0] << endl;  // ����׳��쳣
    } catch (const out_of_range& e) {
        cout << "�����쳣: " << e.what() << endl;
    }
    
    cout << "\n=== �ַ���˳������ ===" << endl;
    
    // 16. �ַ���˳������
    SeqList<string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_back("Data");
    strList.push_back("Structure");
    
    cout << "�ַ���˳���:" << endl;
    strList.display();
    
    return 0;
}