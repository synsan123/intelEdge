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
		cout << "반지름이 " << getRadius() << "인 " << name << endl;
	}
	string getName() { return name; }
	void setName(string name) { this->name = name; }
};

int main() {
	cout << "5개의 정수 반지름과 원의 이름을 입력하세요" << endl;
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
	cout << "가장 면적이 큰 피자는 " << pizza[maxInd].getName() << "입니다" << endl;
	return 0;
}