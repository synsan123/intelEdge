#include <iostream>
using namespace std;

class Circle { // 원을 표현하는 클래스 
    string name;
    int radius;
public:
    Circle(int radius = 1, string name = "") {
        this->radius = radius; this->name = name;
    }
    friend ostream& operator << (ostream& os, Circle c); // friend 선언 
    friend istream& operator >> (istream& ins, Circle& c); // friend 선언, Circle& c 참조자 사용 
};

ostream& operator << (ostream& os, Circle c) {
    os << "(반지름이" << c.radius << "인 " << c.name << ")";
    return os;
}

istream& operator >> (istream& ins, Circle& c) {
    cout << "반지름 >> ";
    ins >> c.radius;
    cout << "이름 >> ";
    ins >> c.name;
    return ins;
}

int main() {
    Circle d, w;
    cin >> d >> w; // 키보드 입력을 받아 객체 d와 w를 완성 
    cout << d << w << endl; // 객체 d, w 출력 
}
