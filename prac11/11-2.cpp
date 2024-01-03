#include <iostream>
using namespace std;

int main() {
    char ch;
    int cnt;

    while (true) {
        cin.get(ch); // 키를 ch에 읽어옴
        if (cin.eof()) // EOF 문자 즉 ctrl-z 키가 입력된 경우, 읽기 종료 
            break;
        if (ch == '\n') // <Enter> 키가 입력된 경우 읽기 중단 
            break;
        else if (ch == ' ')
            cnt++;
    }
    cout << cnt;
}
