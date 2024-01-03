#include <iostream>
using namespace std;

int main() {
    string cmd;
    while (true) {
        cout << "종료하려면 exit을 입력하세요 >> ";
        getline(cin, cmd); // getline() 함수를 통해 문자열 입력
        if (cmd == "exit") {
            cout << "프로그램을 종료합니다....";
            return 0;
        }
    }
}
