#include <iostream>
using namespace std;

class Phone { // 전화 번호를 표현하는 클래스 
    string name;
    string telnum;
    string address;
public:
    Phone(string name = "", string telnum = "", string address = "") {
        this->name = name;
        this->telnum = telnum;
        this->address = address;
    }
    friend ostream& operator << (ostream& os, Phone p); // friend 작성 
    friend istream& operator >> (istream& ins, Phone& p); // friend 작성, Phone& p 참조자 사용 
};

ostream& operator << (ostream& os, Phone p) {
    os << "(" << p.name << "," << p.telnum << "," << p.address << ")";
    return os;
}

istream& operator >> (istream& ins, Phone& p) {
    cout << "이름:";
    ins >> p.name;
    cout << "전화번호:";
    ins >> p.telnum;
    cout << "주소:";
    ins >> p.address;
    return ins;
}

int main() {
    Phone girl, boy;
    cin >> girl >> boy; // 전화 번호를 키보드로부터 읽는다. 
    cout << girl << endl << boy << endl; // 전화 번호를 출력한다. 
}
