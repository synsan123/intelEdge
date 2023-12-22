#include <iostream>
using namespace std;

int main()
{
    char name[10];
    char street[100];
    int age;

    cout << "이름은? ";
    cin.getline(name, 10);
    
    cout << "주소는? ";
    cin.getline(street, 100);

    cout << "나이는? ";
    cin >> age;

    cout << endl;
    cout << name << ", " << street << ", " << age << "세" << endl;

    return 0;
}