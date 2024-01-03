#include <iostream>
#include <map>
using namespace std;

void insert(map<string, string>& pwManager) {
    string name, pw;
    cout << "이름 암호>> ";
    cin >> name >> pw;
    pwManager.insert(make_pair(name, pw));
}

void checkNamePw(map<string, string>& pwManager) {
    string name, pw;
    cout << "이름? "; cin >> name;
    while (true) {
        cout << "암호? "; cin >> pw;
        if (pwManager[name] == pw) {
            cout << "통과!!\n";
            break;
        }
        else
            cout << "실패~~\n"; // 틀리면 출력 후 다시 암호 질문 
    }
}

int main() {
    map<string, string> pwManager;
    cout << "***** 암호 관리 프로그램 WHO를 시작합니다 *****\n";

    while (true) {
        cout << "삽입:1, 검사:2, 종료3>> ";
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
            cout << "프로그램을 종료합니다...";
            return 0;
        }
    }
}
