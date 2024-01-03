#include <iostream>
#include <algorithm>

using namespace std;

class Nation {
    string nation;
    string capital;
public:
    Nation(string n = 0, string c = 0) {
        nation = n;
        capital = c;
    }
    string getNation() {
        return nation;
    }
    string getCapital() {
        return capital;
    }
    bool nationCompare(string n) { //���� �̸��� ���ϴ� �Լ�. 
        if (nation == n)
            return true;
        return false;
    }
};

int main() {
    vector<Nation> v;
    v.push_back(Nation("���ѹα�", "����"));
    v.push_back(Nation("�߱�", "����¡"));
    v.push_back(Nation("����", "���"));
    v.push_back(Nation("�̱�", "�ͽ���"));
    v.push_back(Nation("�븸", "Ÿ�̺���"));
    v.push_back(Nation("ĳ����", "��Ÿ��"));
    v.push_back(Nation("������", "���׹�"));
    v.push_back(Nation("������", "�ĸ�"));
    v.push_back(Nation("����Ʈ", "ī�̷�"));

    cout << "***** ������ ���� ���߱� ������ �����մϴ�. *****\n";

    while (true) {
        int num;
        cout << "���� �Է�: 1, ����: 2, ���� 3 >> ";
        cin >> num;
        switch (num) {
        case 1:
            cout << "���� " << v.size() << "���� ���� �ԷµǾ� �ֽ��ϴ�.\n";
            cout << "����� ������ �Է��ϼ���(no no �̸� �Է³�)\n";
            for (int i = v.size() + 1;; i++) {
                string n, c;
                bool b;
                cout << i << ">>";
                cin >> n >> c;
                if (n == "no" && c == "no")
                    break;
                for (int j = 0; j < v.size(); j++)
                    if (b = v.at(j).nationCompare(n)) {
                        cout << "already exists !!\n";
                        i--;
                        break;
                    }
                if (b)
                    continue;
                v.push_back(Nation(n, c)); // �������� �Է� ���̸� vector v�� �Է� 
            }
            break;

        case 2:
            int random;
            while (true) {
                string c;
                random = rand() % v.size(); // v�� ����ִ� ������ �������� ���� ���ڸ� ����
                cout << v.at(random).getNation() << "�� ������?";
                cin >> c;
                if (c == "exit")
                    break;
                else if (v.at(random).getCapital() == c) // �Է¹��� ������ ������ Correct ��� 
                    cout << "Correct !!\n";
                else
                    cout << "No !!\n";
            }
            break;

        case 3:
            return 0;
        }
    }
}
