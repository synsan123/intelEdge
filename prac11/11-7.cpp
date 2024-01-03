#include <iostream>
#include <cctype>
#include <iomanip>
using namespace std;

void showDec(int d) { // 10진수 출력 
    cout << setw(10) << dec << d;
}

void showHexa(int h) { // 16진수 출력 
    cout << setw(10) << hex << h;
}

void showChar(int c) { // ASCII 출력 
    int i = 0;
    if ((i = isprint(c)) != 0) // 출력 가능한 문자인지 확인 
        cout << setw(10) << (char)c;
    else // 출력 불가능한 문자이면 "." 출력 
        cout << setw(10) << ".";
}

void print() {
    for (int i = 0; i < 4; i++) {
        cout << setw(10) << "dec";
        cout << setw(10) << "hexa";
        cout << setw(10) << "char";
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        cout << setw(10) << "---";
        cout << setw(10) << "----";
        cout << setw(10) << "----";
    }
    cout << endl;
    for (int i = 0; i < 128; i++) { // 127번 반복하여 dec, hexa, ASCII 출력 
        if (i % 4 == 0 && i != 0)
            cout << endl;
        showDec(i);
        showHexa(i);
        showChar(i);
    }
}
int main() {
    cout.setf(ios::left); // 출력 포맷 왼쪽 정렬 
    print();
}
