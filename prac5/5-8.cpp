#include <iostream>
using namespace std;

class MyIntStack {
    int* p; // ���� �޸𸮷� ����� ������ 
    int size; // ������ �ִ� ũ�� 
    int tos; // ������ ž�� ����Ű�� �ε��� 
public:
    MyIntStack();
    MyIntStack(int size);
    MyIntStack(const MyIntStack& s); // ���� ������ 
    ~MyIntStack();
    bool push(int n); // ���� n�� ���ÿ� Ǫ���Ѵ�.
    // ������ �� �� ������ false��, �ƴϸ� true ���� 
    bool pop(int& n); // ������ ž�� �ִ� ���� n�� ���Ѵ�.
    // ���� ������ ��� ������ false��, �ƴϸ� true ���� 
};

MyIntStack::MyIntStack(int size)
{
    this->size = size;
    p = new int[size];
    tos = 0;
}

MyIntStack::MyIntStack(const MyIntStack& s)
{
    this->size = s.size;
    this->tos = s.tos;
    this->p = new int[s.size];
    for (int i = 0; i < s.size; i++)
    {
        this->p[i] = s.p[i];
    }
}

bool MyIntStack::push(int n) {
    if (tos > size)
        return false;
    else {
        p[tos++] = n;
        return true;
    }
}

bool MyIntStack::pop(int& n) {
    if (tos < 0)
        return false;
    else {
        n = p[--tos];
        return true;
    }
}

MyIntStack::~MyIntStack() {
    delete[] p;
    p = NULL;
}

int main() {
    MyIntStack a(10);
    a.push(10);
    a.push(20);
    MyIntStack b = a; // ���� ���� 
    b.push(30);

    int n;
    a.pop(n); // ���� a �� 
    cout << "���� a���� ���� �� " << n << endl;
    b.pop(n); // ���� b �� 
    cout << "���� b���� ���� �� " << n << endl;
}


