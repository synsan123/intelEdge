#include <iostream>
using namespace std;

int main()
{
    char name[10];
    char street[100];
    int age;

    cout << "�̸���? ";
    cin.getline(name, 10);
    
    cout << "�ּҴ�? ";
    cin.getline(street, 100);

    cout << "���̴�? ";
    cin >> age;

    cout << endl;
    cout << name << ", " << street << ", " << age << "��" << endl;

    return 0;
}