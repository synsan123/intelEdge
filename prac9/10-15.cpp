#include<iostream>
#include<vector>
using namespace std;

class Circle {
    string name; // �̸� 
    int radius; // ������ 
public:
    Circle(int radius, string name) {
        this->radius = radius; this->name = name;
    }
    double getArea() { return 3.14 * radius * radius; }
    string getName() { return name; }
};

int main() {
    cout << "���� �����ϰ� �����ϴ� ���α׷��Դϴ�.\n";
    vector<Circle*> v;

    while (true) {
        int num;
        int radius;
        string name;
        cout << "����:1, ����:2, ��κ���:3, ����:4 >> ";
        cin >> num;
        switch (num) {
        case 1:
            cout << "�����ϰ��� �ϴ� ���� �������� �̸��� >> ";
            cin >> radius >> name;
            v.push_back(new Circle(radius, name));
            break;
        case 2: {
            cout << "�����ϰ��� �ϴ� ���� �̸��� >> ";
            cin >> name;
            vector<Circle*>::iterator it = v.begin();
            while (it != v.end()) {
                Circle* p = *it;
                if (p->getName() == name) {
                    it = v.erase(it);
                    delete p;
                }
                else
                    it++;
            }
            break;
        }
        case 3: {
            vector<Circle*>::iterator it;
            for (it = v.begin(); it != v.end(); it++) {
                Circle* p = *it;
                cout << p->getName() << endl;
            }
            cout << endl;
            break;
        }
        case 4:
            return 0;
        }
    }
}
