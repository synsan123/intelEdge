#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
	Person();
	string getName() { return name; }
	string getTel() { return tel; }
	void set(string name, string tel);
private:
	string name;
	string tel;
};

Person::Person() {}
void Person::set(string name, string tel)
{
	this->name = name;
	this->tel = tel;
}
int main()
{
	string name, tel;
	Person* p = new Person[3];

	cout << "�̸��� ��ȭ��ȣ�� �Է��� �ּ���" << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << "��� " << i+1 << ">> ";
		cin >> name >> tel;
		p[i].set(name, tel);
	}

	cout << "��� ����� �̸��� ";

	for (int i = 0; i < 3; i++)
	{
		cout << p[i].getName() << " ";
	}

	cout << endl;
	cout << "��ȭ��ȣ �˻��մϴ�. �̸��� �Է��ϼ��� >> ";
	cin >> name;

	for (int i = 0; i < 3; i++)
	{
		if (name.compare(p[i].getName()) == 0)
		{
			cout << "��ȭ��ȣ�� " << p[i].getTel();
		}
		break;
	}
}