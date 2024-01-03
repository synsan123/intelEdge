#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Circle;
Circle& operator ++(Circle& c);			//���� ������
Circle operator ++(Circle& c, int x);	//���� ������

class Circle {
	int radius;
public:
	Circle(int radius = 0) { this->radius = radius; }
	void show() { cout << "radius = " << radius << " �� ��" << endl; }
	friend Circle& operator ++(Circle& c);
	friend Circle operator ++(Circle& c, int x);
};

Circle& operator ++(Circle& c) {
	c.radius++;
	return c;
}
Circle operator ++(Circle& c, int x) {
	Circle tmp = c;
	c.radius++;
	return tmp;
}

int main() {
	Circle a(5), b(4);
	++a;
	b = a++;
	a.show();
	b.show();
	return 0;
}