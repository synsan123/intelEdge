#include <iostream>
using namespace std;

int main() {
    char ch;
    int cnt;

    while (true) {
        cin.get(ch); // Ű�� ch�� �о��
        if (cin.eof()) // EOF ���� �� ctrl-z Ű�� �Էµ� ���, �б� ���� 
            break;
        if (ch == '\n') // <Enter> Ű�� �Էµ� ��� �б� �ߴ� 
            break;
        else if (ch == ' ')
            cnt++;
    }
    cout << cnt;
}
