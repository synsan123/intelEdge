#include<iostream>
#include<string>
#include<map>
using namespace std;

int main() {
    map<string, int> Score; // map �����̳� ����. Ű�� �ѱ� �̸�, ���� ���� ���� 

    cout << "***** �������� ���α׷� HIGH SCORE�� �����մϴ� *****\n";
    while (true) {
        int num;
        int score;
        string name;
        cout << "�Է�:1, ��ȸ:2, ����:3 >> ";
        cin >> num;
        switch (num) {
        case 1:
            cout << "�̸��� ����>> ";
            cin >> name >> score;
            Score.insert(make_pair(name, score)); // map�� ���� 
            break;
        case 2:
            cout << "�̸� >> ";
            cin >> name;
            if (Score.find(name) == Score.end()) // name 'Ű'�� ������ ã�Ҵµ� ���� 
                cout << "����" << endl;
            else
                cout << name << "�� ������ " << Score[name] << endl; // Score���� name�� ���� ã�� ��� 
            break;
        case 3:
            cout << "���α׷��� �����մϴ�...\n";
            return 0;
        default:
            cout << "����� �Է���\n";
            break;
        }
    }
}
