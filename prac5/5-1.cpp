#include <iostream>
using namespace std;

class Circle
{
public:
	Circle() { radius = 1; }
	Circle(int radius) { this->radius = radius; }
	double getArea() { return 3.14 * radius * radius; }
private:
	int radius;
};

void swap(Circle& a, Circle& b)
{
	Circle temp;
	temp = a;
	a = b;
	b = temp;
}

int main()
{
	Circle circle1(2), circle2(5);
	cout << "swap 전의 원의 면적은 " << circle1.getArea() << " " << circle2.getArea() << endl;
	swap(circle1, circle2);
	cout << "swap 후의 원의 면적은 " << circle1.getArea() << " " << circle2.getArea() << endl;
}