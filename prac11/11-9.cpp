#include <iostream>
using namespace std;

class Phone { // ��ȭ ��ȣ�� ǥ���ϴ� Ŭ���� 
    string name;
    string telnum;
    string address;
public:
    Phone(string name = "", string telnum = "", string address = "") {
        this->name = name;
        this->telnum = telnum;
        this->address = address;
    }
    friend ostream& operator << (ostream& os, Phone p); // friend �ۼ� 
    friend istream& operator >> (istream& ins, Phone& p); // friend �ۼ�, Phone& p ������ ��� 
};

ostream& operator << (ostream& os, Phone p) {
    os << "(" << p.name << "," << p.telnum << "," << p.address << ")";
    return os;
}

istream& operator >> (istream& ins, Phone& p) {
    cout << "�̸�:";
    ins >> p.name;
    cout << "��ȭ��ȣ:";
    ins >> p.telnum;
    cout << "�ּ�:";
    ins >> p.address;
    return ins;
}

int main() {
    Phone girl, boy;
    cin >> girl >> boy; // ��ȭ ��ȣ�� Ű����κ��� �д´�. 
    cout << girl << endl << boy << endl; // ��ȭ ��ȣ�� ����Ѵ�. 
}
