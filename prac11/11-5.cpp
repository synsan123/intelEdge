#include <iostream>
using namespace std;

int main() {
    string cmd;
    while (true) {
        cout << "�����Ϸ��� exit�� �Է��ϼ��� >> ";
        getline(cin, cmd); // getline() �Լ��� ���� ���ڿ� �Է�
        if (cmd == "exit") {
            cout << "���α׷��� �����մϴ�....";
            return 0;
        }
    }
}
