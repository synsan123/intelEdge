#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Book {
    int year;
    string b_name;
    string p_name;
public:
    void set(int year, string b_name, string p_name) {
        this->year = year; this->b_name = b_name; this->p_name = p_name;
    }
    string getP() {
        return p_name;
    }
    int getY() {
        return year;
    }
    void show() {
        cout << year << "�⵵, " << b_name << ", " << p_name << endl;
    }
};

int main() {
    vector<Book> v;
    Book b;
    int year;
    string b_name;
    string p_name;

    cout << "�԰��� å�� �Է��ϼ���. �⵵�� -1�� �Է��ϸ� �԰� �����մϴ�.\n";

    while (true) {
        cout << "�⵵>>";
        cin >> year;
        if (year == -1)
            break;
        fflush(stdin);
        cout << "å�̸�>>";
        getline(cin, b_name);
        cout << "����>>";
        getline(cin, p_name);

        b.set(year, b_name, p_name);
        v.push_back(b);
    }

    cout << "�� �԰�� å�� " << v.size() << "�� �Դϴ�.\n";
    cout << "�˻��ϰ��� �ϴ� ���� �̸��� �Է��ϼ���>>";
    fflush(stdin);
    getline(cin, p_name);
    for (int i = 0; i < v.size(); i++) {
        if (v[i].getP() == p_name)
            v[i].show();
    }
    cout << "�˻��ϰ��� �ϴ� �⵵�� �Է��ϼ���>>";
    cin >> year;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].getY() == year)
            v[i].show();
    }
}
