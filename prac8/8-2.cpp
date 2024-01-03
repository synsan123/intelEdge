#include <iostream>
#include <string>

using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius = 0) { this->radius = radius; }
	int getRadius() { return radius; }
	void setRadius(int radius) { this->radius = radius; }
	double getArea() { return 3.14 * radius * radius; }
};

class NamedCircle : public Circle {
	string name;
public:
	NamedCircle(int radius = 0, string name = "") : Circle(radius) {
		this->name = name;
	}
	void show() {
		cout << "�������� " << getRadius() << "�� " << name << endl;
	}
	string getName() { return name; }
	void setName(string name) { this->name = name; }
};

int main() {
	cout << "5���� ���� �������� ���� �̸��� �Է��ϼ���" << endl;
	NamedCircle pizza[5];
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << ">> ";
		int r; string name;
		cin >> r >> name;
		pizza[i].setName(name);
		pizza[i].setRadius(r);
	}
	int max = 0, maxInd;
	for (int i = 0; i < 5; i++) {
		if (pizza[i].getArea() > max) {
			max = pizza[i].getArea();
			maxInd = i;
		}
	}
	cout << "���� ������ ū ���ڴ� " << pizza[maxInd].getName() << "�Դϴ�" << endl;
	return 0;
}