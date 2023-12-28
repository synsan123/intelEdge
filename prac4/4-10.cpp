#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
	Person() {};
	Person(string name) { this->name = name; }
	string getName() { return name; }
	void setName(string name) { this->name = name; }
private:
	string name;
};

class Family
{
public:
	Family(string name, int size);
	void setName(int num, string name);
	~Family();
	void show();
private:
	int size;
	string name;
	Person* p;
};

Family::Family(string name, int size)
{
	p = new Person[size];
	this->name = name;
	this->size = size;
}

Family::~Family()
{
	delete[] p;
}

void Family::setName(int num, string name)
{
	p[num].setName(name);
}

void Family::show()
{
	cout << name << "가족은 다음과 같이 " << size << "명 입니다." << endl;

	for (int i = 0; i < size; i++)
	{
		cout << p[i].getName() << "\t";
	}
}

int main()
{
	Family* simpson = new Family("Simpson", 3);
	simpson->setName(0, "Mr.Simpson");
	simpson->setName(1, "Mrs.Simpson");
	simpson->setName(2, "Bart Simpson");
	simpson->show();
	delete simpson;
}