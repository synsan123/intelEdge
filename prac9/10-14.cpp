#include <iostream>
#include <map>
using namespace std;

void insert(map<string, string>& pwManager) {
    string name, pw;
    cout << "�̸� ��ȣ>> ";
    cin >> name >> pw;
    pwManager.insert(make_pair(name, pw));
}

void checkNamePw(map<string, string>& pwManager) {
    string name, pw;
    cout << "�̸�? "; cin >> name;
    while (true) {
        cout << "��ȣ? "; cin >> pw;
        if (pwManager[name] == pw) {
            cout << "���!!\n";
            break;
        }
        else
            cout << "����~~\n"; // Ʋ���� ��� �� �ٽ� ��ȣ ���� 
    }
}

int main() {
    map<string, string> pwManager;
    cout << "***** ��ȣ ���� ���α׷� WHO�� �����մϴ� *****\n";

    while (true) {
        cout << "����:1, �˻�:2, ����3>> ";
        int n;
        cin >> n;
        switch (n) {
        case 1:
            insert(pwManager);
            break;
        case 2:
            checkNamePw(pwManager);
            break;
        case 3:
            cout << "���α׷��� �����մϴ�...";
            return 0;
        }
    }
}
