#include <iostream>
#include <cctype>
#include <iomanip>
using namespace std;

void showDec(int d) { // 10���� ��� 
    cout << setw(10) << dec << d;
}

void showHexa(int h) { // 16���� ��� 
    cout << setw(10) << hex << h;
}

void showChar(int c) { // ASCII ��� 
    int i = 0;
    if ((i = isprint(c)) != 0) // ��� ������ �������� Ȯ�� 
        cout << setw(10) << (char)c;
    else // ��� �Ұ����� �����̸� "." ��� 
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
    for (int i = 0; i < 128; i++) { // 127�� �ݺ��Ͽ� dec, hexa, ASCII ��� 
        if (i % 4 == 0 && i != 0)
            cout << endl;
        showDec(i);
        showHexa(i);
        showChar(i);
    }
}
int main() {
    cout.setf(ios::left); // ��� ���� ���� ���� 
    print();
}
