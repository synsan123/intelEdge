#include <iostream>
using namespace std;

class Circle { // ���� ǥ���ϴ� Ŭ���� 
    string name;
    int radius;
public:
    Circle(int radius = 1, string name = "") {
        this->radius = radius; this->name = name;
    }
    friend ostream& operator << (ostream& os, Circle c); // friend ���� 
    friend istream& operator >> (istream& ins, Circle& c); // friend ����, Circle& c ������ ��� 
};

ostream& operator << (ostream& os, Circle c) {
    os << "(��������" << c.radius << "�� " << c.name << ")";
    return os;
}

istream& operator >> (istream& ins, Circle& c) {
    cout << "������ >> ";
    ins >> c.radius;
    cout << "�̸� >> ";
    ins >> c.name;
    return ins;
}

int main() {
    Circle d, w;
    cin >> d >> w; // Ű���� �Է��� �޾� ��ü d�� w�� �ϼ� 
    cout << d << w << endl; // ��ü d, w ��� 
}
