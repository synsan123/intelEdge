#include <iostream>
#include <string>
using namespace std;

istream& prompt(istream& ins) { // prompt ������ 
    cout << "��ȣ?";
    return ins;
}

int main() {
    string password;
    while (true) {
        cin >> prompt >> password;
        if (password == "C++") {
            cout << "login success!!" << endl;
            break;
        }
        else
            cout << "login fail. try again!!" << endl;
    }
}
