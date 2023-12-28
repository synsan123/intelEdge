#include <iostream>
#include <string>
using namespace std;

class Circle {
	int radius = 1;
	string name;
public:
	Circle() { radius = 1; }
	void setCircle(string name, int radius);
	double getArea() {	return 3.14 * radius * radius; }
	string getName() { return name; }
};

class CircleManager {
	Circle* p;
	int size;
	int radius;
	string name;
public:
	CircleManager(int size);
	~CircleManager();
	void searchByName();
	void searchByArea();
};

void Circle::setCircle(string name, int radius)
{
	this->name = name;
	this->radius = radius;
}

CircleManager::CircleManager(int size)
{
	p = new Circle[size];
	this->size = size;
	for (int i = 0; i < size; i++)
	{
		cout << "�� " << i + 1 << "�� �̸��� ������ >> ";
		cin >> name >> radius;
		p[i].setCircle(name, radius);
	}
}
CircleManager::~CircleManager() {
	delete[] p;
}

void CircleManager::searchByName() {
	cout << "�˻��ϰ��� �ϴ� ���� �̸� >> ";
	cin >> name;
	for (int i = 0; i < size; i++)
	{
		if (name == p[i].getName())
		{
			cout << name << "�� ������ " << p[i].getArea() << endl;
		}
	}
}

void CircleManager::searchByArea() {
	cout << "�ּ� ������ ������ �Է��ϼ��� >> ";
	cin >> radius;
	cout << radius << "���� ū ���� �˻��մϴ�." << endl;
	for (int i = 0; i < size; i++)
	{
		if (radius < p[i].getArea())
		{
			cout << p[i].getName() << "�� ������ " << p[i].getArea() << ",";
		}
	}
}

int main()
{
	int size;
	cout << "���� ���� >> ";
	cin >> size;
	CircleManager CircleManage(size);
	CircleManage.searchByName();
	CircleManage.searchByArea();
}